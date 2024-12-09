#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "string_util.h"

char** str_split(char str[], char separator, size_t *size) {
    char **result = 0;
    size_t count = 0;
    char *tmp = str;
    char *last_comma = 0;
    char delim[2];
    delim[0] = separator;
    delim[1] = 0;

    // Count how many elements will be extracted
    while (*tmp) {
        if (separator == *tmp) {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    // Add space for trailing token
    count += last_comma < (str + strlen(str) - 1);

    // Add space for terminating null string so caller
    // knows where the list of returned strings ends
    count++;

    result = malloc(sizeof(char*) * count);

    if (result) {
        size_t idx  = 0;
        char* token = strtok(str, delim);

        while (token) {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        *(result + idx) = 0;
    }

    if (size != NULL) *size = count - 1;


    return result;
}

int str_get_bigger(char **strs, int size) {
    int bigger = 0;
    for (int i = 0; i<size; i++) {
        if (strlen(strs[i]) > bigger) {
            bigger = strlen(strs[i]);
        }
    }
    return bigger;
}