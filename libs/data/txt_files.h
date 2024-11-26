#ifndef TXT_FILES_H_INCLUDED
#define TXT_FILES_H_INCLUDED

typedef struct txtFile {
    char *path;
    char *fileName;
    char *fileDir;
    char loaded;
    char **data;
    size_t size;
} txtFile;


/* Initialize txt file data array */
txtFile txt_files_init(char *path);

/* Load txt files in to Program */
void txt_load_file(txtFile *txt);

/* Unload txt files from Program */
void txt_unload_file(txtFile *txt);

char** txt_get_data(txtFile txt);

size_t txt_get_size(txtFile txt);

#endif