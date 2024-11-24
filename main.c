#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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


    printf(CYAN("Starting...\n\n"));

    char *path_estudantes;

    if (strcmp(OS, "W") == 0)
    {
        path_estudantes = "data\\estudantes.txt";
    }
    else if (strcmp(OS, "L") == 0)
    {
        path_estudantes = "data/estudantes.txt";
    }

    txtFile txt = txt_files_init(path_estudantes);
    printf("FileDir: %s\n", txt.fileDir);
    printf("Filename: %s\n", txt.fileName);

  
    if (txt_load_file(&txt)!=0)
    {
        printf(CYAN("Exiting...\n"));
        return 1;
    }

    // O data lido do TXT é um array de strings em que cada string é uma linha do ficheiro
    // por exemplo está a dar print da primeira linha
    printf("Data: %s\n", txt.data[0]);
    
    // Podes usar a função sizeof para saber quantas linhas tem
    printf("Size: %u\n", sizeof(txt.data));
    //txt_unload_file(&txt);
    //printf("Data: %s\n", txt.data);


  
    return 0;
}