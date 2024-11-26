#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"
#include "../data/txt_files.h"
#include "../utils/string_util.h"
#include "../style/colors.h"



void seek_data(char *path_ficheiro_estu, /*char *path_ficheiro_situacao,*/ ALUNO *base_dados)
{
    txtFile txt_estudantes = txt_files_init(path_ficheiro_estu);
    txt_load_file(&txt_estudantes);
    int num_linhas = txt_get_size(txt_estudantes);

    
    for (int i=0; i < num_linhas ; i++) {
        if ((base_dados[i]).ocupado==0) {
            
            (base_dados[i]).ocupado=1;

            char *linha = txt_estudantes.data[i];
            int k=0;
            char * string = NULL;
            int lin_size = sizeof(txt_estudantes.data[i]);

            string = &(linha[0]);

            printf("\n%d",k);
            
            
            while (linha[k] != '\t')
            {
                *(string+k)=linha[k];
                k++;
            }
            base_dados[i].codigo= atoi(strdup(string));


            k++;
            string = &(linha[k]);
            while (linha[k] != '\t')
            {
                *(string+k)=*(linha+k);
                k++;
            }
            base_dados[i].nome = strdup(string);


            k++;    
            string = &(linha[k]);
            while (linha[k] != '\t')
            {
                *(string+k)=*(linha+k);
                k++;
            }
            base_dados[i].data_n= strdup(string);
            

            k++;
            string = &(linha[k]);
            while (linha[k] < lin_size)
            {
                *(string+k)=*(linha+k);
                k++;
            }
            base_dados[i].nacionalidade = strdup(string);
            puts("ccc");
        }
    }
    txt_unload_file(&txt_estudantes);

    /*txt_estudantes = txt_files_init(path_ficheiro_situacao);
    txt_load_file(&txt_estudantes);
        for (int i=0; i < txt_get_size(txt_estudantes) ; i++) {

        }
    txt_unload_file(&txt_estudantes);*/
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
