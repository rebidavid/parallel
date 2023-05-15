#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MATRIX_SIZE 3

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

int main()
{
    int a[MATRIX_SIZE * MATRIX_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int b[MATRIX_SIZE * MATRIX_SIZE] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    int result[MATRIX_SIZE * MATRIX_SIZE];

    double start_time = omp_get_wtime(); // Start measuring time

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        for (int j = 0; j < MATRIX_SIZE; j++)
        {
            result[i * MATRIX_SIZE + j] = a[i * MATRIX_SIZE + j] + b[i * MATRIX_SIZE + j];
        }
    }

    double end_time = omp_get_wtime(); // End measuring time

    printf("Matrix A:\n");
    printMatrix(a, MATRIX_SIZE);
    printf("\n");

    printf("Matrix B:\n");
    printMatrix(b, MATRIX_SIZE);
    printf("\n");

    printf("Matrix Addition Result:\n");
    printMatrix(result, MATRIX_SIZE);
    printf("\n");

    double execution_time = end_time - start_time;
    printf("Execution Time: %f seconds\n", execution_time);

    return 0;
}
