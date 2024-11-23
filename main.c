#include <stdio.h>
#include <string.h>
#include "libs/style/tools.h"
#include "libs/data/txt_files.h"
#include "libs/style/colors.h"
#include "libs/style/tools.h"

int main(void)
{
    clearConsole();
    printf(CYAN("Starting...\n\n"));

    txtFile txt = txt_files_init("data/file.txt");
    printf("FileDir: %s\n", txt.fileDir);
    printf("Filename: %s\n", txt.fileName);

    if (txt_load_file(&txt)!=0)
    {
        printf(CYAN("Exiting...\n"));
        return 1;
    }

    txt_load_file(&txt);
    printf("Data: %s\n", txt.data[0]);
    //txt_unload_file(&txt);
    //printf("Data: %s\n", txt.data[0]);


    printf("Hello, World!\n");
    printf(GREEN("\n!! Success on Execution !!\n"));
    printf(CYAN("Exiting...\n"));
    return 0;
}