#ifndef MYSTRING_H
#define MYSTRING_H

#include <stddef.h>

size_t my_strlen(const char *s);
char *my_strcpy(char *dest, const char *src);
char *my_strcat(char *dest, const char *src);
int my_strcmp(const char *s1, const char *s2);
char *my_strchr(const char *s, int c);
char *my_strstr(const char *haystack, const char *needle);

#endif