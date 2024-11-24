#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "txt_files.h"
#include "../utils/string_util.h"
#include "../style/colors.h"

#ifdef _WIN32
    #define PATH_SEPARATOR_CHAR '\\'
    #define PATH_SEPARATOR_STR  "\\"
#elif __linux__
    #define PATH_SEPARATOR_CHAR '/'
    #define PATH_SEPARATOR_STR  "/"
#endif

struct txtFile txt_files_init(char path[]) {
    struct txtFile txt;
    txt.fileDir = strdup("");
    char** tokens = str_split(strdup(path), PATH_SEPARATOR_CHAR);

    for (int i = 0; *(tokens + i); i++) {
        if (*(tokens + i + 1) == NULL) {
            txt.fileName = *(tokens + i);
        } else {
            strcat(strcat(txt.fileDir, *(tokens + i)) , PATH_SEPARATOR_STR);
        }  
    }
    return txt;
}

int txt_load_file(txtFile *txt){
    txtFile w_txt = *txt; 
    char *filePath = strcat(strdup(w_txt.fileDir), strdup(w_txt.fileName));
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        fprintf(stderr,RED("Error: Could not open file %s\n"), filePath);
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    char *string = malloc(fileSize + 1);
    fread(string, fileSize, 1, file);
    fclose(file);

    string[fileSize] = 0;

    w_txt.data = str_split(string, '\n');

    *txt = w_txt;

    return 0;
}

int txt_unload_file(txtFile *txt){
    txtFile w_txt = *txt;
    for (int i = 0; *(w_txt.data + i); i++) {
        free(*(w_txt.data + i));
    }
    free(w_txt.data);
    
    return 0;
}

