#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void input(int a[], int n);
void output(int a[], int n);
void process(int a[], int n);

int main() {
    SetConsoleOutputCP(CP_UTF8);

    int n;
    int *a;

    printf("Введите n: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Ошибка: n должно быть > 0.\n");
        return 1;
    }

    a = (int*)malloc(n * sizeof(int));

    if (a == NULL) {
        printf("Ошибка памяти!\n");
        return 1;
    }

    printf("Введите %d элементов:\n", n);
    input(a, n);

    printf("\nМассив:\n");
    output(a, n);
    process(a, n);
    free(a);

    return 0;
}

void input(int a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("a[%d]: ", i);
        scanf("%d", &a[i]);
    }
}

void output(int a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void process(int a[], int n) {
    if (n < 2) {
        printf("\nМало элементов.\n");
        return;
    }

    int min_i = 0;
    int max_i = 0;
    for (int i = 1; i < n; i++) {
        if (a[i] < a[min_i]) {
            min_i = i;
        }
        if (a[i] > a[max_i]) {
            max_i = i;
        }
    }

    int start, end;
    if (min_i < max_i) {
        start = min_i;
        end = max_i;
    } else {
        start = max_i;
        end = min_i;
    }

    printf("\nMin: %d (индекс %d)\n", a[min_i], min_i);
    printf("Max: %d (индекс %d)\n", a[max_i], max_i);

    printf("Четные между min и max:\n");
    int c = 0;
    for (int i = start + 1; i < end; i++) {
        if (a[i] % 2 == 0) {
            printf("%d ", a[i]);
            c++;
        }
    }

    if (c == 0) {
        printf("Нет таких.\n");
    } else {
        printf("\n");
    }
}