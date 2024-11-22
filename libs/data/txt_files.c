#include <stdio.h>
#include <stdlib.h>
#include "txt_files.h"
#include "../utils/string_util.h"

struct txtFile txt_files_init(char path[]) {
    struct txtFile txt;
    txt.filepath = strdup("");
    char** tokens = str_split(strdup(path), '/');

    for (int i = 0; *(tokens + i); i++) {
        if (*(tokens + i + 1) == NULL) {
            txt.filename = *(tokens + i);
        } else {
            strcat(strcat(txt.filepath, "/") ,*(tokens + i));
        }
    }

    return txt;
}