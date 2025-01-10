#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "aluno.h"
#include "../data/files.h"
#include "../style/colors.h"
#include "../style/menu.h"
#include "../utils/string_util.h"
#define SIZE_BUFFER 100
#define DEZENA 10

#ifdef _WIN32
    #define PATH_SEPARATOR_CHAR '\\'
    #define PATH_SEPARATOR_STR  "\\"
#elif __linux__
    #define PATH_SEPARATOR_CHAR '/'
    #define PATH_SEPARATOR_STR  "/"
#endif

//#define ZERO 0 talvez??



ALUNO * criar_lista(int size_alunos) {

    ALUNO * lista_estudantes; //estrutura com informacao dos alunos
    lista_estudantes = malloc(sizeof(ALUNO)*((size_alunos)+2));

    if (sizeof(lista_estudantes)==0) {
        printf("ERRO!");
        return 0;
    }

    for (int i = 0; i<size_alunos; i++) {
        lista_estudantes[i].ocupado = 0;
    }

    return lista_estudantes;
}




int seek_data(txtFile file_estudante, txtFile file_situacao, ALUNO *base_dados, size_t *size_alunos)
{
    size_t wrt_size_alunos = 0;

    //Atribuição dos dados do ficheiro estudantes.txt à struct
    txt_load_file(&file_estudante);
    int tamanho = file_get_size(file_estudante)-1;
    for (int i=0; i < tamanho ; i++) {
        if ((base_dados[i]).ocupado==0) {

            base_dados[i].ocupado=1;

            char *linha = file_estudante.data[i];
            char **dados = str_split(linha, '\t', NULL); //tendo em conta que cada secção está separada por \t

            base_dados[i].codigo = atoi(strdup(dados[0]));

            base_dados[i].nome = strdup(dados[1]);


            char *dn = dados[2];
            char **ptr_dn = str_split(dn, '-', NULL);
            base_dados[i].data_n.dia= atoi(strdup(ptr_dn[0]));
            base_dados[i].data_n.mes= atoi(strdup(ptr_dn[1]));
            base_dados[i].data_n.ano= atoi(strdup(ptr_dn[2]));
            
            base_dados[i].nacionalidade = strdup(dados[3]);
            wrt_size_alunos++;
        }
    }
    txt_unload_file(&file_estudante);
    
    //Atribuição dos dados do ficheiro situaçao_Escolar_Estudantes.txt à struct
    //É efetuada a sua correta colocação por comparação dos números de código
    txt_load_file(&file_situacao);
    
    for (int i=0; (i < tamanho) && (i < file_get_size(file_situacao)); i++) {
        char *linha = file_situacao.data[i];
        char **dados = str_split(linha, '\t', NULL);
        for (int j=0 ; j<tamanho ; j++) {
            if (atoi(dados[0]) == base_dados[j].codigo) {
                base_dados[i].n_matriculas= atoi(strdup(dados[1]));
                
                base_dados[i].ects_concluidos= atoi(strdup(dados[2]));
            
                base_dados[i].ano_curso= atoi(strdup(dados[3]));
                
                char * carater = strdup(dados[4]);
                for (int k=0; k<strlen(carater); k++) {
                    if (carater[k]== '.') {
                        carater[k] = ',';
                    }
                }
                
                base_dados[i].media_atual= atof(strdup(carater));
            }
        }
    }
    txt_unload_file(&file_situacao);

    if (size_alunos != NULL) *size_alunos = tamanho;
    return tamanho;
}




int inserir_estudante(ALUNO *lista_estudantes, int size_base)
{
    //alocar memória para o aluno novo
    ALUNO * ptr = lista_estudantes;
    ptr = (ALUNO *) malloc(sizeof(ALUNO));
    ALUNO * new_lista_estudantes = (ALUNO *) realloc(ptr , sizeof(ALUNO)* (size_base+1));
    if(!new_lista_estudantes)
    {
        printf("erro\n");
        free(ptr);
    }
    
    //procurar posição livre
    int j = 0;
    while((lista_estudantes[j]).ocupado==1) {
        j++;
    }

    //ocupar posição
    (lista_estudantes[j]).ocupado=1; //passa a estar ocupado, e, portanto, visível para as outras funcoes

    //determina o código do novo aluno
    //procura o maior código já utilizado e soma-lhe uma unidade
    int maior_codigo = 0;
    for (int i=0;i<size_base;i++) {
        if (lista_estudantes[i].codigo>maior_codigo) {
            maior_codigo = lista_estudantes[i].codigo;
        }
    }
    lista_estudantes[j].codigo = maior_codigo +1;
    printf("Codigo: ");
    printf(" %d",((lista_estudantes[j]).codigo));

    char * stringgg=NULL;
    size_t bufsize=200;
    printf("\nNome: ");
    fflush(stdin);
    //não consegui usar o scanf ou gets (?????????????porquê?????)
    getline(&stringgg,&bufsize,stdin);
    stringgg = * str_split(stringgg, '\n', NULL);
    lista_estudantes[j].nome=(char*) malloc(sizeof(stringgg));
    lista_estudantes[j].nome=stringgg;
    fflush(stdin);
    
    stringgg=NULL;
    bufsize=11;
    printf("Data de nascimento (dd-mm-aaaa): ");
    fflush(stdin);
    getline(&stringgg,&bufsize,stdin);
    stringgg = * str_split(stringgg, '\n', NULL);
    char *dn = stringgg;
    char **ptr_dn = str_split(dn, '-', NULL);
    lista_estudantes[j].data_n.dia= atoi(strdup(ptr_dn[0]));
    lista_estudantes[j].data_n.mes= atoi(strdup(ptr_dn[1]));
    lista_estudantes[j].data_n.ano= atoi(strdup(ptr_dn[2]));

    fflush(stdin);

    stringgg=NULL;
    bufsize=200;
    printf("Nacionalidade: ");
    fflush(stdin);
    getline(&stringgg,&bufsize,stdin);
    stringgg = * str_split(stringgg, '\n', NULL);
    lista_estudantes[j].nacionalidade=(char*) malloc(sizeof(stringgg));
    lista_estudantes[j].nacionalidade=stringgg;
    fflush(stdin);

    printf("Ano de curso: ");
    fflush(stdin);
    scanf(" %d",&((lista_estudantes[j]).ano_curso));

    printf("Media atual: ");
    fflush(stdin);
    char m_temp[5];
    scanf("%s", m_temp);
    for (int i=0; i<strlen(m_temp); i++) {
        if (m_temp[i] == '.') {
            m_temp[i] = ',';
        }
    }
    lista_estudantes[j].media_atual = atof(m_temp);

    printf("ECTS concluidos: ");
    fflush(stdin);
    scanf(" %d",&((lista_estudantes[j]).ects_concluidos));

    printf("Numero de matriculas: ");
    fflush(stdin);
    scanf(" %d",&((lista_estudantes[j]).n_matriculas));

    puts("\n");
    fflush(stdin);

    //para esvaziar a memória alocada no caso de não ser necessária
    if (j==size_base) {
    free(new_lista_estudantes);
    }
        
    size_base++; //tamanho da estrutura aumenta; relevante porque sizeof() é calculado durante a compilação e não é atualizado

    char * t_guardar = malloc(sizeof(char)*4);
    t_guardar = tipo_de_guardar();

    //guardar os dados do novo aluno num ficheiro .txt ou .cvs (os princípios desta secção aplicam-se a todas as outras secções em que se guardem ficheiros)
    if (strcmp(t_guardar,".txt")==0) {
        
        int temp = lista_estudantes[j].codigo; //para transformacao em *char
        char * temp2 = malloc(sizeof(char)*SIZE_BUFFER); //exagero de espaço, mas se não o fizesse dava erro; vai ser onde é guardado temporariamente o float ou int transformado em char*
        sprintf(temp2, "%d", temp); //utilizado no caso de ser necessário transformar int ou float em char*
        char * info = strdup(temp2);
        info = strcat(info,"\t"); 

        info = strcat(info, strdup(lista_estudantes[j].nome));
        info = strcat(info,"\t"); 
    
        temp = lista_estudantes[j].data_n.dia;
        if (temp<DEZENA) {
            info = strcat(info,"0"); //para que a data de nascimento em char* tenha sempre 2 caracteres no dia (ou mês)
        }
        sprintf(temp2, "%d", temp);
        info = strcat(info,strdup(temp2));
        info = strcat(info,"-"); 

        temp = lista_estudantes[j].data_n.mes;
        if (temp<DEZENA) {
            info = strcat(info,"0"); 
        }
        sprintf(temp2, "%d", temp);
        info = strcat(info,strdup(temp2));
        info = strcat(info,"-"); 
     
        temp = lista_estudantes[j].data_n.ano;
        sprintf(temp2, "%d", temp);
        info = strcat(info,strdup(temp2));
        info = strcat(info,"\t"); 
  
        info = strcat(info, strdup(lista_estudantes[j].nacionalidade));
        info = strcat(info,"\t"); 
  
        temp = lista_estudantes[j].n_matriculas;
        sprintf(temp2, "%d", temp);
        info = strcat(info, strdup(temp2));
        info = strcat(info,"\t");
   
        temp = lista_estudantes[j].ects_concluidos;
        sprintf(temp2, "%d", temp);
        info = strcat(info,strdup(temp2));
        info = strcat(info,"\t"); 

        temp = lista_estudantes[j].ano_curso;
        sprintf(temp2, "%d", temp);
        info = strcat(info,strdup(temp2));
        info = strcat(info,"\t"); 
   
        float temp_f = lista_estudantes[j].media_atual;
        sprintf(temp2, "%.1f", temp_f);
        for (int k=0; k<strlen(temp2)+1; k++) {
            
            if (temp2[k] == ',') { //o compilador só trata de floats com vírgulas, mas os inputs e outputs têm pontos
                temp2[k] = '.';
            }
        }
        info = strcat(info,strdup(temp2));
        info = strcat(info,"\n"); 
        
        temp = lista_estudantes[j].codigo;
        sprintf(temp2, "%d", temp);

        char * nome = strdup("novo_aluno_"); //determina o nome do ficheiro dependendo da situacao
        nome = strcat(nome,temp2);
        nome = strcat(nome,".txt"); //neste caso, tem .txt
        txt_result_save_file(info, nome);

    }
    else if (strcmp(t_guardar,".cvs")==0) {
        char * header = "Codigo\tNome\tData Nascimento\tNacionalidade\tNumero Matriculas\tECTS Concluidos\tAno Curso\tMedia Atual\n"; //header do ficheiro .cvs
        
        int temp = lista_estudantes[j].codigo;
        char * temp2 = malloc(sizeof(char)*SIZE_BUFFER); 
        sprintf(temp2, "%d", temp);
        char * info = strdup(temp2);
        info = strcat(info,"\t"); 

        info = strcat(info, strdup(lista_estudantes[j].nome));
        info = strcat(info,"\t"); 
    
        temp = lista_estudantes[j].data_n.dia;
        if (temp<DEZENA) {
            info = strcat(info,"0"); 
        }
        sprintf(temp2, "%d", temp);
        info = strcat(info,strdup(temp2));
        info = strcat(info,"-"); 

        temp = lista_estudantes[j].data_n.mes;
        if (temp<DEZENA) {
            info = strcat(info,"0"); 
        }
        sprintf(temp2, "%d", temp);
        info = strcat(info,strdup(temp2));
        info = strcat(info,"-"); 
     
        temp = lista_estudantes[j].data_n.ano;
        sprintf(temp2, "%d", temp);
        info = strcat(info,strdup(temp2));
        info = strcat(info,"\t"); 
  
        info = strcat(info, strdup(lista_estudantes[j].nacionalidade));
        info = strcat(info,"\t"); 
  
        temp = lista_estudantes[j].n_matriculas;
        sprintf(temp2, "%d", temp);
        info = strcat(info, strdup(temp2));
        info = strcat(info,"\t");
   
        temp = lista_estudantes[j].ects_concluidos;
        sprintf(temp2, "%d", temp);
        info = strcat(info,strdup(temp2));
        info = strcat(info,"\t"); 

        temp = lista_estudantes[j].ano_curso;
        sprintf(temp2, "%d", temp);
        info = strcat(info,strdup(temp2));
        info = strcat(info,"\t"); 
   
        float temp_f = lista_estudantes[j].media_atual;
        sprintf(temp2, "%.1f", temp_f);
        for (int k=0; k<strlen(temp2)+1; k++) {
            
            if (temp2[k] == ',') {
                temp2[k] = '.';
            }
        }
        info = strcat(info,strdup(temp2));
        info = strcat(info,"\n"); 
    
        temp = lista_estudantes[j].codigo;
        sprintf(temp2, "%d", temp);

        char * nome = strdup("novo_aluno_");
        nome = strcat(nome,temp2);
        nome = strcat(nome,".cvs");
        txt_result_save_file(info, nome);
        
    }


    return size_base;
}




