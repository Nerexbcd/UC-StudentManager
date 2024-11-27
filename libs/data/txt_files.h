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
/* It Prepares the file to be used */
txtFile txt_files_init(char *path);

/* Load txt files in to Program */
/* It reads the file and stores the data in the data array */
void txt_load_file(txtFile *txt);

/* Unload txt files from Program */
/* It frees the memory allocated for the data array */
void txt_unload_file(txtFile *txt);

/* Get txt file data */
/* It returns an array with each line one the file*/
char** txt_get_data(txtFile txt);

/* Get txt file size */
/* It returns the number of lines in the file */
size_t txt_get_size(txtFile txt);

#endif