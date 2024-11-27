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



// ------------------------------ TXT File Initialization

txtFile txt_files_init(char path[]) {
    struct txtFile txt;
    txt.path = strdup(path);
    txt.size = 0;
    txt.loaded = 0;
    char** pathParts = str_split(strdup(path), PATH_SEPARATOR_CHAR, NULL);
    txt.fileDir = strdup("");

    for (int i = 0; *(pathParts + i); i++) {
        if (*(pathParts + i + 1) == NULL) {
            txt.fileName = *(pathParts + i);
        } else {
            strcat(strcat(txt.fileDir, *(pathParts + i)) , PATH_SEPARATOR_STR);
        }  
    }
    return txt;
}

// ------------------------------ TXT File to memmory and vice versa

void txt_load_file(txtFile *txt){
    txtFile w_txt = *txt; 
    FILE *file = fopen(w_txt.path, "r");
    if (file == NULL) {
        fprintf(stderr,RED("Error: Could not open file %s\n"), w_txt.path);
        printf(CYAN("Exiting...\n"));
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    char *string = malloc(fileSize + 1);
    fread(string, fileSize, 1, file);
    fclose(file);

    printf(CYAN("File %s loaded\n"), w_txt.path);

    string[fileSize] = 0;

    w_txt.data = str_split(string, '\n', &w_txt.size);
    free(string);
    w_txt.loaded = 1;

    *txt = w_txt;
}

void txt_unload_file(txtFile *txt){
    txtFile w_txt = *txt;
    for (int i = 0; *(w_txt.data + i); i++) {
        free(*(w_txt.data + i));
    }
    free(w_txt.data);
    w_txt.loaded = 0;
    *txt = w_txt;
}


// ------------------------------ TXT File Infos

size_t txt_get_size(txtFile txt){
    if (txt.loaded == 0) {
        fprintf(stderr,RED("Error: File %s not loaded\n"), txt.path);
        printf(CYAN("Exiting...\n"));
        exit(1);
    }
    return txt.size;
}

// ------------------------------ TXT Data Manipulation

char** txt_get_data(txtFile txt){
    if (txt.loaded == 0) {
        fprintf(stderr,RED("Error: File %s not loaded\n"), txt.path);
        printf(CYAN("Exiting...\n"));
        exit(1);
    }
    return txt.data;
}

void txt_append_data(txtFile *txt, char *data){
    txtFile w_txt = *txt;
    w_txt.data = realloc(w_txt.data, (w_txt.size + 1) * sizeof(char*));
    *(w_txt.data + w_txt.size) = strdup(data);
    w_txt.size++;
    *txt = w_txt;
}

void txt_update_data(txtFile *txt, char *data, size_t index){
    txtFile w_txt = *txt;
    if (index >= w_txt.size) {
        fprintf(stderr,RED("Error: Index out of bounds\n"));
        printf(CYAN("Exiting...\n"));
        exit(1);
    }
    free(*(w_txt.data + index));
    *(w_txt.data + index) = strdup(data);
    *txt = w_txt;
}

void txt_remove_data(txtFile *txt, size_t index){
    txtFile w_txt = *txt;
    if (index >= w_txt.size) {
        fprintf(stderr,RED("Error: Index out of bounds\n"));
        printf(CYAN("Exiting...\n"));
        exit(1);
    }
    free(*(w_txt.data + index));
    for (int i = index; i < w_txt.size - 1; i++) {
        *(w_txt.data + i) = *(w_txt.data + i + 1);
    }
    w_txt.size--;
    w_txt.data = realloc(w_txt.data, w_txt.size * sizeof(char*));
    *txt = w_txt;
}


// ------------------------------ TXT File Save

void txt_save_file(txtFile txt){
    if (txt.loaded == 0) {
        fprintf(stderr,RED("Error: File %s not loaded\n"), txt.path);
        printf(CYAN("Exiting...\n"));
        exit(1);
    }
    FILE *file = fopen(txt.path, "w");
    if (file == NULL) {
        fprintf(stderr,RED("Error: Could not open file %s\n"), txt.path);
        printf(CYAN("Exiting...\n"));
        exit(1);
    }
    for (int i = 0; i < txt.size; i++) {
        fprintf(file, "%s\n", *(txt.data + i));
    }
    fclose(file);
    printf(CYAN("File %s saved\n"), txt.path);
}