void remover_estudante(ALUNO *lista_estudantes,int i)
{
    (lista_estudantes[i]).ocupado=0; //passa a ficar desocupado; deixa de aparecer em qualquer outra funcao
    //Para esvaziar os string:
    (*(lista_estudantes+i)).nome=NULL;
    (*(lista_estudantes+i)).nacionalidade=NULL;
}




void atualizar_uma_caracteristica_estudante(ALUNO *lista_estudantes, int size_base)
{
    //setlocale(LC_ALL, "Portuguese"); //não funciona?
    int i=0; //resultado das opcoes a alterar
    int k=0; //código do estudante
    int j=0; //posição do aluno com código k na lista
    int t=0; //determina posicao do estudante, verifica que existe
    do {
        printf("Qual o codigo do estudante? ");
        fflush(stdin);
        scanf(" %d",&k);

        for(t=0;t<size_base;t++) {
            if(lista_estudantes[t].codigo==k && lista_estudantes[t].ocupado==1) {
                j=t;
                break;
            }
        }

        if (t==size_base) {
            printf("\nErro! Escolha um codigo valido. ");
            fflush(stdin);
        }
    }
    while (t==size_base);

    i = menu_opcoes_field();

    switch (i) {
        //i indica qual elemento da estrutura a mudar, fornecido pelo utilizador no menu anterior
        case 1:
            printf("Qual o novo numero de ECTS concluidos do estudante numero %d?\n",(lista_estudantes[j]).codigo);
            scanf("%d",&(lista_estudantes[j]).ects_concluidos);
            break;

        case 2:
            printf("Qual o novo ano de curso do estudante número %d?\n",(lista_estudantes[j]).codigo);
            scanf("%d",&(lista_estudantes[j]).ano_curso);
            break;

        case 3:
            printf("Qual a nova media do estudante numero %d?\n",(lista_estudantes[j]).codigo);
            scanf("%f",&(lista_estudantes[j]).media_atual);
            break;

        case 4:
            //Esvazia-se o string primeiro para evitar erros:
            (*(lista_estudantes+j)).nome=NULL;
            //Por algum motivo o scanf e gets não funcionam para mim, por isso tenho de fazer esta abominação
            char * stringgg=NULL;
            size_t bufsize=200;
            printf("Qual o novo nome do estudante numero %d?\n",(lista_estudantes[j]).codigo);
            fflush(stdin);
            getline(&stringgg,&bufsize,stdin);
            stringgg = * str_split(stringgg, '\n', NULL);
            lista_estudantes[j].nome=(char*) malloc(sizeof(stringgg));
            lista_estudantes[j].nome=stringgg;
            fflush(stdin);
            break;

        case 5:
            (*(lista_estudantes+j)).nacionalidade=NULL;
            stringgg=NULL;
            bufsize=200;
            printf("Qual a nova nacionalidade do estudante numero %d?\n",(lista_estudantes[j]).codigo);
            fflush(stdin);
            getline(&stringgg,&bufsize,stdin); //scanf decidiu reclamar comigo
            stringgg = * str_split(stringgg, '\n', NULL);
            lista_estudantes[j].nacionalidade=(char*) malloc(sizeof(stringgg));
            lista_estudantes[j].nacionalidade=stringgg;
            fflush(stdin);
            break;

        case 6:

            stringgg=NULL;
            bufsize=11;
            printf("Qual a nova data de nascimento do estudante numero %d?\n",(lista_estudantes[j]).codigo);
            fflush(stdin);
            getline(&stringgg,&bufsize,stdin);
            stringgg = * str_split(stringgg, '\n', NULL);
            char *dn = stringgg;
            char **ptr_dn = str_split(dn, '-', NULL); //Separa o string  da data nas suas componentes para ser mais fácil lidar com ele
            lista_estudantes[j].data_n.dia= atoi(strdup(ptr_dn[0]));
            lista_estudantes[j].data_n.mes= atoi(strdup(ptr_dn[1]));
            lista_estudantes[j].data_n.ano= atoi(strdup(ptr_dn[2]));

            fflush(stdin);
            break;

        case 7:
            printf("Qual o novo numero de matriculas do estudante numero %d?\n",(lista_estudantes[j]).codigo);
            char m_temp[5];
            scanf("%s", m_temp);
            for (int i=0; i<strlen(m_temp); i++) {
                if (m_temp[i] == '.') { //inputs podem estar com pontos, mas compilador só funciona com vírgulas em floats
                    m_temp[i] = ',';
                }
            }
            lista_estudantes[j].n_matriculas = atof(m_temp);
            break;
    }

    printf("Novos dados do estudante:\n");
    mostrar_um_aluno(lista_estudantes,j);

    char * t_guardar = malloc(sizeof(char)*4);
    t_guardar = tipo_de_guardar();

    if (strcmp(t_guardar,".txt")==0) {
        
        int temp = lista_estudantes[j].codigo;
        char * temp2 = malloc(sizeof(char)*SIZE_BUFFER); 
        sprintf(temp2, "%d", temp);
        char * info = strdup(temp2);
        info = strcat(info,"\t"); 

        info = strcat(info, strdup(lista_estudantes[j].nome));
        info = strcat(info,"\t"); 
    
        temp = lista_estudantes[j].data_n.dia;
        if (temp<DEZENA) {
            info = strcat(info,"0"); 
        }
        sprintf(temp2, "%d", temp);
        info = strcat(info,strdup(temp2));
        info = strcat(info,"-"); 

        temp = lista_estudantes[j].data_n.mes;
        if (temp<DEZENA) {
            info = strcat(info,"0"); 
        }
        sprintf(temp2, "%d", temp);
        info = strcat(info,strdup(temp2));
        info = strcat(info,"-"); 
     
        temp = lista_estudantes[j].data_n.ano;
        sprintf(temp2, "%d", temp);
        info = strcat(info,strdup(temp2));
        info = strcat(info,"\t"); 
  
        info = strcat(info, strdup(lista_estudantes[j].nacionalidade));
        info = strcat(info,"\t"); 
  
        temp = lista_estudantes[j].n_matriculas;
        sprintf(temp2, "%d", temp);
        info = strcat(info, strdup(temp2));
        info = strcat(info,"\t");
   
        temp = lista_estudantes[j].ects_concluidos;
        sprintf(temp2, "%d", temp);
        info = strcat(info,strdup(temp2));
        info = strcat(info,"\t"); 

        temp = lista_estudantes[j].ano_curso;
        sprintf(temp2, "%d", temp);
        info = strcat(info,strdup(temp2));
        info = strcat(info,"\t"); 
   
        float temp_f = lista_estudantes[j].media_atual;
        sprintf(temp2, "%.1f", temp_f);
        for (int k=0; k<strlen(temp2)+1; k++) {
            
            if (temp2[k] == ',') {
                temp2[k] = '.';
            }
        }
        info = strcat(info,strdup(temp2));
        info = strcat(info,"\n"); 
        
        temp = lista_estudantes[i].codigo;
        sprintf(temp2, "%d", temp);

        char * nome = strdup("aluno_alterado_"); //nome do ficheiro vai depender do codigo do aluno para evitar reescrever outros possíveis ficheiros
        nome = strcat(nome,temp2);
        nome = strcat(nome,".txt");
        txt_result_save_file(info, nome);
        txt_result_save_file(info, nome);

    }
    else if (strcmp(t_guardar,".cvs")==0) {
        char * header = "Codigo\tNome\tData Nascimento\tNacionalidade\tNumero Matriculas\tECTS Concluidos\tAno Curso\tMedia Atual\n";
        
        int temp = lista_estudantes[j].codigo;
        char * temp2 = malloc(sizeof(char)*SIZE_BUFFER); 
        sprintf(temp2, "%d", temp);
        char * info = strdup(temp2);
        info = strcat(info,"\t"); 

        info = strcat(info, strdup(lista_estudantes[j].nome));
        info = strcat(info,"\t"); 
    
        temp = lista_estudantes[j].data_n.dia;
        if (temp<DEZENA) {
            info = strcat(info,"0"); 
        }
        sprintf(temp2, "%d", temp);
        info = strcat(info,strdup(temp2));
        info = strcat(info,"-"); 

        temp = lista_estudantes[j].data_n.mes;
        if (temp<DEZENA) {
            info = strcat(info,"0"); 
        }
        sprintf(temp2, "%d", temp);
        info = strcat(info,strdup(temp2));
        info = strcat(info,"-"); 
     
        temp = lista_estudantes[j].data_n.ano;
        sprintf(temp2, "%d", temp);
        info = strcat(info,strdup(temp2));
        info = strcat(info,"\t"); 
  
        info = strcat(info, strdup(lista_estudantes[j].nacionalidade));
        info = strcat(info,"\t"); 
  
        temp = lista_estudantes[j].n_matriculas;
        sprintf(temp2, "%d", temp);
        info = strcat(info, strdup(temp2));
        info = strcat(info,"\t");
   
        temp = lista_estudantes[j].ects_concluidos;
        sprintf(temp2, "%d", temp);
        info = strcat(info,strdup(temp2));
        info = strcat(info,"\t"); 

        temp = lista_estudantes[j].ano_curso;
        sprintf(temp2, "%d", temp);
        info = strcat(info,strdup(temp2));
        info = strcat(info,"\t"); 
   
        float temp_f = lista_estudantes[j].media_atual;
        sprintf(temp2, "%.1f", temp_f);
        for (int k=0; k<strlen(temp2)+1; k++) {
            
            if (temp2[k] == ',') {
                temp2[k] = '.';
            }
        }
        info = strcat(info,strdup(temp2));
        info = strcat(info,"\n"); 
    
        temp = lista_estudantes[i].codigo;
        sprintf(temp2, "%d", temp);

        char * nome = strdup("aluno_alterado_");
        nome = strcat(nome,temp2);
        nome = strcat(nome,".cvs");
        cvs_result_save_file(header, info, nome);
        
    }
    
}





