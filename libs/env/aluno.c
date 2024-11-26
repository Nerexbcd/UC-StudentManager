#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"
#include "../data/txt_files.h"
#include "../utils/string_util.h"
#include "../style/colors.h"



void seek_data(char *path_ficheiro_estu, char *path_ficheiro_situacao, ALUNO *base_dados)
{
    txtFile txt_estudantes = txt_files_init(path_ficheiro_estu);
    txt_load_file(&txt_estudantes);
    int num_linhas = txt_get_size(txt_estudantes);

    //Atribuição dos dados do ficheiro estudantes.txt à struct
    for (int i=0; i < num_linhas ; i++) {
        if ((base_dados[i]).ocupado==0) {
            
            (base_dados[i]).ocupado=1;

            char *linha = txt_estudantes.data[i];
            int kk;
            char * string = NULL;
            int lin_size = sizeof(txt_estudantes.data[i]);
            int what;
            
            kk=0;
            string = &(linha[kk]);
            
            while (linha[kk] != '\t')
            {
                *(string+kk)=linha[kk];
                kk++;
            }
            base_dados[i].codigo= atoi(strdup(string));
            printf("\ncodigo:%d\n",base_dados[i].codigo);

            kk++;
            string = &(linha[kk]);
            while (linha[kk+1] != '\t') 
            {
                    string[kk] = linha[kk+1];
                    kk++;
            }
            base_dados[i].nome = strdup(string);
            printf("nome:%send",base_dados[i].nome);


            kk++;    
            string = &(linha[kk]);
            while (linha[kk] != '\t')
            {
                *(string+kk)=*(linha+kk);
                kk++;
            }
            base_dados[i].data_n= strdup(string);


            kk++;
            string = &(linha[kk]);
            while (linha[kk] < lin_size)
            {
                *(string+kk)=*(linha+kk);
                kk++;
            }
            base_dados[i].nacionalidade = strdup(string);
        }
    }
    txt_unload_file(&txt_estudantes);

    //Atribuição dos dados do ficheiro situaçao_Escolar_Estudantes.txt à struct
    //É efetuada a sua correta colocação por comparação dos números de código
    puts ("\ncccc");
    txt_estudantes = txt_files_init(path_ficheiro_estu);
    txt_load_file(&txt_estudantes);
    int num_linhas_b = txt_get_size(txt_estudantes);

    for (int i=0; i < num_linhas ; i++) {
        if ((base_dados[i]).ocupado=1) {
            puts("\naaaa");
            for (int j=0 ; j<num_linhas_b ; j++) {
                puts("\nbbbb");
                char *linha = txt_estudantes.data[i];
                int k=0;
                char * string = NULL;

                string = &(linha[k]);

                while (linha[k] != '\t') {
                *(string+k)=linha[k];
                k++;
                }

                if (base_dados[i].codigo == atoi(strdup(string))) {
                    k++;    
                    string = &(linha[k]);
                    while (linha[k] != '\t')
                    {
                        *(string+k)=*(linha+k);
                        k++;
                    }
                    base_dados[i].n_matriculas= atoi(strdup(string));

                    while (linha[k] != '\t')
                    {
                        *(string+k)=*(linha+k);
                        k++;
                    }
                    base_dados[i].ects_concluidos= atoi(strdup(string));

                    while (linha[k] != '\t')
                    {
                        *(string+k)=*(linha+k);
                        k++;
                    }
                    base_dados[i].ano_curso= atoi(strdup(string));

                        while (linha[k] != '\t')
                    {
                        *(string+k)=*(linha+k);
                        k++;
                    }
                    base_dados[i].media_atual= atof(strdup(string));
                }
            }
        }
    }
    txt_unload_file(&txt_estudantes);
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
