#include <stdio.h>

#include "libs/data/txt_files.h"

int main(void)
{
    txtFile txt = txt_files_init("/home/user/documents/file.txt");
    printf("Filepath: %s\n", txt.filepath);
    printf("Filename: %s\n", txt.filename);


    printf("Hello, World!\n");
    return 0;
}