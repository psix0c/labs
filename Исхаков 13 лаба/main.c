#include <stdio.h>
#include "mystring.c"
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    printf("my_strlen\n");
    const char *str = "Привет!";
    printf("Строка: \"%s\"\n", str);
    printf("Длина строки (my_strlen): %zu\n", my_strlen(str));
    printf("\n");


    printf("my_strcpy\n");
    const char *src = "Эта строка будет скопирована.";
    char dest[50];
    my_strcpy(dest, src);
    printf("Исходная строка: \"%s\"\n", src);
    printf("Скопированная строка: \"%s\"\n", dest);
    printf("\n");


    printf("my_strcat\n");
    char destt[50] = "Первая. ";
    const char *srcc = "Вторая. ";
    printf("Строка 1: \"%s\"\n", destt);
    printf("Строка 2: \"%s\"\n", srcc);
    my_strcat(destt, srcc);
    printf("Результат: \"%s\"\n", destt);
    printf("\n");


    printf("my_strcmp\n");
    const char *s1 = "яблоко";
    const char *s2 = "яблоко";
    const char *s3 = "яблоня";
    const char *s4 = "ясли";
    printf("Сравнение \"%s\" и \"%s\": %d\n", s1, s2, my_strcmp(s1, s2));
    printf("Сравнение \"%s\" и \"%s\": %d\n", s1, s3, my_strcmp(s1, s3));
    printf("Сравнение \"%s\" и \"%s\": %d\n", s3, s4, my_strcmp(s3, s4));
    printf("\n");


    printf("my_strchr\n");
    const char *str_for_chr = "Это тестовая строка с символом 's'.";
    char char_find = 's';
    char *result_chr = my_strchr(str_for_chr, char_find);
    if (result_chr != NULL) {
        printf("Символ '%c' найден в строке \"%s\"\n", char_find, str_for_chr);
        printf("Часть строки, начиная с этого символа: \"%s\"\n", result_chr);
    } else {
        printf("Символ '%c' не найден.\n", char_find);
    }
    printf("\n");


    printf("my_strstr\n");
    const char *haystack = "Быстрая бурая лиса прыгает через ленивую собаку";
    const char *needle = "лиса";
    char *result_str = my_strstr(haystack, needle);
    if (result_str != NULL) {
        printf("Подстрока \"%s\" найдена в \"%s\"\n", needle, haystack);
        printf("Часть строки, начиная с подстроки: \"%s\"\n", result_str);
    } else {
        printf("Подстрока \"%s\" не найдена.\n", needle);
    }
    printf("\n");

    return 0;
}