void mostrar_um_aluno(ALUNO *lista_estudantes,int posicao)
{
    fflush(stdin);
    //printf abstante simples, sem nada a comentar
    printf("Codigo: %d\n",lista_estudantes[posicao].codigo);
    printf("Nome: %s\n",lista_estudantes[posicao].nome);
    printf("Nacionalidade: %s\n",lista_estudantes[posicao].nacionalidade);
    printf("Data de nascimento: %d-%d-%d\n", lista_estudantes[posicao].data_n.dia, lista_estudantes[posicao].data_n.mes, lista_estudantes[posicao].data_n.ano);
    printf("Numero de matriculas: %i\n",lista_estudantes[posicao].n_matriculas);
    printf("Ano do curso: %i\n",lista_estudantes[posicao].ano_curso);
    printf("Media atual: %.1f\n",lista_estudantes[posicao].media_atual);
    printf("ECTS concluidos: %i\n\n",lista_estudantes[posicao].ects_concluidos);
    fflush(stdin);

}



void mostrar_toda_lista(ALUNO *lista_estudantes, int size_base) {

    for (int i=0,rep=0; i<size_base;i++) {
        if ((lista_estudantes[i].ocupado)==1) {
            if ((rep != 0) && (rep%3==0)) { //paginacao mostra dados de 3 em 3 alunos, de modo a evitar ter demasiada informacao no ecra de uma vez
                printf("Pagina seguinte ->");
                fflush(stdin);
                getchar();
                puts("");
                fflush(stdin);
            }
            
            mostrar_um_aluno(lista_estudantes,i);
            rep++;
        }
    }


    char * t_guardar = malloc(sizeof(char)*4);
    t_guardar = tipo_de_guardar();
    
    char * info;

    if (strcmp(t_guardar,".txt")==0) {
        
        for (int j=0, rep=0; j<size_base; j++) {
            if (lista_estudantes[j].ocupado==1) {
                
                int temp = lista_estudantes[j].codigo;
                char * temp2 = malloc(sizeof(char)*SIZE_BUFFER); 
                sprintf(temp2, "%d", temp);
                if (rep==0) {
                    info = strdup(temp2);
                }
                else {
                    info = strcat(info, temp2);
                }
                info = strcat(info,"\t"); 

                info = strcat(info, strdup(lista_estudantes[j].nome));
                info = strcat(info,"\t"); 
            
                temp = lista_estudantes[j].data_n.dia;
                if (temp<DEZENA) {
                    info = strcat(info,"0"); 
                }
                sprintf(temp2, "%d", temp);
                info = strcat(info,strdup(temp2));
                info = strcat(info,"-"); 

                temp = lista_estudantes[j].data_n.mes;
                if (temp<DEZENA) {
                    info = strcat(info,"0"); 
                }
                sprintf(temp2, "%d", temp);
                info = strcat(info,strdup(temp2));
                info = strcat(info,"-"); 
            
                temp = lista_estudantes[j].data_n.ano;
                sprintf(temp2, "%d", temp);
                info = strcat(info,strdup(temp2));
                info = strcat(info,"\t"); 
        
                info = strcat(info, strdup(lista_estudantes[j].nacionalidade));
                info = strcat(info,"\t"); 
        
                temp = lista_estudantes[j].n_matriculas;
                sprintf(temp2, "%d", temp);
                info = strcat(info, strdup(temp2));
                info = strcat(info,"\t");
        
                temp = lista_estudantes[j].ects_concluidos;
                sprintf(temp2, "%d", temp);
                info = strcat(info,strdup(temp2));
                info = strcat(info,"\t"); 

                temp = lista_estudantes[j].ano_curso;
                sprintf(temp2, "%d", temp);
                info = strcat(info,strdup(temp2));
                info = strcat(info,"\t"); 
        
                float temp_f = lista_estudantes[j].media_atual;
                sprintf(temp2, "%.1f", temp_f);
                for (int k=0; k<strlen(temp2)+1; k++) {
                    
                    if (temp2[k] == ',') {
                        temp2[k] = '.';
                    }
                }
                info = strcat(info,strdup(temp2));
                info = strcat(info,"\n"); 

                rep = 1;
            }
        }

        char * nome = "todos_alunos.txt";
        txt_result_save_file(info, nome);

    }
    else if (strcmp(t_guardar,".cvs")==0) {
        char * header = "Codigo\tNome\tData Nascimento\tNacionalidade\tNumero Matriculas\tECTS Concluidos\tAno Curso\tMedia Atual\n";
        char * info;

        for (int j=0, rep=0; j<size_base; j++) {
            if (lista_estudantes[j].ocupado==1) {
        
                int temp = lista_estudantes[j].codigo;
                char * temp2 = malloc(sizeof(char)*SIZE_BUFFER); 
                sprintf(temp2, "%d", temp);
            
                if (rep == 0) {
                    info = strdup(temp2);
                    rep = 1;
                }
                else {
                    info = strcat(info,strdup(temp2));
                }

                info = strcat(info,"\t"); 

                info = strcat(info, strdup(lista_estudantes[j].nome));
                info = strcat(info,"\t"); 
            
                temp = lista_estudantes[j].data_n.dia;
                if (temp<DEZENA) {
                    info = strcat(info,"0"); 
                }
                sprintf(temp2, "%d", temp);
                info = strcat(info,strdup(temp2));
                info = strcat(info,"-"); 

                temp = lista_estudantes[j].data_n.mes;
                if (temp<DEZENA) {
                    info = strcat(info,"0"); 
                }
                sprintf(temp2, "%d", temp);
                info = strcat(info,strdup(temp2));
                info = strcat(info,"-"); 
            
                temp = lista_estudantes[j].data_n.ano;
                sprintf(temp2, "%d", temp);
                info = strcat(info,strdup(temp2));
                info = strcat(info,"\t"); 
        
                info = strcat(info, strdup(lista_estudantes[j].nacionalidade));
                info = strcat(info,"\t"); 
        
                temp = lista_estudantes[j].n_matriculas;
                sprintf(temp2, "%d", temp);
                info = strcat(info, strdup(temp2));
                info = strcat(info,"\t");
        
                temp = lista_estudantes[j].ects_concluidos;
                sprintf(temp2, "%d", temp);
                info = strcat(info,strdup(temp2));
                info = strcat(info,"\t"); 

                temp = lista_estudantes[j].ano_curso;
                sprintf(temp2, "%d", temp);
                info = strcat(info,strdup(temp2));
                info = strcat(info,"\t"); 
        
                float temp_f = lista_estudantes[j].media_atual;
                sprintf(temp2, "%.1f", temp_f);
                for (int k=0; k<strlen(temp2)+1; k++) {
                    
                    if (temp2[k] == ',') {
                        temp2[k] = '.';
                    }
                }
                info = strcat(info,strdup(temp2));
                info = strcat(info,"\n"); 
            }
        }

        char * nome = "todos_alunos.cvs";
        cvs_result_save_file(header, info, nome);
        
    }
}



void mostrar_lista_por_ordem_apelido(ALUNO *lista_estudantes, int size_base)
{
    int * vet_organizado; //tem os índices da estrutura alunos organizados por ordem alfabetica dos apelidos
    vet_organizado = malloc(sizeof(int)*size_base);

    //cria o vetor que vai determinar a ordem alfabética dos apelidos
    for (int k=0;k<size_base;k++) {
        vet_organizado[k]=k;
    }
    
    //struct vai acumular todos os apelidos, pela mesma ordem dos estudantes na lista normal
    APELIDO *lista_apelidos;
    lista_apelidos = malloc(sizeof(APELIDO *) * size_base);

    for (int g=0; g<size_base;g++) {
        char * linha = strdup(lista_estudantes[g].nome); //copia nome
        char ** nome_comp = NULL;
        nome_comp = str_split(linha,' ', NULL); //divide o nome
        int componentes = 0; //determina a quantidade de subdivisoes do nome
        int i=0;

        while(nome_comp[i+1]!=0) { //procura a última subdivisão
            componentes++;
            i++;
        }
        lista_apelidos[g].apel = malloc(sizeof(char) * strlen(nome_comp[componentes])); 
        lista_apelidos[g].apel = nome_comp[componentes]; //guarda o apelido na estrutura
        printf("\n%s\n",lista_apelidos[g].apel);
    }


    int temp; //temporario, serve para trocar índices

    //compara os apelidos, mas guarda a sua ordem correta no vet_organizado
    //organiza por ordem decrescente
    //crescente nao funciona por algum motivo????
    //de notar que não faz conversão de maiúsculas para minúsculas e vice-versa
    for (int j=0; j<size_base-1;j++) {
        for(int i = 0; i<size_base-1; i++)
        {
            int pos1 = vet_organizado[i];
            int pos2 = vet_organizado[i+1];

            if(strcmp(lista_apelidos[pos1].apel, lista_apelidos[pos2].apel) < 0)
            {
                temp = vet_organizado[i];
                vet_organizado[i] = vet_organizado[i+1];
                vet_organizado[i+1] = temp;
            }
        }
    }

    //mostra os nomes por ordem crescente (alfabética) do apelido
    //como a lista está na ordem decrescente, também está o contador (para ser crescente)

    printf("\n%i\n",strcmp("Higgs","Costa"));
    for (int i=size_base-1, rep=0; i>=0; i--) {
        int posicao = vet_organizado[i]; //determina qual o índice a considerar
        if (lista_estudantes[posicao].ocupado==1) {
            if(rep!=0 && rep%DEZENA==0) { //paginação 10 a 10
                printf("Pagina seguinte ->");
                fflush(stdin);
                getchar();
                puts("");
                fflush(stdin);
            }
            printf("%s\n",lista_estudantes[posicao].nome);
            fflush(stdin);
            rep++;
        }
    }
    
    char * t_guardar = malloc(sizeof(char)*4);
    t_guardar = tipo_de_guardar();

    if (strcmp(t_guardar,".txt")==0) {
        
        char * info = NULL;

        for (int i=size_base-1, rep=0; i>=0; i--) {
            int posicao = vet_organizado[i];
            if (lista_estudantes[posicao].ocupado==1) {
                if (!info) {
                    info = strdup(lista_estudantes[posicao].nome);
                }
                else {
                    strcat (info,"\n");
                    info = strcat(info, lista_estudantes[posicao].nome);
                }
            }
        }
        char * nome = "resultado_alfabetico.txt";
        txt_result_save_file(info, nome);
    }
    else if (strcmp(t_guardar,".cvs")==0) {
        char * header = "Lista de estudantes por ordem alfabetica do apelido\n";
        char * info = NULL;

        for (int i=size_base-1, rep=0; i>=0; i--) {
            int posicao = vet_organizado[i];
            if (lista_estudantes[posicao].ocupado==1) {
                if (!info) {
                    info = strdup(lista_estudantes[posicao].nome);
                }
                else {
                    strcat (info,"\n");
                    info = strcat(info, lista_estudantes[posicao].nome);
                }
            }
        }

        char * nome = "resultado_alfabetico.cvs";
        cvs_result_save_file(header, info, nome);
        
    }

    

}




