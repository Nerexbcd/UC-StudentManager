#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "aluno.h"
#include "../data/txt_files.h"
#include "../utils/string_util.h"
#include "../style/colors.h"



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
            printf("codigo:%d \n",base_dados[i].codigo);

            base_dados[i].nome = strdup(dados[1]);
            printf("nome:%s \n",base_dados[i].nome);

            base_dados[i].data_n= strdup(dados[2]);
            printf("ndata_n:%s \n",(base_dados[i]).data_n);

            base_dados[i].nacionalidade = strdup(dados[3]);
            printf("nacionalidade:%s \n\n",base_dados[i].nacionalidade);

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
                printf("codigo:%d \n",base_dados[j].codigo);

                base_dados[i].n_matriculas= atoi(strdup(dados[1]));
                printf("n_matriculas:%d \n",base_dados[i].n_matriculas);

                base_dados[i].ects_concluidos= atoi(strdup(dados[2]));
                printf("ects_concluidos:%d \n",base_dados[i].ects_concluidos);

                base_dados[i].ano_curso= atoi(strdup(dados[3]));
                printf("ano_curso:%d \n",base_dados[i].ano_curso);

                base_dados[i].media_atual= atof(strdup(dados[4]));
                printf("media_atual:%f \n\n",base_dados[i].media_atual);
            }
        }
    }
    txt_unload_file(&file_situacao);

    if (size_alunos != NULL) *size_alunos = wrt_size_alunos;
}


void inserir_estudante(ALUNO *lista_estudantes)
{
    for (int j=0;j<sizeof(lista_estudantes);j++) {
        if ((lista_estudantes[j]).ocupado==0) {
            (lista_estudantes[j]).ocupado=1;
            (lista_estudantes[j]).codigo=352;
            (lista_estudantes[j]).ects_concluidos=3;
            (lista_estudantes[j]).ano_curso=4;
            (lista_estudantes[j]).n_matriculas=2;
            (lista_estudantes[j]).media_atual=12.3;
            (lista_estudantes[j]).nome="EU";
            (lista_estudantes[j]).nacionalidade="ANGOLA";
            (lista_estudantes[j]).data_n="23-06-2938";
            break;
        }
    }
}


void remover_estudante(ALUNO *lista_estudantes,int i)
{
    (lista_estudantes[i]).ocupado=0;
    //Para esvaziar os string:
    (*(lista_estudantes+i)).nome=NULL;
    (*(lista_estudantes+i)).nacionalidade=NULL;
    (*(lista_estudantes+i)).data_n=NULL;
}

void atualizar_estudante(ALUNO *lista_estudantes,int i)
{
    setlocale(LC_ALL, "Portuguese");

    int j = sizeof(lista_estudantes);
    switch (i) {
        case 0:
            printf("Qual é o novo código do estudante número %d?\n",(lista_estudantes[j]).codigo);
            scanf("%d",&(lista_estudantes[j]).codigo);
            break;
        case 1:
            printf("Qual é o novo número de ECTS concluídos do estudante número %d?\n",(lista_estudantes[j]).codigo);
            scanf("%d",&(lista_estudantes[j]).ects_concluidos);
            break;
        case 2:
            printf("Qual é o novo ano de curso do estudante número %d?\n",(lista_estudantes[j]).codigo);
            scanf("%d",&(lista_estudantes[j]).ano_curso);
            break;
        case 3:
            printf("Qual é a nova média do estudante número %d?\n",(lista_estudantes[j]).codigo);
            scanf("%f",&(lista_estudantes[j]).media_atual);
            break;
        case 4:
            //Esvazia-se o string primeiro para evitar erros:
            (*(lista_estudantes+j)).nome=NULL;
            //(lista_estudantes[j]).nome;
            break;
        case 5:
            (*(lista_estudantes+j)).nacionalidade=NULL;
            //(lista_estudantes[j]).nacionalidade;
            break;
        case 6:
            (*(lista_estudantes+j)).data_n=NULL;
            //(lista_estudantes[j]).data_n;
            break;
        case 7:
            printf("Qual é o novo número de matrículas do estudante número %d?\n",(lista_estudantes[j]).codigo);
            scanf("%d",&(lista_estudantes[j]).n_matriculas);
            break;
    }
}


int calcular_tam_lista(ALUNO *lista_estudantes) {
    int tam = 0;
    for (int i=0; i<sizeof(lista_estudantes) ;i++) {
        if (lista_estudantes[i].ocupado==1) {
            tam++;
        }
    }
    return tam;
}


void mostrar_lista(ALUNO *lista_estudantes) {
    setlocale(LC_ALL, "Portuguese");

    for (int i=0; i<sizeof(lista_estudantes);i++) {
        if ((lista_estudantes[i].ocupado)==1) {
            printf("Código: %d\n",lista_estudantes[i].codigo);
            printf("Nome: %s\n",lista_estudantes[i].nome);
            printf("Nacionalidade: %s\n",lista_estudantes[i].nacionalidade);
            printf("Data de nascimento: %s\n",lista_estudantes[i].data_n);
            printf("Número de matrículas: %d\n",lista_estudantes[i].n_matriculas);
            printf("Ano do curso: %d\n",lista_estudantes[i].ano_curso);
            printf("Média atual: %.1f\n",lista_estudantes[i].media_atual);
            printf("ECTS concluídos: %d\n\n",lista_estudantes[i].ects_concluidos);

        }
    }
}