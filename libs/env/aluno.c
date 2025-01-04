#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "aluno.h"
#include "../data/txt_files.h"
#include "../style/colors.h"
#include "../style/menu.h"
#include "../utils/string_util.h"

//#define ZERO 0 talvez??



ALUNO * criar_lista(txtFile *txt_estudantes) {

    //alocar memória necessária para todos os elementos da lista
    ALUNO *lista_estudantes;
    lista_estudantes = malloc(sizeof(ALUNO)*((txt_estudantes->size)+1));

    if (sizeof(lista_estudantes)==0) {
        printf("ERRO!");
        return 0;
    }

    for (int i=0 ; i<=(txt_estudantes->size) ; i++) {
        int z=0;
        lista_estudantes[i].ocupado=0;
        lista_estudantes[i].nome=NULL;
        lista_estudantes[i].nacionalidade=NULL;
    }

    return lista_estudantes;
}




void seek_data(txtFile file_estudante, txtFile file_situacao, ALUNO *base_dados, size_t *size_alunos)
{
    size_t wrt_size_alunos = 0;

    //Atribuição dos dados do ficheiro estudantes.txt à struct
    txt_load_file(&file_estudante);
    for (int i=0; i < txt_get_size(file_estudante) ; i++) {
        if ((base_dados[i]).ocupado==0) {

            (base_dados[i]).ocupado=1;

            char *linha = file_estudante.data[i];
            char **dados = str_split(linha, '\t', NULL);

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

    for (int i=0; i < txt_get_size(file_situacao) ; i++) {
        char *linha = file_situacao.data[i];
        char **dados = str_split(linha, '\t', NULL);

        for (int j=0 ; j<wrt_size_alunos ; j++) {
            if (atoi(dados[0]) == base_dados[j].codigo) {
                
                base_dados[i].n_matriculas= atoi(strdup(dados[1]));

                base_dados[i].ects_concluidos= atoi(strdup(dados[2]));

                base_dados[i].ano_curso= atoi(strdup(dados[3]));

                base_dados[i].media_atual= atof(strdup(dados[4]));
            }
        }
    }
    txt_unload_file(&file_situacao);

    if (size_alunos != NULL) *size_alunos = wrt_size_alunos;
}




int inserir_estudante(ALUNO *lista_estudantes,size_t *size_alunos, int size_base)
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
    (lista_estudantes[j]).ocupado=1;

    printf("Codigo: ");
    scanf(" %d",&((lista_estudantes[j]).codigo));

    char * stringgg=NULL;
    size_t bufsize=200;
    printf("Nome: ");
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
    scanf(" %f",&((lista_estudantes[j]).media_atual));

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
        
    size_base++;

    return size_base;
}




void remover_estudante(ALUNO *lista_estudantes,int i)
{
    (lista_estudantes[i]).ocupado=0;
    //Para esvaziar os string:
    (*(lista_estudantes+i)).nome=NULL;
    (*(lista_estudantes+i)).nacionalidade=NULL;
}




void atualizar_uma_caracteristica_estudante(ALUNO *lista_estudantes, int size_base)
{
    //setlocale(LC_ALL, "Portuguese"); //não funciona?
    int i=0;
    int k=0; //código do estudante
    int j=0; //posição do aluno com código k na lista
    int t=0;

    do {
        printf("Qual o codigo do estudante? ");
        fflush(stdin);
        scanf(" %d",&k);

        for(t=0;t<size_base;t++) {
            if(lista_estudantes[t].codigo==k) {
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
        case 0:
            printf("Qual o novo codigo do estudante numero %d?\n",(lista_estudantes[j]).codigo);
            scanf("%d",&(lista_estudantes[j]).codigo);
            break;

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
            getline(&stringgg,&bufsize,stdin);
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
            char **ptr_dn = str_split(dn, '-', NULL);
            lista_estudantes[j].data_n.dia= atoi(strdup(ptr_dn[0]));
            lista_estudantes[j].data_n.mes= atoi(strdup(ptr_dn[1]));
            lista_estudantes[j].data_n.ano= atoi(strdup(ptr_dn[2]));

            fflush(stdin);
            break;

        case 7:
            printf("Qual o novo numero de matriculas do estudante numero %d?\n",(lista_estudantes[j]).codigo);
            scanf("%d",&(lista_estudantes[j]).n_matriculas);
            break;
    }

    printf("Novos dados do estudante:\n");
    mostrar_um_aluno(lista_estudantes,j);
    
}





int calcular_tam_lista(ALUNO *lista_estudantes) {
    //pode ser útil
    int tam = 0;
    for (int i=0; i<sizeof(lista_estudantes) ;i++) {
        if (lista_estudantes[i].ocupado==1) {
            tam++;
        }
    }
    return tam;
}



void mostrar_um_aluno(ALUNO *lista_estudantes,int posicao)
{
    fflush(stdin);
    printf("Codigo: %d\n",lista_estudantes[posicao].codigo);
    printf("Nome: %s\n",lista_estudantes[posicao].nome);
    printf("Nacionalidade: %s\n",lista_estudantes[posicao].nacionalidade);
    printf("Data de nascimento: %d-%d-%d\n", lista_estudantes[posicao].data_n.dia, lista_estudantes[posicao].data_n.mes, lista_estudantes[posicao].data_n.ano);
    printf("Numero de matriculas: %d\n",lista_estudantes[posicao].n_matriculas);
    printf("Ano do curso: %d\n",lista_estudantes[posicao].ano_curso);
    printf("Media atual: %.1f\n",lista_estudantes[posicao].media_atual);
    printf("ECTS concluidos: %d\n\n",lista_estudantes[posicao].ects_concluidos);
    fflush(stdin);
}



void mostrar_toda_lista(ALUNO *lista_estudantes, int size_base) {

    for (int i=0,j=0,rep=0; j<size_base;i++) {
        if ((lista_estudantes[i].ocupado)==1) {
            if ((rep != 0) && (rep%3==0)) {
                printf("Pagina seguinte ->");
                fflush(stdin);
                getchar();
                puts("");
                fflush(stdin);
            }
            
            mostrar_um_aluno(lista_estudantes,i);
            rep++;
            j++;
        }
    }
}



void mostrar_lista_por_ordem_apelido(ALUNO *lista_estudantes, int size_base)
{
    int * vet_organizado;
    vet_organizado = malloc(sizeof(int)*sizeof(lista_estudantes));

    //cria o vetor que vai determinar a ordem alfabética dos apelidos
    for (int k=0;k<size_base;k++) {
        vet_organizado[k]=k;
    }
    
    //struct vai acumular todos os apelidos, pela mesma ordem dos estudantes na lista normal
    APELIDO *lista_apelidos;
    lista_apelidos = malloc(sizeof(APELIDO *) * size_base);

    for (int g=0; g<size_base;g++) {
        char * linha = strdup(lista_estudantes[g].nome);
        char ** nome_comp = NULL;
        nome_comp = str_split(linha,' ', NULL);
        int componentes = 0;
        int i=0;

        while(nome_comp[i+1]!=0) {
            componentes++;
            i++;
        }
        lista_apelidos[g].apel = malloc(sizeof(char) * strlen(nome_comp[componentes]));
        lista_apelidos[g].apel = nome_comp[componentes];
    }


    int temp;

    //compara os apelidos, mas guarda a sua ordem correta no vet_organizado
    //organiza por ordem decrescente
    //crescente nao funciona por algum motivo????
    for(int i = 0; i<sizeof(vet_organizado)-1; ++i)
    {
        int pos1 = vet_organizado[i];
        int pos2 = vet_organizado[i+1];

        if(strcmp(lista_apelidos[pos1].apel, lista_apelidos[pos2].apel) < 0 )
        {
            temp = vet_organizado[i];
            vet_organizado[i] = vet_organizado[i+1];
            vet_organizado[i+1] = temp;
        }
    }

    //mostra os nomes por ordem crescente (alfabética) do apelido
    //como a lista está na ordem decrescente, também está o contador (para ser crescente)
    for (int i=sizeof(vet_organizado)-1, rep=0; i>=0; i--) {
        int posicao = vet_organizado[i];
        if (lista_estudantes[posicao].ocupado==1) {
            if(rep!=0 && rep%10==0) {
                printf("Pagina seguinte ->");
                fflush(stdin);
                getchar();
                puts("");
                fflush(stdin);
            }
            printf("%s\n",lista_estudantes[posicao].nome);
            rep++;
        }
    }

}




float media_mat(ALUNO *lista_estudantes,char *nacion, int size_base) {

    int media=0;
    int num=0;

    if (nacion == 0) {
        for(int i=0;i<size_base;i++) {
            if (lista_estudantes[i].codigo==1) {
                media=media+(lista_estudantes[i].n_matriculas);
                num++;
            }
        }
        return (media/num);
    }
    else if (nacion != 0) {
        for(int i=0;i<size_base;i++) {
            if ((lista_estudantes[i].codigo==1) && (lista_estudantes[i].nacionalidade==nacion)) {
                media=media+(lista_estudantes[i].n_matriculas);
                num++;
            }
        }
        return (media/num);
    }
}





void pesquisar(ALUNO *lista_estudantes,char *pesquisa, int size_base)
{
    int * lista_matches;
    lista_matches = (int *) malloc(sizeof(int)*size_base);

    for (int s=0; s<sizeof(lista_matches); s++) {
        lista_matches[s]=0;
    }


    for (int i=0; i<size_base; i++) {

        char * vetor = lista_estudantes[i].nome;  //define o vetor a comparar.
    
        for (int k=0; k<(sizeof(* lista_estudantes->nome)); k++) { //vai comparar elemento a elemento
            int repeticao=k;

            do {
                int posicao=0;
                int matches=0;

                //procura o primeiro elemento que seja igual ao primeiro elemento do vetor pesquisa
                while((vetor[posicao+repeticao]!=pesquisa[0]) && ((posicao+repeticao)<(strlen(vetor)))) {  //determina qual é o elemento inicial
                    int f=posicao+repeticao;
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
            while ((strlen(vetor))-repeticao>strlen(pesquisa) && repeticao!=0);

        }
    }

    int rep=0;
    int g=0;
    for (int k=0; k<size_base; k++) {
        if (rep==0) {//no case de ser a primeira iteração
            printf("Resultado(s) da pesquisa <%s>:\n",pesquisa);
        }
        if (lista_matches[k]==1) {
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



void listar_est_entre_data_n(ALUNO * lista_estudantes, char *data_1 , char * data_2, char * nac_1, char * nac_2, char * nac_3, char * nac_4, char * nac_5, int size_base)
{
    DATA_NAS data_sup;//data maior
    DATA_NAS data_inf;//data menor

    DATA_NAS data_prim;//primeira data fornecida, data_1, organizada em struct
    DATA_NAS data_seg;//segunda data fornecida, data_2, organizada em struct

    //Coloca as datas fornecidas pelo utilizador na struct do tipo DATA_NAS para fácil comparação
    //com as datas dos alunos
    char *dnp = data_1;//ponteiro de data_1
    char **ptr_dnp = str_split(dnp, '-', NULL);//vai separar as datas da carater '-'
    data_prim.dia= atoi(strdup(ptr_dnp[0]));//alocação de cada elemento no campo adequado
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

    //Efetua a comparação da data dos estudantes com o intervalo definido
    int rep=0;//serve para determinar se é necessário o elemento de paginação
    for (int k=0;k<size_base;k++) {
        if (rep!=0 && rep%3==0) {//elemento de paginação, organizado em blocos de 3 outputs
                printf("Pagina seguinte ->");
                fflush(stdin);
                getchar();
                puts("");
                fflush(stdin);
        }
        //se pertencem a uma das 5 nacionalidades fornecidas:
        if (lista_estudantes[k].ocupado==1 && (lista_estudantes[k].nacionalidade==nac_1 || lista_estudantes[k].nacionalidade==nac_2 || lista_estudantes[k].nacionalidade==nac_3 || lista_estudantes[k].nacionalidade==nac_4 || lista_estudantes[k].nacionalidade==nac_5)) {
            //Compara os anos inicialmente
            if ((lista_estudantes[k].data_n.ano>data_inf.ano) && (lista_estudantes[k].data_n.ano<data_sup.ano)) {
                mostrar_um_aluno(lista_estudantes,k);
            }
            else if (lista_estudantes[k].data_n.ano==data_inf.ano) {
                //No caso dos anos serem os extremos, compara os meses.
                if ((lista_estudantes[k].data_n.mes>data_inf.mes) && (lista_estudantes[k].data_n.mes<data_sup.mes)) {
                mostrar_um_aluno(lista_estudantes,k);
                }
                //No casos dos meses serem os extremos, compara os dias.
                else if (lista_estudantes[k].data_n.mes==data_inf.mes) { 
                    if ((lista_estudantes[k].data_n.dia>=data_inf.dia) && (lista_estudantes[k].data_n.dia<=data_sup.dia)) {
                        mostrar_um_aluno(lista_estudantes,k);
                    }
                }
                else if (lista_estudantes[k].data_n.mes==data_sup.mes) {
                    if ((lista_estudantes[k].data_n.dia>=data_inf.dia) && (lista_estudantes[k].data_n.dia<=data_sup.dia)) {
                        mostrar_um_aluno(lista_estudantes,k);
                    }
                }
            }
            //Mesma situação que o anterior, mas caso extremo oposto
            else if (lista_estudantes[k].data_n.ano==data_sup.ano) {
                if ((lista_estudantes[k].data_n.mes>data_inf.mes) && (lista_estudantes[k].data_n.mes<data_sup.mes)) {
                mostrar_um_aluno(lista_estudantes,k);
                }
                else if (lista_estudantes[k].data_n.mes==data_inf.mes) { 
                    if ((lista_estudantes[k].data_n.dia>=data_inf.dia) && (lista_estudantes[k].data_n.dia<=data_sup.dia)) {
                        mostrar_um_aluno(lista_estudantes,k);
                    }
                }
                else if (lista_estudantes[k].data_n.mes==data_sup.mes) {
                    if ((lista_estudantes[k].data_n.dia>=data_inf.dia) && (lista_estudantes[k].data_n.dia<=data_sup.dia)) {
                        mostrar_um_aluno(lista_estudantes,k);
                    }
                }

            }
        }
        rep++;//aumenta o número da iteração para a paginação adequada
    }
}


int estudantes_risco_prescrever(ALUNO * lista_estudantes, int size_base) {

    setlocale(LC_ALL,"Portuguese");
    setlocale(LC_ALL,"pt_PT.UTF-8");
    //SetConsoleOutputCP();
    //SetConsoleCP();
    
    //vetor cujas posicoes com 1 correspondem às posicoes dos alunos em risco de prescricao na struct lista_estudantes
    int * lista_prescricao = malloc(sizeof(int) * size_base);
    for (int i=0; i<sizeof(lista_prescricao); i++) {
        lista_prescricao[i]=0;//inicializa a 0: significa que o aluno na posicao i não está em risco de prescrição
    }

    int num=0; //número de estudantes em risco de prescrição
    for (int i=0;i<size_base;i++) {
        if (lista_estudantes[i].ocupado==1) {
            //3 matrículas e menos de 60 ects
            if ((lista_estudantes[i].n_matriculas==3) && (lista_estudantes[i].ects_concluidos<60)) {
                lista_prescricao[i]=1;//posição com valor 1: indica risco de prescrição
                num++;//aumenta o nº de estudantes em risco
            }
            //4 matrículas e menos de 120 ects
            else if ((lista_estudantes[i].n_matriculas==4) && (lista_estudantes[i].ects_concluidos<120)) {
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

    int rep=0;
    if (num!=0) {//no caso de haver pelo menos 1 estudante em risco
        for (int i=0;i<sizeof(lista_prescricao);i++) {
            if (lista_prescricao[i]==1) {
                if (rep==0) {//na primeira iteração vai ter este cabeçalho
                    printf("Lista de alunos em risco de prescrição:\n");
                }
                else if(rep!=0 && rep%10==0) {//paginação, mostra nomes em blocos de 10
                    printf("Pagina seguinte ->");
                    fflush(stdin);
                    getchar();
                    puts("");
                    fflush(stdin);
                }
                printf("%s\n",lista_estudantes[i].nome);//mostra o nome do estudante em risco
            }
        }
    }
    else {//no caso de ser tudo a 0
        printf("Não há alunos em risco de prescrição!\n");
    }

    return num;//retorna o número de estudantes em risco
}



float * media_idades_nacionalidade(ALUNO * lista_estudantes, char * nacio, float ano_atual, int size_base)
{
    //vetor vai organizar as médias das idades da nacionalidade fornecida pelo ano de curso
    float * media_por_nac_por_ano = malloc(sizeof(float)*5);

    for (int j=1; j<6; j++) { //determina qual o ano de curso (e posicao no vetor) estamos a avaliar
        float n_ele = 0;
        float soma = 0;

        for (int i=0; i<size_base;i++) {
            //procura os alunos que obedecem a todas as condicoes:
            //nacionalidade, ano de curso correto, existência na base de dados
            if ((lista_estudantes[i].ocupado == 1) && (strcmp(lista_estudantes[i].nacionalidade,nacio)==0) && (lista_estudantes[i].ano_curso == j)) {
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

    return media_por_nac_por_ano; //retorna todo o vetor
}