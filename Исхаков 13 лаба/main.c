#include <stdio.h>
#include "mystring.c"
#include <windows.h>
int main() {
    SetConsoleOutputCP(CP_UTF8);
    printf("my_strlen\n");
    const char *str_for_len = "Hello, C language!";
    printf("Строка: \"%s\"\n", str_for_len);
    printf("Длина строки (my_strlen): %zu\n", my_strlen(str_for_len));
    printf("\n");


    printf("my_strcpy\n");
    const char *src_for_cpy = "This will be copied.";
    char dest_for_cpy[50];
    my_strcpy(dest_for_cpy, src_for_cpy);
    printf("Исходная строка: \"%s\"\n", src_for_cpy);
    printf("Скопированная строка: \"%s\"\n", dest_for_cpy);
    printf("\n");


    printf("my_strcat\n");
    char dest_for_cat[50] = "First part. ";
    const char *src_for_cat = "Second part.";
    printf("Строка 1: \"%s\"\n", dest_for_cat);
    printf("Строка 2: \"%s\"\n", src_for_cat);
    my_strcat(dest_for_cat, src_for_cat);
    printf("Результат конкатенации: \"%s\"\n", dest_for_cat);
    printf("\n");


    printf("my_strcmp\n");
    const char *s1 = "apple";
    const char *s2 = "apple";
    const char *s3 = "apples";
    const char *s4 = "apply";
    printf("Сравнение \"%s\" и \"%s\": %d\n", s1, s2, my_strcmp(s1, s2));
    printf("Сравнение \"%s\" и \"%s\": %d\n", s1, s3, my_strcmp(s1, s3));
    printf("Сравнение \"%s\" и \"%s\": %d\n", s3, s4, my_strcmp(s3, s4));
    printf("\n");


    printf("my_strchr\n");
    const char *str_for_chr = "This is a test string.";
    char char_to_find = 's';
    char *result_chr = my_strchr(str_for_chr, char_to_find);
    if (result_chr != NULL) {
        SetConsoleOutputCP(CP_UTF8);
        printf("Символ '%c' найден в строке \"%s\"\n", char_to_find, str_for_chr);
        printf("Часть строки, начиная с этого символа: \"%s\"\n", result_chr);
    } else {
        SetConsoleOutputCP(CP_UTF8);
        printf("Символ '%c' не найден.\n", char_to_find);
    }
    printf("\n");

    SetConsoleOutputCP(CP_UTF8);
    printf("my_strstr\n");
    const char *haystack = "A big brown fox jumps over the lazy dog";
    const char *needle = "fox";
    char *result_str = my_strstr(haystack, needle);
    if (result_str != NULL) {
        SetConsoleOutputCP(CP_UTF8);
        printf("Подстрока \"%s\" найдена в \"%s\"\n", needle, haystack);
        printf("Часть строки, начиная с подстроки: \"%s\"\n", result_str);
    } else {
        SetConsoleOutputCP(CP_UTF8);
        printf("Подстрока \"%s\" не найдена.\n", needle);
    }
    printf("\n");

    return 0;
}