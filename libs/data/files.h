#ifndef files_H_INCLUDED
#define files_H_INCLUDED

typedef struct txtFile {
    char *path;
    char *fileName;
    char *fileDir;
    char loaded;
    char **data;
    int size;
} txtFile;


// ------------------------------ TXT File Error Handling

/* Error File Openning */
void txt_error_open_file(char *path);

/* Error File Data Not Loaded */
void txt_error_not_loaded(char *path);

/* Error Index Out Of Bounds */
void txt_error_index_out_of_bounds();


// ------------------------------ TXT File Initialization

/* Initialize txt file data array */
/* It Prepares the file to be used */
txtFile files_init(char *path);


// ------------------------------ TXT File to memmory and vice versa 

/* Load txt files in to Program */
/* It reads the file and stores the data in the data array */
void txt_load_file(txtFile *txt);

/* Unload txt files from Program */
/* It frees the memory allocated for the data array */
void txt_unload_file(txtFile *txt);


// ------------------------------ TXT File Infos

/* Get txt file size */
/* It returns the number of lines in the file */
int file_get_size(txtFile txt);


// ------------------------------ TXT Data Manipulation

/* Get txt file data */
/* It returns an array with each line one the file*/
char** txt_get_data(txtFile txt);

/* Append data to txt file */
/* It adds a new line to the file */
void txt_append_data(txtFile *txt, char *data);

/* Update data in txt file */
/* It changes the data in the line index */
void txt_update_data(txtFile *txt, char *data, int index);

/* Remove data from txt file */
/* It removes the line index from the file */
void txt_remove_data(txtFile *txt, int index);


// ------------------------------ TXT File Save

/* Save data to txt file */
/* It saves the data array to the file */
void txt_save_file(txtFile txt);

/* Save data to cvs file*/
/* Used in case of not using txtFile data, such as in function results*/
void cvs_result_save_file(char * header, char * result, char * nome);

/* Save data to txt file*/
/* Used in case of not using txtFile data, such as in function results*/
void txt_result_save_file(char * result, char * nome);

#endif