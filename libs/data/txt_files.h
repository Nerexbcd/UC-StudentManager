#ifndef TXT_FILES_H_INCLUDED
#define TXT_FILES_H_INCLUDED

typedef struct txtFile {
    char *filename;
    char *filepath;
    FILE file;
} txtFile;


/* Initialize txt file data array */
struct txtFile txt_files_init(char *path);

/* Load txt files in to Program */
int load_txt_file(const char *filename);

#endif