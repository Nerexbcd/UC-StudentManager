#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "aluno.h"
#include "../data/txt_files.h"
#include "../style/colors.h"
#include "../style/menu.h"
#include "../utils/string_util.h"


ALUNO * criar_lista(txtFile txt_estudantes) {
    ALUNO *lista_estudantes;
    lista_estudantes = malloc(sizeof(ALUNO)*(txt_estudantes.size)+1);
    for (int i=0;i<=txt_estudantes.size+1;i++) {
        lista_estudantes[i].ocupado=0;
    }
    return lista_estudantes;

    printf("%d\n",lista_estudantes[1].ocupado);
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

            base_dados[i].data_n= strdup(dados[2]);

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




void inserir_estudante(ALUNO *lista_estudantes,size_t *size_alunos)
{
    ALUNO * ptr = lista_estudantes;
    ptr = (ALUNO *) malloc(sizeof(ALUNO));
    ALUNO * new_lista_estudantes = (ALUNO *) realloc(ptr , sizeof(ALUNO));
    if(!new_lista_estudantes)
    {
        printf("erro\n");
        free(ptr);
    }

    int j = 0;
    while((lista_estudantes[j]).ocupado==1) {
        j++;
    }

    
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
    lista_estudantes[j].data_n=(char*) malloc(sizeof(stringgg));
    lista_estudantes[j].data_n=stringgg;
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

    /*if j=sizeof(lista_estudantes) {
    free(lista_estudantes);
    }*/
}




void remover_estudante(ALUNO *lista_estudantes,int i)
{
    (lista_estudantes[i]).ocupado=0;
    //Para esvaziar os string:
    (*(lista_estudantes+i)).nome=NULL;
    (*(lista_estudantes+i)).nacionalidade=NULL;
    (*(lista_estudantes+i)).data_n=NULL;
}




void atualizar_uma_caracteristica_estudante(ALUNO *lista_estudantes)
{
    //setlocale(LC_ALL, "Portuguese"); //não funciona?
    int i;
    int k; //código do estudante
    int j; //posição do aluno com código k na lista


    printf("Qual o codigo do estudante? ");
    fflush(stdin);
    scanf(" %d",&k);

    for(int t=0;t<sizeof(*lista_estudantes);t++) {
        if(lista_estudantes[t].codigo==k) {
            j=t;
            break;
        }
    }

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
            break;
        case 6:
            (*(lista_estudantes+j)).data_n=NULL;
            stringgg=NULL;
            bufsize=11;
            printf("Qual a nova data de nascimento do estudante numero %d?\n",(lista_estudantes[j]).codigo);
            fflush(stdin);
            getline(&stringgg,&bufsize,stdin);
            stringgg = * str_split(stringgg, '\n', NULL);
            lista_estudantes[j].data_n=(char*) malloc(sizeof(stringgg));
            lista_estudantes[j].data_n=stringgg;
            fflush(stdin);
            break;
            break;
        case 7:
            printf("Qual o novo numero de matriculas do estudante numero %d?\n",(lista_estudantes[j]).codigo);
            scanf("%d",&(lista_estudantes[j]).n_matriculas);
            break;
    }
}





int calcular_tam_lista(ALUNO *lista_estudantes) {
    //pode ser útil
    int tam = 0;
    for (int i=0; i<sizeof(lista_estudantes[0]) ;i++) {
        if (lista_estudantes[i].ocupado==1) {
            tam++;
        }
    }
    return tam;
}






void mostrar_toda_lista(ALUNO *lista_estudantes) {

    for (int i=0,j=0; j<calcular_tam_lista(lista_estudantes);i++) {
        if ((lista_estudantes[i].ocupado)==1) {
            if ((i != 0) && (i%3==0)) {
                printf("Pagina seguinte ->");
                fflush(stdin);
                getchar();
                puts("");
                fflush(stdin);
            }

            fflush(stdin);
            printf("Codigo: %d\n",lista_estudantes[i].codigo);
            printf("Nome: %s\n",lista_estudantes[i].nome);
            printf("Nacionalidade: %s\n",lista_estudantes[i].nacionalidade);
            printf("Data de nascimento: %s\n",lista_estudantes[i].data_n);
            printf("Numero de matriculas: %d\n",lista_estudantes[i].n_matriculas);
            printf("Ano do curso: %d\n",lista_estudantes[i].ano_curso);
            printf("Media atual: %.1f\n",lista_estudantes[i].media_atual);
            printf("ECTS concluidos: %d\n\n",lista_estudantes[i].ects_concluidos);
            fflush(stdin);

            j++;
        }
    }
}




int media_mat(ALUNO *lista_estudantes,char *nacion) {

    int media=0;
    int num=0;

    if (nacion == 0) {
        for(int i=0;i<sizeof(lista_estudantes);i++) {
            if (lista_estudantes[i].codigo==1) {
                media=media+(lista_estudantes[i].n_matriculas);
                num++;
            }
        }
        return (media/num);
    }
    else if (nacion != 0) {
        for(int i=0;i<sizeof(lista_estudantes);i++) {
            if ((lista_estudantes[i].codigo==1) && (lista_estudantes[i].nacionalidade==nacion)) {
                media=media+(lista_estudantes[i].n_matriculas);
                num++;
            }
        }
        return (media/num);
    }
}