float media_mat(ALUNO *lista_estudantes,char *nacion, int size_base) {

    float media=0; //têm que estar em floats para fazer a divisao corretamente; media das matriculas, inicialmente a sua soma
    float num=0; //numero de individuos a considerar

    if (nacion == 0) { //se for geral
        for(int i=0;i<size_base;i++) {
            if (lista_estudantes[i].codigo==1) {
                media=media+(lista_estudantes[i].n_matriculas);
                num++;
            }
        }
        return (media/num); //calcula a média
    }
    else if (nacion != 0) { //se for de uma certa nacionalidade
        for(int i=0;i<size_base;i++) {
            if ((lista_estudantes[i].codigo==1) && (lista_estudantes[i].nacionalidade==nacion)) {
                media=media+(lista_estudantes[i].n_matriculas);
                num++;
            }
        }
        return (media/num); //calcula a média
    } 
}





void pesquisar(ALUNO *lista_estudantes,char *pesquisa, int size_base)
{
    int * lista_matches; //indica se encontrou a pesquisa num índice (1) ou se não (0)
    lista_matches = (int *) malloc(sizeof(int)*size_base);
    

    for (int s=0; s<size_base; s++) {
        lista_matches[s]=0;
    }


    for (int i=0; i<size_base; i++) {

        char * vetor = lista_estudantes[i].nome;  //define o vetor a comparar.
      
        for (int k=0; k<sizeof(*(lista_estudantes->nome)); k++) { //vai comparar elemento a elemento
           
            int repeticao=k; //indica se houve repeticao de procura no vetor do nome
           
            do {
                int posicao=0; //posicao no vetor
                int matches=0;

                //procura o primeiro elemento que seja igual ao primeiro elemento do vetor pesquisa
                while((vetor[posicao+repeticao]!=pesquisa[0]) && ((posicao+repeticao)<(strlen(vetor)))) {  //determina qual é o elemento inicial
                    posicao++;
                }
                
                //se não houver um elemento igual ao primeiro elemento da pesquisa, posicao==strlen(vetor)
                //caso contrário, vai verificar se os outros elementos são iguais
                if (posicao<strlen(vetor)) {

                    matches=1;

                    for (int j=1; (j<strlen(pesquisa)) && (posicao+repeticao+j)<strlen(vetor); j++) {
                        if (pesquisa[j]==vetor[posicao+repeticao+j]) {
                            matches++;
                        }
                    }
                    
                    //verifica se o número de elementos iguais consecutivos é igual ao número de elementos da pesquisa
                    if ((matches)==(strlen(pesquisa))) {
                        lista_matches[i]=1;//o vetor matches vai ser 1 nas posicoes correspondentes às posições dos nomes que contêm a pesquisa
                    }
                    else {
                        repeticao++;//caso não seja igual, verifica se algum outro segmento do nome coincide com o vetor pesquisa
                        //isto acontece através de começar a pesquisa do primeiro elemento em comum 1 espaço à frente do anterior
                    
                    }

                }
            }
            while ((strlen(vetor))-repeticao>strlen(pesquisa) && repeticao!=0); //enquanto o vetor ainda tiver espaço para conter a pesquisa, senão sai
         

        }

    }

    int rep=0;
    int g=0;
    for (int k=0; k<size_base; k++) {
        if (rep==0) {//no case de ser a primeira iteração
            printf("Resultado(s) da pesquisa <%s>:\n",pesquisa);
        }
        if (lista_matches[k]==1) { //se a pesquisa deu positivo
            if ((g != 0) && (g%3==0)) {
                printf("Pagina seguinte ->");
                fflush(stdin);
                getchar();
                puts("");
                fflush(stdin);
            }
            mostrar_um_aluno(lista_estudantes,k);
            g++;
        }
        rep++;
    }

    char * t_guardar = malloc(sizeof(char)*4);
    t_guardar = tipo_de_guardar();
    
    char * info;

    if (strcmp(t_guardar,".txt")==0) {
        
        for (int j=0, rep=0; j<size_base; j++) {
            if (lista_matches[j]==1) {
                
                int temp = lista_estudantes[j].codigo;
                char * temp2 = malloc(sizeof(char)*SIZE_BUFFER); 
                sprintf(temp2, "%d", temp);
                if (rep==0) {
                    info = strdup(temp2);
                }
                else {
                    info = strcat(info, temp2);
                }
                info = strcat(info,"\t"); 

                info = strcat(info, strdup(lista_estudantes[j].nome));
                info = strcat(info,"\t"); 
            
                temp = lista_estudantes[j].data_n.dia;
                if (temp<DEZENA) {
                    info = strcat(info,"0"); 
                }
                sprintf(temp2, "%d", temp);
                info = strcat(info,strdup(temp2));
                info = strcat(info,"-"); 

                temp = lista_estudantes[j].data_n.mes;
                if (temp<DEZENA) {
                    info = strcat(info,"0"); 
                }
                sprintf(temp2, "%d", temp);
                info = strcat(info,strdup(temp2));
                info = strcat(info,"-"); 
            
                temp = lista_estudantes[j].data_n.ano;
                sprintf(temp2, "%d", temp);
                info = strcat(info,strdup(temp2));
                info = strcat(info,"\t"); 
        
                info = strcat(info, strdup(lista_estudantes[j].nacionalidade));
                info = strcat(info,"\t"); 
        
                temp = lista_estudantes[j].n_matriculas;
                sprintf(temp2, "%d", temp);
                info = strcat(info, strdup(temp2));
                info = strcat(info,"\t");
        
                temp = lista_estudantes[j].ects_concluidos;
                sprintf(temp2, "%d", temp);
                info = strcat(info,strdup(temp2));
                info = strcat(info,"\t"); 

                temp = lista_estudantes[j].ano_curso;
                sprintf(temp2, "%d", temp);
                info = strcat(info,strdup(temp2));
                info = strcat(info,"\t"); 
        
                float temp_f = lista_estudantes[j].media_atual;
                sprintf(temp2, "%.1f", temp_f);
                for (int k=0; k<strlen(temp2)+1; k++) {
                    
                    if (temp2[k] == ',') {
                        temp2[k] = '.';
                    }
                }
                info = strcat(info,strdup(temp2));
                info = strcat(info,"\n"); 

                rep = 1;
            }
        }

        char * nome = strdup("resultado_pesquisa_");
        nome = strcat(nome,pesquisa);
        nome = strcat(nome,".txt");
        txt_result_save_file(info, nome);

    }
    else if (strcmp(t_guardar,".cvs")==0) {
        char * header = "Codigo\tNome\tData Nascimento\tNacionalidade\tNumero Matriculas\tECTS Concluidos\tAno Curso\tMedia Atual\n";
        char * info;

        for (int j=0, rep=0; j<size_base; j++) {
            if (lista_matches[j]==1) {
        
                int temp = lista_estudantes[j].codigo;
                char * temp2 = malloc(sizeof(char)*SIZE_BUFFER); 
                sprintf(temp2, "%d", temp);
            
                if (rep == 0) {
                    info = strdup(temp2);
                    rep = 1;
                }
                else {
                    info = strcat(info,strdup(temp2));
                }

                info = strcat(info,"\t"); 

                info = strcat(info, strdup(lista_estudantes[j].nome));
                info = strcat(info,"\t"); 
            
                temp = lista_estudantes[j].data_n.dia;
                if (temp<DEZENA) {
                    info = strcat(info,"0"); 
                }
                sprintf(temp2, "%d", temp);
                info = strcat(info,strdup(temp2));
                info = strcat(info,"-"); 

                temp = lista_estudantes[j].data_n.mes;
                if (temp<DEZENA) {
                    info = strcat(info,"0"); 
                }
                sprintf(temp2, "%d", temp);
                info = strcat(info,strdup(temp2));
                info = strcat(info,"-"); 
            
                temp = lista_estudantes[j].data_n.ano;
                sprintf(temp2, "%d", temp);
                info = strcat(info,strdup(temp2));
                info = strcat(info,"\t"); 
        
                info = strcat(info, strdup(lista_estudantes[j].nacionalidade));
                info = strcat(info,"\t"); 
        
                temp = lista_estudantes[j].n_matriculas;
                sprintf(temp2, "%d", temp);
                info = strcat(info, strdup(temp2));
                info = strcat(info,"\t");
        
                temp = lista_estudantes[j].ects_concluidos;
                sprintf(temp2, "%d", temp);
                info = strcat(info,strdup(temp2));
                info = strcat(info,"\t"); 

                temp = lista_estudantes[j].ano_curso;
                sprintf(temp2, "%d", temp);
                info = strcat(info,strdup(temp2));
                info = strcat(info,"\t"); 
        
                float temp_f = lista_estudantes[j].media_atual;
                sprintf(temp2, "%.1f", temp_f);
                for (int k=0; k<strlen(temp2)+1; k++) {
                    
                    if (temp2[k] == ',') {
                        temp2[k] = '.';
                    }
                }
                info = strcat(info,strdup(temp2));
                info = strcat(info,"\n"); 
            }
        }

        char * nome = strdup("resultado_pesquisa_");
        nome = strcat(nome,pesquisa);
        nome = strcat(nome,".cvs");
        cvs_result_save_file(header, info, nome);
        
    }

    
}



