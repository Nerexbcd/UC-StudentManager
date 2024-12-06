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
txtFile txt_files_init(char *path);


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
size_t txt_get_size(txtFile txt);


// ------------------------------ TXT Data Manipulation

/* Get txt file data */
/* It returns an array with each line one the file*/
char** txt_get_data(txtFile txt);

/* Get txt file line */
/* It returns the line index from the file */
char* txt_get_line(txtFile txt, size_t index);

/* Append data to txt file */
/* It adds a new line to the file */
void txt_append_data(txtFile *txt, char *data);

/* Update data in txt file */
/* It changes the data in the line index */
void txt_update_data(txtFile *txt, char *data, size_t index);

/* Remove data from txt file */
/* It removes the line index from the file */
void txt_remove_data(txtFile *txt, size_t index);


// ------------------------------ TXT File Save

/* Save data to txt file */
/* It saves the data array to the file */
void txt_save_file(txtFile txt);

#endif