#include <stddef.h>

size_t my_strlen(const char *s) {
    if (s == NULL) return 0;
    size_t length = 0;
    while (s[length] != '\0') {
        length++;
    }
    return length;
}

char *my_strcpy(char *dest, const char *src) {
    if (dest == NULL || src == NULL) return dest;
    size_t i;
    for (i = 0; src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return dest;
}

char *my_strcat(char *dest, const char *src) {
    if (dest == NULL || src == NULL) return dest;
    size_t dest_len = my_strlen(dest);
    size_t i = 0;
    while (src[i] != '\0') {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[dest_len + i] = '\0';
    return dest;
}

int my_strcmp(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) return 0;
    size_t i = 0;
    while (s1[i] == s2[i]) {
        if (s1[i] == '\0') {
            return 0;
        }
        i++;
    }
    return (unsigned char)s1[i] - (unsigned char)s2[i];
}

char *my_strchr(const char *s, int c) {
    if (s == NULL) return NULL;
    for (size_t i = 0; s[i] != '\0'; i++) {
        if (s[i] == (char)c) {
            return (char *)&s[i];
        }
    }
    if (c == '\0') {
        return (char *)&s[my_strlen(s)];
    }
    return NULL;
}

char *my_strstr(const char *haystack, const char *needle) {
    if (haystack == NULL || needle == NULL) return NULL;
    if (needle[0] == '\0') {
        return (char *)haystack;
    }
    for (size_t i = 0; haystack[i] != '\0'; i++) {
        size_t j = 0;
        while (needle[j] != '\0' && haystack[i + j] == needle[j]) {
            j++;
        }
        if (needle[j] == '\0') {
            return (char *)&haystack[i];
        }
    }
    return NULL;
}