int mostrar_alunos_entre_medias(ALUNO *lista_estudantes,float x,float y, int size_base) 
{
    int n_est_com_media=0;//número de estudantes com média entre estes valores

    //determinar o maior e menor valor
    float max=x;
    float min=0;
    if (max>y) {
        min=y;
    }
    else {
        max=y;
        min=x;
    }

    //Mostrar os alunos com médias entre estes 2 valores
    int i=0;//elemento de paginação, determina quantas iterações foram mostradas ao utilizador
    int n_result = 0; //diz se houve resultados ou se não
    int n_alu = 0; //número de alunos considerados

    for (int k=0;k<size_base;k++) {
        if ((lista_estudantes[k].ocupado==1) && (lista_estudantes[k].media_atual>=min) && (lista_estudantes[k].media_atual<=max)) {
            if ((i != 0) && (i%3==0)) {//elemento de paginação, mostra em blocos de 3
                printf("Pagina seguinte ->");
                fflush(stdin);
                getchar();
                puts("");
                fflush(stdin);
            }
            mostrar_um_aluno(lista_estudantes,k);
            n_est_com_media++;
            i++;
        }
        else n_result++;
        
        n_alu++;
    }

    if (n_result==n_alu) { //verifica se não houve resultados
        printf("Nao ha resultados no intervalo de medias %.2f - %.2f.\n",min,max);
    }
    else { //se houve, oferece para guardar
        char * t_guardar = malloc(sizeof(char)*4);
        t_guardar = tipo_de_guardar();
        
        char * info;

        if (strcmp(t_guardar,".txt")==0) {
            
            for (int j=0, rep=0; j<size_base; j++) {
                if (lista_estudantes[j].ocupado==1 && (lista_estudantes[j].media_atual>=min) && (lista_estudantes[j].media_atual<=max)) {
                    
                    int temp = lista_estudantes[j].codigo;
                    char * temp2 = malloc(sizeof(char)*SIZE_BUFFER); 
                    sprintf(temp2, "%d", temp);
                    if (rep==0) {
                        info = strdup(temp2);
                    }
                    else {
                        info = strcat(info, temp2);
                    }
                    info = strcat(info,"\t"); 

                    info = strcat(info, strdup(lista_estudantes[j].nome));
                    info = strcat(info,"\t"); 
                
                    temp = lista_estudantes[j].data_n.dia;
                    if (temp<DEZENA) {
                        info = strcat(info,"0"); 
                    }
                    sprintf(temp2, "%d", temp);
                    info = strcat(info,strdup(temp2));
                    info = strcat(info,"-"); 

                    temp = lista_estudantes[j].data_n.mes;
                    if (temp<DEZENA) {
                        info = strcat(info,"0"); 
                    }
                    sprintf(temp2, "%d", temp);
                    info = strcat(info,strdup(temp2));
                    info = strcat(info,"-"); 
                
                    temp = lista_estudantes[j].data_n.ano;
                    sprintf(temp2, "%d", temp);
                    info = strcat(info,strdup(temp2));
                    info = strcat(info,"\t"); 
            
                    info = strcat(info, strdup(lista_estudantes[j].nacionalidade));
                    info = strcat(info,"\t"); 
            
                    temp = lista_estudantes[j].n_matriculas;
                    sprintf(temp2, "%d", temp);
                    info = strcat(info, strdup(temp2));
                    info = strcat(info,"\t");
            
                    temp = lista_estudantes[j].ects_concluidos;
                    sprintf(temp2, "%d", temp);
                    info = strcat(info,strdup(temp2));
                    info = strcat(info,"\t"); 

                    temp = lista_estudantes[j].ano_curso;
                    sprintf(temp2, "%d", temp);
                    info = strcat(info,strdup(temp2));
                    info = strcat(info,"\t"); 
            
                    float temp_f = lista_estudantes[j].media_atual;
                    sprintf(temp2, "%.1f", temp_f);
                    for (int k=0; k<strlen(temp2)+1; k++) {
                        
                        if (temp2[k] == ',') {
                            temp2[k] = '.';
                        }
                    }
                    info = strcat(info,strdup(temp2));
                    info = strcat(info,"\n"); 

                    rep = 1;
                }
            }

            char * nome = strdup("alunos_entre_medias_");
            float temp = min;
            char * temp2;
            sprintf(temp2, "%f", temp);
            nome = strcat(nome,temp2);
            nome = strcat(nome,"_");
            temp = max;
            sprintf(temp2, "%f", temp);
            nome = strcat(nome,temp2);
            nome = strcat(nome,".txt");
            txt_result_save_file(info, nome);

        }
        else if (strcmp(t_guardar,".cvs")==0) {
            char * header = "Codigo\tNome\tData Nascimento\tNacionalidade\tNumero Matriculas\tECTS Concluidos\tAno Curso\tMedia Atual\n";
            char * info;

            for (int j=0, rep=0; j<size_base; j++) {
                if (lista_estudantes[j].ocupado==1 && (lista_estudantes[j].media_atual>=min) && (lista_estudantes[j].media_atual<=max)) {
            
                    int temp = lista_estudantes[j].codigo;
                    char * temp2 = malloc(sizeof(char)*SIZE_BUFFER); 
                    sprintf(temp2, "%d", temp);
                
                    if (rep == 0) {
                        info = strdup(temp2);
                        rep = 1;
                    }
                    else {
                        info = strcat(info,strdup(temp2));
                    }

                    info = strcat(info,"\t"); 

                    info = strcat(info, strdup(lista_estudantes[j].nome));
                    info = strcat(info,"\t"); 
                
                    temp = lista_estudantes[j].data_n.dia;
                    if (temp<DEZENA) {
                        info = strcat(info,"0"); 
                    }
                    sprintf(temp2, "%d", temp);
                    info = strcat(info,strdup(temp2));
                    info = strcat(info,"-"); 

                    temp = lista_estudantes[j].data_n.mes;
                    if (temp<DEZENA) {
                        info = strcat(info,"0"); 
                    }
                    sprintf(temp2, "%d", temp);
                    info = strcat(info,strdup(temp2));
                    info = strcat(info,"-"); 
                
                    temp = lista_estudantes[j].data_n.ano;
                    sprintf(temp2, "%d", temp);
                    info = strcat(info,strdup(temp2));
                    info = strcat(info,"\t"); 
            
                    info = strcat(info, strdup(lista_estudantes[j].nacionalidade));
                    info = strcat(info,"\t"); 
            
                    temp = lista_estudantes[j].n_matriculas;
                    sprintf(temp2, "%d", temp);
                    info = strcat(info, strdup(temp2));
                    info = strcat(info,"\t");
            
                    temp = lista_estudantes[j].ects_concluidos;
                    sprintf(temp2, "%d", temp);
                    info = strcat(info,strdup(temp2));
                    info = strcat(info,"\t"); 

                    temp = lista_estudantes[j].ano_curso;
                    sprintf(temp2, "%d", temp);
                    info = strcat(info,strdup(temp2));
                    info = strcat(info,"\t"); 
            
                    float temp_f = lista_estudantes[j].media_atual;
                    sprintf(temp2, "%.1f", temp_f);
                    for (int k=0; k<strlen(temp2)+1; k++) {
                        
                        if (temp2[k] == ',') {
                            temp2[k] = '.';
                        }
                    }
                    info = strcat(info,strdup(temp2));
                    info = strcat(info,"\n"); 
                }
            }

            char * nome = strdup("alunos_entre_medias_");
            float temp = min;
            char * temp2;
            sprintf(temp2, "%f", temp);
            nome = strcat(nome,temp2);
            nome = strcat(nome,"_");
            temp = max;
            sprintf(temp2, "%f", temp);
            nome = strcat(nome,temp2);
            nome = strcat(nome,".cvs");
            cvs_result_save_file(header, info, nome);
            
        }
    }

    return n_est_com_media;
}



int n_est_finalistas(ALUNO * lista_estudantes, int size_base) {
    int n_fin=0;//vai guardar o número de alunos que é finalista

    //para ser considerado finalista, o aluno tem de ter pelo menos 154 ects
    for (int i=0;i<size_base;i++) {
        if ((lista_estudantes[i].ocupado==1) && (lista_estudantes[i].ects_concluidos>=154)) {
            n_fin++;
        }
    }

    return n_fin;//retorna o número de estudantes finalistas
}



