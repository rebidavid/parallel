#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

// Mátrix kiírása
void printMatrix(int *matrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("%d ", matrix[i * size + j]);
        }
        printf("\n");
    }
}

// A mátrixok összeadását végző függvény
void matrixAddition(int *a, int *b, int *result, int matrix_size)
{
#pragma omp parallel for
    for (int i = 0; i < matrix_size; i++)
    {
        for (int j = 0; j < matrix_size; j++)
        {
            result[i * matrix_size + j] = a[i * matrix_size + j] + b[i * matrix_size + j];
        }
    }
}

int main()
{
    int matrix_size;
    int num_threads;

    printf("Enter matrix size: ");
    scanf("%d", &matrix_size);

    printf("Enter number of threads: ");
    scanf("%d", &num_threads);
    
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);

    int *a = malloc(matrix_size * matrix_size * sizeof(int));
    int *b = malloc(matrix_size * matrix_size * sizeof(int));
    int *result = malloc(matrix_size * matrix_size * sizeof(int));

    printf("Generating random values for Matrix A...\n");
    for (int i = 0; i < matrix_size; i++)
    {
        for (int j = 0; j < matrix_size; j++)
        {
            a[i * matrix_size + j] = rand() % 100;
        }
    }

    printf("Generating random values for Matrix B...\n");
    for (int i = 0; i < matrix_size; i++)
    {
        for (int j = 0; j < matrix_size; j++)
        {
            b[i * matrix_size + j] = rand() % 100;
        }
    }

    matrixAddition(a, b, result, matrix_size);

    printf("Matrix A:\n");
    printMatrix(a, matrix_size);
    printf("\n");

    printf("Matrix B:\n");
    printMatrix(b, matrix_size);
    printf("\n");

    printf("Matrix Addition Result:\n");
    printMatrix(result, matrix_size);
    printf("\n");

    gettimeofday(&end_time, NULL);

    // Az eltelt idő meghatározása és kiírása
    long start_sec = start_time.tv_sec;
    long start_usec = start_time.tv_usec;
    long end_sec = end_time.tv_sec;
    long end_usec = end_time.tv_usec;

    long seconds = end_sec - start_sec;
    long microseconds = end_usec - start_usec;
    double elapsed_time = seconds + (microseconds / 1e6);

    if (microseconds < 0)
    {
        seconds--;
        microseconds += 1000000;
    }

    // Eltelt idő kiíratása
    printf("Elapsed Time: %.6f seconds\n", elapsed_time);

    // Dinamikusan foglalt memória felszabadítása
    free(a);
    free(b);
    free(result);

    return 0;
}
