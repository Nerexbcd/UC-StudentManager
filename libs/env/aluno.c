#include <stdio.h>
#include <stdlib.h>
#include "aluno.h"
#include "../data/txt_files.h"
#include "../utils/string_util.h"
#include "../style/colors.h"


void inserir_estudante(ALUNO *lista_estudantes,int i,char *txt)
{
    int j;
    for (j=0;j<=sizeof(lista_estudantes);j++) {
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

void seek_data(char *path_ficheiro_estu, char *path_ficheiro_situacao, ALUNO *base_dados)
{
    int k=0;
    txtFile txt_estudantes = txt_files_init(path_ficheiro_estu);
    txt_load_file(&txt_estudantes);
    for (int i=0,j=0; i < txt_get_size(txt_estudantes) ; i++) {
        if ((base_dados[j]).ocupado==0) {
            (base_dados[j]).ocupado=1;
            while (*txt_estudantes.data != "\n") {
                k=0;
                while (*txt_estudantes.data != "\t") {
                    switch (k) {
                        case 0:
                        break;
                        case 1:
                        //etc;
                        break;
                    }
                    k++;
                }
            }
        j++;
        }
    }
    txt_unload_file(&txt_estudantes);

    txt_estudantes = txt_files_init(path_ficheiro_situacao);
    txt_load_file(&txt_estudantes);
        for (int i=0; i < txt_get_size(txt_estudantes) ; i++) {

        }
    txt_unload_file(&txt_estudantes);
}

void remover_estudante(ALUNO *lista_estudantes,int i)
{
    (lista_estudantes[i]).ocupado=0;
}

void atualizar_estudante(ALUNO *lista_estudantes,int i)
{
    
}