void listar_est_entre_data_n(ALUNO * lista_estudantes, char *data_1 , char * data_2, int size_base)
{
    char * data_3 = strdup(data_1); //copia as strings para evitar erros
    char * data_4 = strdup(data_2);
    
    DATA_NAS data_sup;//data maior
    DATA_NAS data_inf;//data menor

    DATA_NAS data_prim;//primeira data fornecida, data_1, organizada em struct
    DATA_NAS data_seg;//segunda data fornecida, data_2, organizada em struct

    //Coloca as datas fornecidas pelo utilizador na struct do tipo DATA_NAS para fácil comparação
    //com as datas dos alunos
    char *dnp = data_1;//ponteiro de data_1
    char **ptr_dnp = str_split(dnp, '-', NULL);//vai separar as datas da carater '-'
    data_prim.dia= atoi(strdup(ptr_dnp[0]));//alocação de cada elemento no campo adequado: dia, mes e ano
    data_prim.mes= atoi(strdup(ptr_dnp[1]));
    data_prim.ano= atoi(strdup(ptr_dnp[2]));

    //de forma semelhante:
    char *dns = data_2;
    char **ptr_dns = str_split(dns, '-', NULL);
    data_seg.dia= atoi(strdup(ptr_dns[0]));
    data_seg.mes= atoi(strdup(ptr_dns[1]));
    data_seg.ano= atoi(strdup(ptr_dns[2]));


    //Determina qual a data superior e a data inferior por comparação
    //comparação por anos
    if ((data_prim.ano)>(data_seg.ano)) {
        data_sup = data_prim;
        data_inf = data_seg;
    }
    else if ((data_seg.ano)>(data_prim.ano)) {
        data_sup = data_seg;
        data_inf = data_prim;
    }
    else if ((data_seg.ano)==(data_prim.ano)) {
        //comparação por meses
        if ((data_prim.mes)>(data_seg.mes)) {
            data_sup = data_prim;
            data_inf = data_seg;
        }
        else if ((data_seg.mes)>(data_prim.mes)) {
            data_sup = data_seg;
            data_inf = data_prim;
        }
        else if ((data_prim.mes)==(data_seg.mes)) {
            //comparação por dias
            if ((data_prim.dia)>(data_seg.dia)) {
            data_sup = data_prim;
            data_inf = data_seg;
            }
            else if ((data_seg.dia)>(data_prim.dia)) {
                data_sup = data_seg;
                data_inf = data_prim;
            }
        }
    }

    int * lista_matches = (int *) calloc(size_base, sizeof(int)); //vai indicar se os alunos nos índices são hits ou se não
    int * lista_preliminary_matches = (int *) calloc(size_base, sizeof(int)); //inicializa tudo a 0

    //Efetua a comparação da data dos estudantes com o intervalo definido
    //Nacionalidades são tidas em conta noutro ciclo

    for (int k=0;k<size_base;k++) {
        if (lista_estudantes[k].ocupado==1) {
            //Compara os anos inicialmente
            if ((lista_estudantes[k].data_n.ano>data_inf.ano) && (lista_estudantes[k].data_n.ano<data_sup.ano)) {
                lista_preliminary_matches[k]=1;
            }
            else if (lista_estudantes[k].data_n.ano==data_inf.ano) {
                //No caso dos anos serem os extremos, compara os meses.
                if ((lista_estudantes[k].data_n.mes>data_inf.mes) && (lista_estudantes[k].data_n.mes<data_sup.mes)) {
                    lista_preliminary_matches[k]=1;
                }
                //No casos dos meses serem os extremos, compara os dias.
                else if (lista_estudantes[k].data_n.mes==data_inf.mes) { 
                    if ((lista_estudantes[k].data_n.dia>=data_inf.dia) && (lista_estudantes[k].data_n.dia<=data_sup.dia)) {
                        lista_preliminary_matches[k]=1;
                    }
                }
                else if (lista_estudantes[k].data_n.mes==data_sup.mes) {
                    if ((lista_estudantes[k].data_n.dia>=data_inf.dia) && (lista_estudantes[k].data_n.dia<=data_sup.dia)) {
                        lista_preliminary_matches[k]=1;
                    }
                }
            }
            //Mesma situação que o anterior, mas caso extremo oposto
            else if (lista_estudantes[k].data_n.ano==data_sup.ano) {
                if ((lista_estudantes[k].data_n.mes>data_inf.mes) && (lista_estudantes[k].data_n.mes<data_sup.mes)) {
                    lista_preliminary_matches[k]=1;
                }
                else if (lista_estudantes[k].data_n.mes==data_inf.mes) { 
                    if ((lista_estudantes[k].data_n.dia>=data_inf.dia) && (lista_estudantes[k].data_n.dia<=data_sup.dia)) {
                        lista_preliminary_matches[k]=1;
                    }
                }
                else if (lista_estudantes[k].data_n.mes==data_sup.mes) {
                    if ((lista_estudantes[k].data_n.dia>=data_inf.dia) && (lista_estudantes[k].data_n.dia<=data_sup.dia)) {
                        lista_preliminary_matches[k]=1;
                    }
                }

            }
        }
    }

    //nacionalidades permitidas
    char * nacio1;
    char * nacio2;
    char * nacio3;
    char * nacio4;
    char * nacio5;
    int n_resultados = 0; //numero de resultados para parte final


    //Determina as nacionalidades: as cinco primeiras encontradas.
    for (int k=0,repeat=0;k<size_base;k++) {
        if (lista_preliminary_matches[k]==1) {
            if (repeat==0) {
                nacio1 = strdup(lista_estudantes[k].nacionalidade);
                lista_matches[k]=1;
                repeat++;
                n_resultados++;
            }
            else if (repeat==1) {
                if (strcmp(lista_estudantes[k].nacionalidade,nacio1)==0) {
                    lista_matches[k]=1;
                    n_resultados++;
                }
                else {
                    nacio2=strdup(lista_estudantes[k].nacionalidade);
                    lista_matches[k]=1;
                    repeat++;
                    n_resultados++;
                }
            }
            else if (repeat==2) {
                if ((strcmp(lista_estudantes[k].nacionalidade,nacio1)==0) || ((strcmp(lista_estudantes[k].nacionalidade,nacio2)==0))) {
                    lista_matches[k]=1;
                    n_resultados++;
                }
                else {
                    nacio3=strdup(lista_estudantes[k].nacionalidade);
                    lista_matches[k]=1;
                    repeat++;
                    n_resultados++;
                }
            }
            else if (repeat==3) {
                if ((strcmp(lista_estudantes[k].nacionalidade,nacio1)==0) || ((strcmp(lista_estudantes[k].nacionalidade,nacio2)==0)) || ((strcmp(lista_estudantes[k].nacionalidade,nacio3)==0))) {
                    lista_matches[k]=1;
                    n_resultados++;
                }
                else {
                    nacio4=strdup(lista_estudantes[k].nacionalidade);
                    lista_matches[k]=1;
                    repeat++;
                    n_resultados++;
                }
            }
            else if (repeat==4) {
                if ((strcmp(lista_estudantes[k].nacionalidade,nacio1)==0) || ((strcmp(lista_estudantes[k].nacionalidade,nacio2)==0)) || ((strcmp(lista_estudantes[k].nacionalidade,nacio3)==0)) || ((strcmp(lista_estudantes[k].nacionalidade,nacio4)==0))) {
                    lista_matches[k]=1;
                    n_resultados++;
                }
                else {
                    nacio5=strdup(lista_estudantes[k].nacionalidade);
                    lista_matches[k]=1;
                    repeat++;
                    n_resultados++;
                }
            }
            else if (repeat>4) {
                if ((strcmp(lista_estudantes[k].nacionalidade,nacio1)==0) || ((strcmp(lista_estudantes[k].nacionalidade,nacio2)==0)) || ((strcmp(lista_estudantes[k].nacionalidade,nacio3)==0)) || ((strcmp(lista_estudantes[k].nacionalidade,nacio4)==0)) || ((strcmp(lista_estudantes[k].nacionalidade,nacio5)==0))) {
                    lista_matches[k]=1;
                    n_resultados++;
                }
            }

        }
    }

    //Faz o display dos resultados
    printf("\nLista dos alunos com datas de nascimento entre %s e %s:",data_3,data_4);
    for (int k=0;k<size_base;k++) {

        if (n_resultados==0) {
            printf("\nNao ha alunos com datas de nascimento entre %s e %s.\n",data_3,data_4);
            break;
        }
        else {
            if (lista_matches[k]==1) {
                printf("\n%s",lista_estudantes[k].nome);
            }

            if (n_resultados!=0 && n_resultados%11==0) {//elemento de paginação, organizado em blocos de 3 outputs
                printf("\nPagina seguinte ->");
                fflush(stdin);
                getchar();
                puts("");
                fflush(stdin);
            }
        }
    }

    if (n_resultados!=0) {
        puts("");
        char * t_guardar = malloc(sizeof(char)*4);
        t_guardar = tipo_de_guardar();
        
        char * info;

        if (strcmp(t_guardar,".txt")==0) {
            
            for (int j=0, rep=0; j<size_base; j++) {
                if (lista_matches[j]==1) {
                    
                    int temp = lista_estudantes[j].codigo;
                    char * temp2 = malloc(sizeof(char)*SIZE_BUFFER); 
                    sprintf(temp2, "%d", temp);
                    if (rep==0) {
                        info = strdup(temp2);
                    }
                    else {
                        info = strcat(info, temp2);
                    }
                    info = strcat(info,"\t"); 

                    info = strcat(info, strdup(lista_estudantes[j].nome));
                    info = strcat(info,"\t"); 
                
                    temp = lista_estudantes[j].data_n.dia;
                    if (temp<DEZENA) {
                        info = strcat(info,"0"); 
                    }
                    sprintf(temp2, "%d", temp);
                    info = strcat(info,strdup(temp2));
                    info = strcat(info,"-"); 

                    temp = lista_estudantes[j].data_n.mes;
                    if (temp<DEZENA) {
                        info = strcat(info,"0"); 
                    }
                    sprintf(temp2, "%d", temp);
                    info = strcat(info,strdup(temp2));
                    info = strcat(info,"-"); 
                
                    temp = lista_estudantes[j].data_n.ano;
                    sprintf(temp2, "%d", temp);
                    info = strcat(info,strdup(temp2));
                    info = strcat(info,"\t"); 
            
                    info = strcat(info, strdup(lista_estudantes[j].nacionalidade));
                    info = strcat(info,"\t"); 
            
                    temp = lista_estudantes[j].n_matriculas;
                    sprintf(temp2, "%d", temp);
                    info = strcat(info, strdup(temp2));
                    info = strcat(info,"\t");
            
                    temp = lista_estudantes[j].ects_concluidos;
                    sprintf(temp2, "%d", temp);
                    info = strcat(info,strdup(temp2));
                    info = strcat(info,"\t"); 

                    temp = lista_estudantes[j].ano_curso;
                    sprintf(temp2, "%d", temp);
                    info = strcat(info,strdup(temp2));
                    info = strcat(info,"\t"); 
            
                    float temp_f = lista_estudantes[j].media_atual;
                    sprintf(temp2, "%.1f", temp_f);
                    for (int k=0; k<strlen(temp2)+1; k++) {
                        
                        if (temp2[k] == ',') {
                            temp2[k] = '.';
                        }
                    }
                    info = strcat(info,strdup(temp2));
                    info = strcat(info,"\n"); 

                    rep = 1;
                }
            }

            char * nome = strdup("alunos_com_datas_nascimento_entre"); //evita reescrever ficheiros
            nome = strcat(nome,data_3);
            nome = strcat(nome,"_");
            nome = strcat(nome,data_4);
            nome = strcat(nome,".txt");
            txt_result_save_file(info, nome);

        }
        else if (strcmp(t_guardar,".cvs")==0) {
            char * header = "Codigo\tNome\tData Nascimento\tNacionalidade\tNumero Matriculas\tECTS Concluidos\tAno Curso\tMedia Atual\n";
            char * info;

            for (int j=0, rep=0; j<size_base; j++) {
                if (lista_matches[j]==1) {
            
                    int temp = lista_estudantes[j].codigo;
                    char * temp2 = malloc(sizeof(char)*SIZE_BUFFER); 
                    sprintf(temp2, "%d", temp);
                
                    if (rep == 0) {
                        info = strdup(temp2);
                        rep = 1;
                    }
                    else {
                        info = strcat(info,strdup(temp2));
                    }

                    info = strcat(info,"\t"); 

                    info = strcat(info, strdup(lista_estudantes[j].nome));
                    info = strcat(info,"\t"); 
                
                    temp = lista_estudantes[j].data_n.dia;
                    if (temp<DEZENA) {
                        info = strcat(info,"0"); 
                    }
                    sprintf(temp2, "%d", temp);
                    info = strcat(info,strdup(temp2));
                    info = strcat(info,"-"); 

                    temp = lista_estudantes[j].data_n.mes;
                    if (temp<DEZENA) {
                        info = strcat(info,"0"); 
                    }
                    sprintf(temp2, "%d", temp);
                    info = strcat(info,strdup(temp2));
                    info = strcat(info,"-"); 
                
                    temp = lista_estudantes[j].data_n.ano;
                    sprintf(temp2, "%d", temp);
                    info = strcat(info,strdup(temp2));
                    info = strcat(info,"\t"); 
            
                    info = strcat(info, strdup(lista_estudantes[j].nacionalidade));
                    info = strcat(info,"\t"); 
            
                    temp = lista_estudantes[j].n_matriculas;
                    sprintf(temp2, "%d", temp);
                    info = strcat(info, strdup(temp2));
                    info = strcat(info,"\t");
            
                    temp = lista_estudantes[j].ects_concluidos;
                    sprintf(temp2, "%d", temp);
                    info = strcat(info,strdup(temp2));
                    info = strcat(info,"\t"); 

                    temp = lista_estudantes[j].ano_curso;
                    sprintf(temp2, "%d", temp);
                    info = strcat(info,strdup(temp2));
                    info = strcat(info,"\t"); 
            
                    float temp_f = lista_estudantes[j].media_atual;
                    sprintf(temp2, "%.1f", temp_f);
                    for (int k=0; k<strlen(temp2)+1; k++) {
                        
                        if (temp2[k] == ',') {
                            temp2[k] = '.';
                        }
                    }
                    info = strcat(info,strdup(temp2));
                    info = strcat(info,"\n"); 
                }
            }

            char * nome = strdup("alunos_com_datas_nascimento_entre");
            nome = strcat(nome,data_3);
            nome = strcat(nome,"_");
            nome = strcat(nome,data_4);
            nome = strcat(nome,".cvs");
            cvs_result_save_file(header, info, nome);
            
        }
    }

    
}


