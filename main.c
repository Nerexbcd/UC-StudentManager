#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libs/style/tools.h"
#include "libs/data/txt_files.h"
#include "libs/env/aluno.h"
#include "libs/style/colors.h"
#include "libs/style/tools.h"

int main(void)
{
    clearConsole();


    printf(CYAN("Starting...\n\n"));


    txtFile txt = txt_files_init("data\\estudantes.txt");
    printf("FileDir: %s\n", txt.fileDir);
    printf("Filename: %s\n", txt.fileName);

  
    if (txt_load_file(&txt)!=0)
    {
        printf(CYAN("Exiting...\n"));
        return 1;
    }

    printf("Data: %s\n", txt.data);
    //txt_unload_file(&txt);
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