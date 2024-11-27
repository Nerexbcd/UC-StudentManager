#ifndef STRING_UTIL_H_INCLUDED
#define STRING_UTIL_H_INCLUDED

/* Split a String */
/* It splits a string by a separator and returns an array with each part. Also can return the size of parts the original string was separeted */
char** str_split(char str[], const char separator, size_t *size);

#endif