#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"
#include "../data/txt_files.h"
#include "../utils/string_util.h"
#include "../style/colors.h"



void seek_data(txtFile file_estudante, txtFile file_situacao, ALUNO *base_dados, size_t *size_alunos)
{
    size_t wrt_size_alunos = 0;
    txt_load_file(&file_estudante);

    //Atribuição dos dados do ficheiro estudantes.txt à struct
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


void inserir_estudante(ALUNO *lista_estudantes,int i)
{
    int j;
    for (j=0;j<i;j++) {
        if ((lista_estudantes[j]).ocupado==0) {
        (lista_estudantes[j]).ocupado=1;
        (lista_estudantes[j]).codigo=0;
        (lista_estudantes[j]).ects_concluidos=0;
        (lista_estudantes[j]).ano_curso=0;
        (lista_estudantes[j]).media_atual=0;
        (lista_estudantes[j]).nome;
        (lista_estudantes[j]).nacionalidade;
        (lista_estudantes[j]).data_n;
        break;
        }
    }
}


void remover_estudante(ALUNO *lista_estudantes,int i)
{
    (lista_estudantes[i]).ocupado=0;
}

void atualizar_estudante(ALUNO *lista_estudantes,int i)
{
    
}
