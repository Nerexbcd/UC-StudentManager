#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include "libs/style/tools.h"
#include "libs/data/txt_files.h"
#include "libs/env/aluno.h"
#include "libs/style/colors.h"
#include "libs/style/tools.h"

    #ifdef _WIN32
        #define OS "W"
    #elif __linux__
        #define OS "L"
    #endif

int main(void)
{
    clearConsole();

    setlocale(LC_ALL, "Portuguese");

    printf(CYAN("Starting...\n\n"));

    char *path_estudantes_a;
    char *path_estudantes_b;

    if (strcmp(OS, "W") == 0)
    {
        path_estudantes_b = "data\\situacao_Escolar_Estudantes.txt";
        path_estudantes_a= "data\\estudantes.txt";
    }
    else if (strcmp(OS, "L") == 0)
    {
        path_estudantes_a = "./data/estudantes.txt";
        path_estudantes_b = "./data/situacao_Escolar_Estudantes.txt";
    }



    txtFile txt_estudantes_a = txt_files_init(path_estudantes_a);
    txtFile txt_estudantes_b = txt_files_init(path_estudantes_b);
    printf("FileDir: %s\n", txt_estudantes_a.fileDir);
    printf("Filename: %s\n", txt_estudantes_a.fileName);

    txt_load_file(&txt_estudantes_a);
  
    // Podes usar a função sizeof para saber quantas linhas tem
    printf("Size: %u\n", txt_get_size(txt_estudantes_a));

    for (int i = 0; i < txt_get_size(txt_estudantes_a) ; i++) {
        printf("Data: %s\n", txt_estudantes_a.data[i]);
    }

    txt_unload_file(&txt_estudantes_a);

    ALUNO aaa[4];
    aaa[0].ocupado=0;
    aaa[1].ocupado=0;
    aaa[2].ocupado=0;
    aaa[3].ocupado=0;
    aaa[0].codigo=001;

    seek_data(path_estudantes_a, path_estudantes_b, aaa);
    printf("\ncodigo: %d",aaa[1].codigo);


    //printf("Data: %s\n", txt.data);

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