int estudantes_risco_prescrever(ALUNO * lista_estudantes, int size_base) {
    
    //vetor cujas posicoes com 1 correspondem às posicoes dos alunos em risco de prescricao na struct lista_estudantes
    int * lista_prescricao = malloc(sizeof(int) * size_base);
    for (int i=0; i<size_base; i++) {
        lista_prescricao[i]=0;//inicializa a 0: significa que o aluno na posicao i não está em risco de prescrição
    }

    
    int num=0; //número de estudantes em risco de prescrição
    for (int i=0;i<size_base;i++) {
        
        if (lista_estudantes[i].ocupado==1) {
            //3 matrículas e menos de 60 ects
            if ((lista_estudantes[i].n_matriculas>=3) && (lista_estudantes[i].ects_concluidos<60)) {
                lista_prescricao[i]=1;//posição com valor 1: indica risco de prescrição
                num++;//aumenta o nº de estudantes em risco
            }
            //4 matrículas e menos de 120 ects
            else if ((lista_estudantes[i].n_matriculas>=4) && (lista_estudantes[i].ects_concluidos<120)) {
                lista_prescricao[i]=1;
                num++;
            }
            //mais de 5 matrículas e não finalistas (pelo menos 154 ects)
            else if ((lista_estudantes[i].n_matriculas>5) && (lista_estudantes[i].ects_concluidos<154)) {
                lista_prescricao[i]=1;
                num++;
            }
        }
    }

    int rep=0;//para paginacao
    if (num!=0) {//no caso de haver pelo menos 1 estudante em risco
        for (int i=0;i<size_base;i++) {
            if (lista_prescricao[i]==1) {
                if (rep==0) {//na primeira iteração vai ter este cabeçalho
                    printf("Lista de alunos em risco de prescricao:\n");
                }
                else if(rep!=0 && rep%DEZENA==0) {//paginação, mostra nomes em blocos de 10
                    printf("Pagina seguinte ->");
                    fflush(stdin);
                    getchar();
                    puts("");
                    fflush(stdin);
                }
                printf("%s\n",lista_estudantes[i].nome);//mostra o nome do estudante em risco
            }
        }

        char * t_guardar = malloc(sizeof(char)*4);
        t_guardar = tipo_de_guardar();
        
        char * info;

        if (strcmp(t_guardar,".txt")==0) {
            
            for (int j=0, rep=0; j<size_base; j++) {
                if (lista_prescricao[j]==1) {
                    
                    int temp = lista_estudantes[j].codigo;
                    char * temp2 = malloc(sizeof(char)*SIZE_BUFFER); 
                    sprintf(temp2, "%d", temp);
                    if (rep==0) {
                        info = strdup(temp2);
                    }
                    else {
                        info = strcat(info, temp2);
                    }
                    info = strcat(info,"\t"); 

                    info = strcat(info, strdup(lista_estudantes[j].nome));
                    info = strcat(info,"\t"); 
                
                    temp = lista_estudantes[j].data_n.dia;
                    if (temp<DEZENA) {
                        info = strcat(info,"0"); 
                    }
                    sprintf(temp2, "%d", temp);
                    info = strcat(info,strdup(temp2));
                    info = strcat(info,"-"); 

                    temp = lista_estudantes[j].data_n.mes;
                    if (temp<DEZENA) {
                        info = strcat(info,"0"); 
                    }
                    sprintf(temp2, "%d", temp);
                    info = strcat(info,strdup(temp2));
                    info = strcat(info,"-"); 
                
                    temp = lista_estudantes[j].data_n.ano;
                    sprintf(temp2, "%d", temp);
                    info = strcat(info,strdup(temp2));
                    info = strcat(info,"\t"); 
            
                    info = strcat(info, strdup(lista_estudantes[j].nacionalidade));
                    info = strcat(info,"\t"); 
            
                    temp = lista_estudantes[j].n_matriculas;
                    sprintf(temp2, "%d", temp);
                    info = strcat(info, strdup(temp2));
                    info = strcat(info,"\t");
            
                    temp = lista_estudantes[j].ects_concluidos;
                    sprintf(temp2, "%d", temp);
                    info = strcat(info,strdup(temp2));
                    info = strcat(info,"\t"); 

                    temp = lista_estudantes[j].ano_curso;
                    sprintf(temp2, "%d", temp);
                    info = strcat(info,strdup(temp2));
                    info = strcat(info,"\t"); 
            
                    float temp_f = lista_estudantes[j].media_atual;
                    sprintf(temp2, "%.1f", temp_f);
                    for (int k=0; k<strlen(temp2)+1; k++) {
                        
                        if (temp2[k] == ',') {
                            temp2[k] = '.';
                        }
                    }
                    info = strcat(info,strdup(temp2));
                    info = strcat(info,"\n"); 

                    rep = 1;
                }
            }

            char * nome = "alunos_em_risco_precricao.txt";
            txt_result_save_file(info, nome);

        }
        else if (strcmp(t_guardar,".cvs")==0) {
            char * header = "Codigo\tNome\tData Nascimento\tNacionalidade\tNumero Matriculas\tECTS Concluidos\tAno Curso\tMedia Atual\n";
            char * info;

            for (int j=0, rep=0; j<size_base; j++) {
                if (lista_prescricao[j]==1) {
            
                    int temp = lista_estudantes[j].codigo;
                    char * temp2 = malloc(sizeof(char)*SIZE_BUFFER); 
                    sprintf(temp2, "%d", temp);
                
                    if (rep == 0) {
                        info = strdup(temp2);
                        rep = 1;
                    }
                    else {
                        info = strcat(info,strdup(temp2));
                    }

                    info = strcat(info,"\t"); 

                    info = strcat(info, strdup(lista_estudantes[j].nome));
                    info = strcat(info,"\t"); 
                
                    temp = lista_estudantes[j].data_n.dia;
                    if (temp<DEZENA) {
                        info = strcat(info,"0"); 
                    }
                    sprintf(temp2, "%d", temp);
                    info = strcat(info,strdup(temp2));
                    info = strcat(info,"-"); 

                    temp = lista_estudantes[j].data_n.mes;
                    if (temp<DEZENA) {
                        info = strcat(info,"0"); 
                    }
                    sprintf(temp2, "%d", temp);
                    info = strcat(info,strdup(temp2));
                    info = strcat(info,"-"); 
                
                    temp = lista_estudantes[j].data_n.ano;
                    sprintf(temp2, "%d", temp);
                    info = strcat(info,strdup(temp2));
                    info = strcat(info,"\t"); 
            
                    info = strcat(info, strdup(lista_estudantes[j].nacionalidade));
                    info = strcat(info,"\t"); 
            
                    temp = lista_estudantes[j].n_matriculas;
                    sprintf(temp2, "%d", temp);
                    info = strcat(info, strdup(temp2));
                    info = strcat(info,"\t");
            
                    temp = lista_estudantes[j].ects_concluidos;
                    sprintf(temp2, "%d", temp);
                    info = strcat(info,strdup(temp2));
                    info = strcat(info,"\t"); 

                    temp = lista_estudantes[j].ano_curso;
                    sprintf(temp2, "%d", temp);
                    info = strcat(info,strdup(temp2));
                    info = strcat(info,"\t"); 
            
                    float temp_f = lista_estudantes[j].media_atual;
                    sprintf(temp2, "%.1f", temp_f);
                    for (int k=0; k<strlen(temp2)+1; k++) {
                        
                        if (temp2[k] == ',') {
                            temp2[k] = '.';
                        }
                    }
                    info = strcat(info,strdup(temp2));
                    info = strcat(info,"\n"); 
                }
            }

            char * nome = "alunos_em_risco_prescricao.cvs";
            cvs_result_save_file(header, info, nome);
            
        }
    }

    else {//no caso de ser tudo a 0
        printf("Nao ha alunos em risco de prescricao!\n");
    }

    puts("");

    return num;//retorna o número de estudantes em risco
}



float * media_idades_nacionalidade(ALUNO * lista_estudantes, char * nacio, float ano_atual, int size_base)
{
    //vetor vai organizar as médias das idades da nacionalidade fornecida pelo ano de curso
    float * media_por_nac_por_ano = malloc(sizeof(float)*5);

    for (int j=1; j<6; j++) { //determina qual o ano de curso (e posicao no vetor) estamos a avaliar
        float n_ele = 0; //em float para fazer divisão corretamente; numero de elementos
        float soma = 0; //soma dos valores

        if (strcmp(nacio,"0")!=0) {
            for (int i=0; i<size_base;i++) {
                //procura os alunos que obedecem a todas as condicoes:
                //nacionalidade, ano de curso correto, existência na base de dados
                if ((lista_estudantes[i].ocupado == 1) && (strcmp(lista_estudantes[i].nacionalidade,nacio)==0) && (lista_estudantes[i].ano_curso == j)) {
                    n_ele++;
                    float idade = ano_atual - (lista_estudantes[i].data_n.ano); //idade é obtida de forma muito simplificada através do ano de nascimento.
                    //ignoram-se as outras componentes desta data por agora
                    //poderia incorporar-se o cálculo com meses e dias, mas seria demasido complicado ter que arredondar e obter a data do sistema
                    soma = soma + idade;
                }
            }
            if (n_ele!=0) {
                media_por_nac_por_ano[j-1] = (soma/n_ele); //cálculo da média, armazena no vetor
            }
            else { //para evitar possíveis divisões por zero
                media_por_nac_por_ano[j-1] = 0;
            }
        }
        else { //mesmo princípio mas cálculo geral em vez de por nacionalidade
            for (int i=0; i<size_base;i++) {
                if ((lista_estudantes[i].ocupado == 1) && (lista_estudantes[i].ano_curso == j)) {
                        n_ele++;
                        float idade = ano_atual - (lista_estudantes[i].data_n.ano); //idade é obtida de forma muito simplificada através do ano de nascimento.
                        //ignoram-se as outras componentes desta data por agora
                        soma = soma + idade;
                }
            }
            
            if (n_ele!=0) {
                media_por_nac_por_ano[j-1] = (soma/n_ele);
            }
            else { //para evitar possíveis divisões por zero
                media_por_nac_por_ano[j-1] = 0;
            }
        }
    }
    

    return media_por_nac_por_ano; //retorna todo o vetor
}


