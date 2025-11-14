#include <stdio.h>
#include <windows.h>

int main() {

    int n;
    SetConsoleOutputCP(CP_UTF8);
    printf("Введите количество элементов массива: ");
    scanf("%d", &n);

    if (n <= 0) {
        SetConsoleOutputCP(CP_UTF8);
        printf("Количество элементов должно быть положительным числом.\n");
        return 1;
    }

    int arr[n];
    SetConsoleOutputCP(CP_UTF8);
    printf("Введите элементы массива:\n");
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }

    if (n < 2) {
        SetConsoleOutputCP(CP_UTF8);
        printf("Недостаточно элементов для поиска диапазона.\n");
        return 0;
    }

    int min = arr[0];
    int max = arr[0];
    int min_idx = 0;
    int max_idx = 0;

    for (int i = 1; i < n; ++i) {
        if (arr[i] < min) {
            min = arr[i];
            min_idx = i;
        }
        if (arr[i] > max) {
            max = arr[i];
            max_idx = i;
        }
    }

    int start_index;
    int end_index;

    if (min_idx < max_idx) {
        start_index = min_idx;
        end_index = max_idx;
    } else {
        start_index = max_idx;
        end_index = min_idx;
    }
    SetConsoleOutputCP(CP_UTF8);
    printf("Четные элементы массива между минимальным и максимальным:\n");

    for (int i = start_index + 1; i < end_index; ++i) {
        if (arr[i] % 2 == 0) {
            printf("%d ", arr[i]);
        }
    }

    printf("\n");

    return 0;
}