#ifndef STRING_UTIL_H_INCLUDED
#define STRING_UTIL_H_INCLUDED

/* Split a String */
/* It splits a string by a separator and returns an array with each part. Also can return the size of parts the original string was separeted */
char** str_split(char str[], const char separator, size_t * size);

int str_get_bigger(char **strs, int *size);

char* str_concat(const char *s1, const char *s2);

char* str_convert_int(int num);

#endif