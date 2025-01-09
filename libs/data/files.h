#ifndef files_H_INCLUDED
#define files_H_INCLUDED

typedef struct SDTM_File {
    char *path;
    char *fileName;
    char *fileDir;
    char loaded;
    char **data;
    size_t size;
} SDTM_File;


// ------------------------------ File Error Handling

/* Error File Opening */
void error_open_file(char *path);

/* Error File Data Not Loaded */
void error_not_loaded(char *path);

/* Error Index Out Of Bounds */
void error_index_out_of_bounds();


// ------------------------------ TXT File Initialization

/* Initialize txt file data array */
/* It Prepares the file to be used */
SDTM_File files_init(char *path);


// ------------------------------ TXT File to memmory and vice versa 

/* Load txt files in to Program */
/* It reads the file and stores the data in the data array */
void txt_load_file(SDTM_File *txt);

/* Unload txt files from Program */
/* It frees the memory allocated for the data array */
void txt_unload_file(SDTM_File *txt);


// ------------------------------ TXT File Infos

/* Get txt file size */
/* It returns the number of lines in the file */
size_t txt_get_size(SDTM_File txt);


// ------------------------------ TXT Data Manipulation

/* Get txt file data */
/* It returns an array with each line one the file*/
char** txt_get_data(SDTM_File txt);

/* Append data to txt file */
/* It adds a new line to the file */
void txt_append_data(SDTM_File *txt, char *data);

/* Update data in txt file */
/* It changes the data in the line index */
void txt_update_data(SDTM_File *txt, char *data, size_t index);

/* Remove data from txt file */
/* It removes the line index from the file */
void txt_remove_data(SDTM_File *txt, size_t index);


// ------------------------------ TXT File Save

/* Save data to txt file */
/* It saves the data array to the file */
void txt_save_file(SDTM_File txt);


void cvs_result_save_file(char * header, char * result, char * nome);

void txt_result_save_file(char * result, char * nome);

#endif