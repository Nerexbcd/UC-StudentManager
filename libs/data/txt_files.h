#ifndef TXT_FILES_H_INCLUDED
#define TXT_FILES_H_INCLUDED

typedef struct txtFile {
    char *fileName;
    char *fileDir;
    char *loaded;
    char **data;
} txtFile;


/* Initialize txt file data array */
struct txtFile txt_files_init(char *path);

/* Load txt files in to Program */
int txt_load_file(txtFile *txt);

/* Unload txt files from Program */
int txt_unload_file(txtFile *txt);

#endif