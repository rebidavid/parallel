#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_DEPTH 10

void fill_array(double *array, int size, int depth) {
    if (depth > MAX_DEPTH || size == 1) {
        // Ha elértük a maximális mélységet, vagy már csak egy elem van a tömbben, kilépünk a rekurzióból
        return;
    }

    // Tömb feltöltése véletlenszerű értékekkel
    for (int i = 0; i < size; i++) {
        array[i] = (double)rand() / RAND_MAX;
    }

    // Tömb felezése és rekurzív hívások
    int half_size = size / 2;
    double *left = malloc(half_size * sizeof(double));
    double *right = malloc((size - half_size) * sizeof(double));
    for (int i = 0; i < half_size; i++) {
        left[i] = array[i];
    }
    for (int i = half_size; i < size; i++) {
        right[i - half_size] = array[i];
    }
    fill_array(left, half_size, depth + 1);
    fill_array(right, size - half_size, depth + 1);
    for (int i = 0; i < half_size; i++) {
        array[i] = left[i];
    }
    for (int i = half_size; i < size; i++) {
        array[i] = right[i - half_size];
    }
    free(left);
    free(right);
}

int main() {
    srand(time(NULL));

    // Tömb mérete
    int size = 16;

    // Tömb létrehozása és feltöltése
    double *array = malloc(size * sizeof(double));
    fill_array(array, size, 0);

    // Tömb kiírása
    printf("Array:\n");
    for (int i = 0; i < size; i++) {
        printf("%f\n", array[i]);
    }

    free(array);
    return 0;
}
