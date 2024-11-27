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

   // for (int i = 0; i < 10; i++)
    //{
        clearConsole();
   /*    program_header();
        printf(CYAN("Starting..."));
        for (int j = 1; j < i; j++) {
            printf(CYAN("."));
        }
        if (i == 9) printf(CYAN(" [✓]"));
        printf("\n");
        sleep(1);
    }
    */

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

  
    // // Podes usar a função sizeof para saber quantas linhas tem
    // printf("Size: %u\n", txt_get_size(txt_estudantes));



    ALUNO aaa[10];
    aaa[0].ocupado=0;
    aaa[1].ocupado=0;
    aaa[2].ocupado=0;
    aaa[3].ocupado=0;
    aaa[4].ocupado=0;


    size_t size_alunos = 0;

    seek_data(txt_estudantes, txt_situacao, aaa,&size_alunos);

    

    mostrar_lista(aaa);


    //Menu principal
   /*
   do
    {
        load ficheiro 1
        atribuir atributos do ficheiro 1 ao struct aluno
        load ficheiro 2
        atribuir atributos do ficheiro 2 ao struct aluno

        escolhas do utilizador (com outros menus)

        saida - break
    } while (1);
    */
    
  
    return 0;
}