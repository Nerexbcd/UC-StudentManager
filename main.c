#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include "libs/style/tools.h"
#include "libs/data/txt_files.h"
#include "libs/env/aluno.h"
#include "libs/style/colors.h"
#include "libs/style/tools.h"
#include "libs/style/program.h"
#include "libs/style/menu.h"

#ifdef _WIN32
    #define OS "W"
    #include<windows.h>
#elif __linux__
    #define OS "L"
    #include<unistd.h>
#endif


int main(void)
{
    

    setlocale(LC_ALL, "Portuguese");

    /*
    // // Podes usar a função sizeof para saber quantas linhas tem
    //printf("Size: %u\n", txt_get_size(txt_estudantes));
    */

    
    int condicao_saida=0;
    //MENU PRINCIPAL
    do
    {
        
        for (int i = 0; i < 10; i++)
        {
            clearConsole();
            //program_header();
            printf(CYAN("Starting..."));
            for (int j = 1; j < i; j++) {
                printf(CYAN("."));
            }
            if (i == 9) printf(CYAN(" [DONE!]"));
            printf("\n");
            //sleep(1);
        }
        


        printf("BEM VINDO!\n\n");

        char *path_estudantes;
        char *path_situacao;


        if (strcmp(OS, "W") == 0)
        {

            path_estudantes = "data\\estudantes.txt";
            path_situacao   = "data\\situacao_Escolar_Estudantes.txt";
        }
        else if (strcmp(OS, "L") == 0)
        {
            path_estudantes = "./data/estudantes.txt";
            path_situacao   = "./data/situacao_Escolar_Estudantes.txt";
        }

        txtFile txt_estudantes = txt_files_init(path_estudantes);
        txtFile txt_situacao   = txt_files_init(path_situacao);

        ALUNO *dados_alunos = criar_lista(&txt_estudantes);

        size_t size_alunos = 0;

        seek_data(txt_estudantes, txt_situacao,dados_alunos, &size_alunos);

        mostrar_toda_lista(dados_alunos);

        char * pesquisa = "i";
        char * ptr_pesquisa = pesquisa;

        pesquisar(dados_alunos,ptr_pesquisa);

        gets("");


        int opcao = 0;
        do
        {
            /*
            switch (opcao)
            {
            case 1:constant-expression:
                code
                break;
            case 2:
                break;
            case 3:
                break;
            default: 
                printf("Erro de seleção! Por favor faça uma escolha válida.\n")
                opcao=0;
                break;
            }
            */
            //etc
        }
        while (opcao==0);


    } while (condicao_saida==0);
 

 /*
    mostrar_toda_lista(aaa);

    inserir_estudante(aaa,&size_alunos);
    inserir_estudante(aaa,&size_alunos);
    //inserir_estudante(aaa);
    //inserir_estudante(aaa);

    mostrar_toda_lista(aaa);

    atualizar_uma_caracteristica_estudante(aaa);


    mostrar_toda_lista(aaa);


  */  
  
    return 0;
}