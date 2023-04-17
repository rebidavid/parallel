#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define ARRAY_SIZE 1000000

int main() {
    srand(time(NULL));

    // Tömb létrehozása
    double *array = malloc(ARRAY_SIZE * sizeof(double));

    // Véletlenszerű értékek generálása
    #pragma omp parallel for
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = (double) rand() / RAND_MAX;
    }

    // Tömb kiírása
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%f\n", array[i]);
    }

    // Tömb felszabadítása
    free(array);

    return 0;
}