void n_medio_mat(ALUNO * lista_estudantes, int size_base)
{
    //media geral
    float soma_geral = 0; //soma
    float n_total = 0; //numero de elementos
    float media_geral = 0; //media

    //calcula a soma e numero de elementos (do número de matrículas)
    for (int i=0; i<size_base; i++) {
        if (lista_estudantes[i].ocupado==1) {
            soma_geral += lista_estudantes[i].n_matriculas;
            n_total++;
        }
    }

    media_geral = soma_geral / n_total; //calcula a média

    //media por nacionalidades
    

    NACIO * vetor_nacionalidades = NULL; //armazena as nacionalidades a considerar numa estrutura própria
    int size_vetor_nacio = 0; //tamanho da estrutura a considerar num outro ciclo
    float * medias = calloc(1,sizeof(float)); //cria os vetores relevantes, inicializa todos os campos a 0
    float * somas = calloc(1,sizeof(float));
    float * n_ele = calloc(1,sizeof(float));

    for (int i=0, k=0; i<size_base; i++) {
        if (lista_estudantes[i].ocupado == 1) {
            if (!vetor_nacionalidades) { //se não existir, primeira iteração

                NACIO * new_vetor_nacionalidades = (NACIO *) realloc(vetor_nacionalidades,sizeof(NACIO)); //realocação de memória
                vetor_nacionalidades = new_vetor_nacionalidades;
                vetor_nacionalidades[0].nacionalidade = (char *) (strdup (lista_estudantes[i].nacionalidade));
                
                medias = (float *) realloc(medias,sizeof(float));
                somas = (float* ) realloc(somas,sizeof(float));
                n_ele = (float *) realloc(n_ele,sizeof(float));
                somas[0] = lista_estudantes[i].n_matriculas; //determina soma e número de elementos
                n_ele[0] = 1;
                
                size_vetor_nacio = 1; //aumenta tamanho da estrutura
            }
            else {

                int num_rep = 0; //determina quantos elementos foram percorridos na estrutura para ver se o aluno tem uma das suas nacionalidades
                
                for (int j=0; j<size_vetor_nacio; j++) {
                    //se o aluno tiver nacionalidade já pertencente à estrutura
                    if (strcmp(lista_estudantes[i].nacionalidade,vetor_nacionalidades[j].nacionalidade)==0) {
                        
                        printf("\n%s\n",vetor_nacionalidades[j].nacionalidade);
                        somas[j] = somas[j] + lista_estudantes[i].n_matriculas;
                        n_ele[j] ++;

                        
                        break;
                    }
                    else {
                        num_rep++; //no caso de não encontrar a nacionalidade certa, percorre a estrutura de nacionalidades
                    }
                }
                //se o aluno tiver uma nacionalidade nova
                if (num_rep==size_vetor_nacio) {
                    k++;
                    size_vetor_nacio ++; //aumenta o tamanho da estrutura
                
                    NACIO * new_vetor_nacionalidades = (NACIO *) realloc(vetor_nacionalidades,sizeof(NACIO *)*sizeof(NACIO)); //??? só funcionava assim
                    vetor_nacionalidades = new_vetor_nacionalidades;
                    //adiciona nova nacionalidade
                    vetor_nacionalidades[k].nacionalidade = strdup (lista_estudantes[i].nacionalidade);
                    medias = (float *) realloc(medias,sizeof(float)* sizeof(float*)); //adiciona mais espaço aos outros vetores
                    somas = (float *) realloc(somas,sizeof(float)* sizeof(float*));
                    n_ele = (float *) realloc(n_ele,sizeof(float)*sizeof(float*));
                    somas[k] = lista_estudantes[i].n_matriculas;
                    n_ele[k] = 1;

                }
            }
        }
        
    
    }

    
    for (int i=0; i<size_vetor_nacio; i++) {
        medias[i]=somas[i]/n_ele[i]; //calcula todas as médias
    }

    printf("\nA media geral do numero de matriculas e %.2f",media_geral);

    for (int i=0;i<size_vetor_nacio;i++) { //percorre a estrutura e o vetor das médias
        printf("\nA media do numero de matriculas da nacionalidade \"%s\" e %.2f.",vetor_nacionalidades[i].nacionalidade,medias[i]);
    }

    puts("");
}


void criar_txt_ficheiro_guardar (ALUNO * dados_alunos, int size_base, char * filepath1, char * filepath2)
{
    txtFile output_txt_estudantes; //estrutura para estudantes
    txtFile output_txt_situacao; //estrutura para situação
    output_txt_situacao.data = NULL;
    char * vetor_situacao; //vetor que vai receber informação
    
    char * vetor_estudantes; //vetor que vai receber informaçao (nao tinha a certeza como fazer diretamente para txt.data)
    //é só para o ficheiro estudantes, o outro tem outro vetor
    
    for (int i=0,rep=0,rep2=0; i<size_base; i++) {
        if (dados_alunos[i].ocupado==1){ //apenas se ocupado
            
            //vetor_estudantes
            if (rep!=0) {
                //no caso de não ser a primeira iteração do aluno, acrescenta um parágrafo
                vetor_estudantes = strcat(vetor_estudantes,"\n");
            }
            

            int temp = dados_alunos[i].codigo; //informação a transformar
            char * temp2 = malloc(sizeof(char)*((int)(log10(temp)))); //logaritmo necessário para determinar espaço utilizado; vai ter a informação transformada em char*
            sprintf(temp2, "%d", temp); //função utilizada para transformar int e float em char*
            if (rep==0) { //no caso de ser a primeira iteração, inicializa o vetor
                vetor_estudantes = strdup(temp2);
            }
            else {
                vetor_estudantes = strcat(vetor_estudantes,strdup(temp2)); //Strcat vai adicionar a informação ao vetor
            }
            vetor_estudantes = strcat(vetor_estudantes,"\t"); //elemento de separação de cada secção
            
            vetor_estudantes = strcat(vetor_estudantes,strdup(dados_alunos[i].nome));
            vetor_estudantes = strcat(vetor_estudantes,"\t");

            temp = dados_alunos[i].data_n.dia;
            temp2 = malloc(sizeof(char)*(int)(log10(temp)));
            if (temp<DEZENA) {
                vetor_estudantes = strcat(vetor_estudantes,"0"); 
            }
            sprintf(temp2, "%d", temp);
            
            vetor_estudantes = strcat(vetor_estudantes,strdup(temp2));
            vetor_estudantes = strcat(vetor_estudantes,"-");
            
            temp = dados_alunos[i].data_n.mes;
            temp2 = malloc(sizeof(char)*((int)log10(temp)));
            if (temp<DEZENA) {
                vetor_estudantes = strcat(vetor_estudantes,"0"); 
            }
            sprintf(temp2, "%d", temp);
            vetor_estudantes = strcat(vetor_estudantes,strdup(temp2));
            vetor_estudantes = strcat(vetor_estudantes,"-"); 
            
            temp = dados_alunos[i].data_n.ano;
            temp2 = malloc(sizeof(char)*((int)log10(temp)));
            sprintf(temp2, "%d", temp);
            vetor_estudantes = strcat(vetor_estudantes,strdup(temp2));
            
            
            vetor_estudantes = strcat(vetor_estudantes,"\t");
            vetor_estudantes = strcat(vetor_estudantes,strdup(dados_alunos[i].nacionalidade));


            //vetor situacao escolar dos alunos
            if (rep2!=0) {
                //no caso de não ser a primeira iteração do aluno, acrescenta um parágrafo
                vetor_situacao = strcat(vetor_situacao,"\n");
            }
            

            temp = dados_alunos[i].codigo;
            temp2 = temp2 = malloc(sizeof(char)*((int)log10(temp))); 
            sprintf(temp2, "%d", temp);
            if (rep==0) {
                vetor_situacao = strdup(temp2);
            }
            else {
                vetor_situacao = strcat(vetor_situacao,strdup(temp2));
            }
            vetor_situacao = strcat(vetor_situacao,"\t");

            temp = dados_alunos[i].ano_curso;
            temp2 = malloc(sizeof(char)*(int)(log10(temp)));
            sprintf(temp2, "%d", temp);
            
            vetor_situacao = strcat(vetor_situacao,strdup(temp2));
            vetor_situacao = strcat(vetor_situacao,"\t");
            
            temp = dados_alunos[i].ects_concluidos;
            temp2 = malloc(sizeof(char)*((int)log10(temp)));
            sprintf(temp2, "%d", temp);
            vetor_situacao = strcat(vetor_situacao,strdup(temp2));
            vetor_situacao = strcat(vetor_situacao,"\t"); 
            
            temp = dados_alunos[i].n_matriculas;
            temp2 = malloc(sizeof(char)*((int)log10(temp)));
            sprintf(temp2, "%d", temp);
            vetor_situacao = strcat(vetor_situacao,strdup(temp2));
            vetor_situacao = strcat(vetor_situacao,"\t");
            
            float temp_f = dados_alunos[i].media_atual;
            temp2 = malloc(sizeof(char)*((float)log10(temp_f)));
            sprintf(temp2, "%.1f", temp_f);
            for (int k=0; k<strlen(temp2)+1; k++) {
                
                if (temp2[k] == ',') {
                    temp2[k] = '.';
                }
            }
            vetor_situacao = strcat(vetor_situacao,strdup(temp2));


            rep++; //verifica se é a primeira iteração do vetor estudantes
            rep2++; //verifica se é a primeira iteração do vetor alunos
        } 
    }

    int size_txt_est = strlen(vetor_estudantes); //calcula tamanho dos dados
    output_txt_estudantes.size = size_txt_est; //coloca na struct
    int size_txt_sit = strlen(vetor_situacao);
    output_txt_situacao.size = size_txt_sit;
    
    output_txt_estudantes.data = & vetor_estudantes; //transfere vetor para campo adequado na struct
    output_txt_situacao.data = & vetor_situacao;
    
    output_txt_estudantes.path = strdup(filepath1); //utiliza os caminho iniciais dos ficheiros originais
    output_txt_situacao.path = strdup(filepath2);

    //separa os caminhos dos nomes dos ficheiros, de modo a obter este último
    char** pathParts1 = str_split(strdup(filepath1), PATH_SEPARATOR_CHAR, NULL);

    for (int i = 0; *(pathParts1 + i); i++) {
        if (*(pathParts1 + i + 1) == NULL) { //procura a última parte (a parte antes de \0)
            output_txt_estudantes.fileName = *(pathParts1 + i);
        }
    }

    char** pathParts2 = str_split(strdup(filepath1), PATH_SEPARATOR_CHAR, NULL);

    for (int i = 0; *(pathParts2 + i); i++) {
        if (*(pathParts2 + i + 1) == NULL) {
            output_txt_situacao.fileName = *(pathParts2 + i);
        } 
    }

    if (output_txt_estudantes.size!=0) {
        output_txt_estudantes.loaded = 1; //diz que a informação está carregada se o tamanho da informação da estrutura for diferente de zero
    }
    else {
        output_txt_estudantes.loaded = 0;
    }

    if (output_txt_situacao.size!=0) {
        output_txt_situacao.loaded = 1;
    }
    else {
        output_txt_situacao.loaded = 0;
    }

    txt_save_file(output_txt_estudantes); //guarda os ficheiros
    txt_save_file(output_txt_situacao);

}