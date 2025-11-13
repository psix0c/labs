#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void InputArrayFromFile(int arr[], int n, FILE *f);
void OutputArrayToFile(int arr[], int n, FILE *f);
void ProcessArray(int arr[], int n, FILE *f);

int main() {
    SetConsoleOutputCP(CP_UTF8);

    FILE *in, *out;
    fopen_s(&in,"input.txt", "rt");
    fopen_s(&out,"output.txt", "wt");

    if (!in) {
        printf("Ошибка1\n");
        return 1;
    }
    if (!out) {
        printf("Ошибка2\n");
        fclose(in);
        return 1;
    }

    int n;
    fscanf(in, "%d", &n);
    if (n <= 0) {
        fprintf(out, "Ошибка3\n");
        fclose(in);
        fclose(out);
        return 1;
    }

    int *array = malloc(n * sizeof(int));
    if (array == NULL) {
        fprintf(out, "Ошибка выделения памяти!\n");
        fclose(in);
        fclose(out);
        return 1;
    }

    InputArrayFromFile(array, n, in);

    fprintf(out, "Исходный массив:\n");
    OutputArrayToFile(array, n, out);

    ProcessArray(array, n, out);

    free(array);
    fclose(in);
    fclose(out);

    printf("Обработка завершена. Результат записан в output.txt\n");
    return 0;
}

void InputArrayFromFile(int arr[], int n, FILE *f) {
    for (int i = 0; i < n; i++) {
        fscanf(f, "%d", &arr[i]);
    }
}

void OutputArrayToFile(int arr[], int n, FILE *f) {
    for (int i = 0; i < n; i++) {
        fprintf(f, "%d ", arr[i]);
    }
    fprintf(f, "\n");
}

void ProcessArray(int arr[], int n, FILE *f) {
    if (n < 2) {
        fprintf(f, "В массиве слишком мало элементов\n");
        return;
    }

    int min_idx = 0, max_idx = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[min_idx]) min_idx = i;
        if (arr[i] > arr[max_idx]) max_idx = i;
    }

    int start_index = (min_idx < max_idx) ? min_idx : max_idx;
    int end_index   = (min_idx < max_idx) ? max_idx : min_idx;

    fprintf(f, "\nМинимальный элемент: %d (индекс %d)\n", arr[min_idx], min_idx);
    fprintf(f, "Максимальный элемент: %d (индекс %d)\n", arr[max_idx], max_idx);

    fprintf(f, "Чётные элементы между min и max:\n");
    int count = 0;
    for (int i = start_index + 1; i < end_index; i++) {
        if (arr[i] % 2 == 0) {
            fprintf(f, "%d ", arr[i]);
            count++;
        }
    }

    if (count == 0) {
        fprintf(f, "Таких элементов нет.\n");
    } else {
        fprintf(f, "\n");
    }
}
