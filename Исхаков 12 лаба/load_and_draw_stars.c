#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

struct S
{
    int x, y;
    unsigned char r, g, b;
    int w;
    int rad;
};

void draw(const struct S* s, int num)
{
    SetConsoleOutputCP(CP_UTF8);
    printf("\n--- Звезда #%d ---\n", num);
    printf("Центр: (%d, %d)\n", s->x, s->y);
    printf("Цвет (RGB): (%d, %d, %d)\n", s->r, s->g, s->b);
    printf("Толщина контура: %d\n", s->w);
    printf("Радиус: %d\n", s->rad);
}

int main()
{
    FILE* f = fopen("stars.dat", "rb");
    if (f == NULL)
    {
        SetConsoleOutputCP(CP_UTF8);
        printf("Ошибка: не удалось открыть файл stars.dat! Убедитесь, что он существует.\n");
        return 1;
    }

    int n;
    fread(&n, sizeof(int), 1, f);
    SetConsoleOutputCP(CP_UTF8);
    printf("В файле найдено %d фигур.\n", n);

    struct S* stars = (struct S*)malloc(n * sizeof(struct S));
    if (stars == NULL) {
        SetConsoleOutputCP(CP_UTF8);
        printf("Ошибка: не удалось выделить память!\n");
        fclose(f);
        return 1;
    }

    size_t count = fread(stars, sizeof(struct S), n, f);

    fclose(f);

    if (count != n) {
        SetConsoleOutputCP(CP_UTF8);
        printf("Ошибка: не удалось прочитать все данные из файла. Файл может быть поврежден.\n");
        free(stars);
        return 1;
    }

    SetConsoleOutputCP(CP_UTF8);
    printf("Данные успешно загружены. \"Отрисовка\":\n");

    for (int i = 0; i < n; ++i)
    {
        draw(&stars[i], i + 1);
    }

    free(stars);

    return 0;
}