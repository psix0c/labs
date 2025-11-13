#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

struct S {
    int x, y;
    unsigned char r, g, b;
    int w;
    int rad;
};

int main() {
    SetConsoleOutputCP(CP_UTF8);
    int n;
    printf("Введите количество звезд: ");
    scanf("%d", &n);

    struct S* stars = (struct S*)malloc(n * sizeof(struct S));
    if (stars == NULL) {
        printf("Ошибка: не удалось выделить память!\n");
        return 1;
    }

    for (int i = 0; i < n; ++i)
    {
        SetConsoleOutputCP(CP_UTF8);
        printf("\nВвод данных для звезды #%d\n", i + 1);
        printf("Координата центра X: ");
        scanf("%d", &stars[i].x);
        printf("Координата центра Y: ");
        scanf("%d", &stars[i].y);

        int red, green, blue;
        SetConsoleOutputCP(CP_UTF8);
        printf("Цвет (R G B, через пробел, 0-255): ");
        scanf("%d %d %d", &red, &green, &blue);
        stars[i].r = (unsigned char)red;
        stars[i].g = (unsigned char)green;
        stars[i].b = (unsigned char)blue;

        printf("Толщина контура W: ");
        scanf("%d", &stars[i].w);
        printf("Радиус R: ");
        scanf("%d", &stars[i].rad);
    }

    FILE* f = fopen("stars.dat", "wb");
    if (f == NULL)
    {
        SetConsoleOutputCP(CP_UTF8);
        printf("Ошибка: не удалось открыть файл для записи!\n");
        free(stars);
        return 1;
    }

    SetConsoleOutputCP(CP_UTF8);
    fwrite(&n, sizeof(int), 1, f);
    fwrite(stars, sizeof(struct S), n, f);

    fclose(f);
    printf("\nДанные о %d звездах успешно сохранены в файл stars.dat\n", n);
    free(stars);

    return 0;
}