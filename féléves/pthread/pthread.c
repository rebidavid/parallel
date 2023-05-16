#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define MATRIX_SIZE 3
#define NUM_THREADS 3

// Az egyes szálak által használt adatstruktúra
struct ThreadData
{
    int thread_id;
    int *a;
    int *b;
    int *result;
    pthread_barrier_t *barrier;
};

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

// A szál által végrehajtott függvény, ahol a mátrixok összeadása történik
void *matrixAddition(void *threadarg)
{
    struct ThreadData *data = (struct ThreadData *)threadarg;
    int start_row = data->thread_id * (MATRIX_SIZE / NUM_THREADS);
    int end_row = (data->thread_id + 1) * (MATRIX_SIZE / NUM_THREADS);

    // Mátrixok összeadása
    for (int i = start_row; i < end_row; i++)
    {
        for (int j = 0; j < MATRIX_SIZE; j++)
        {
            data->result[i * MATRIX_SIZE + j] = data->a[i * MATRIX_SIZE + j] + data->b[i * MATRIX_SIZE + j];
        }
    }

    // Szinkronizáció a barrier segítségével
    pthread_barrier_wait(data->barrier);

    return NULL;
}

int main()
{
    int a[MATRIX_SIZE * MATRIX_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int b[MATRIX_SIZE * MATRIX_SIZE] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    int result[MATRIX_SIZE * MATRIX_SIZE];

    pthread_t threads[NUM_THREADS];
    struct ThreadData thread_data[NUM_THREADS];
    pthread_barrier_t barrier;

    // Barrier inicializálása a szálak számával
    pthread_barrier_init(&barrier, NULL, NUM_THREADS);

    // Szálak létrehozása és adataik beállítása
    for (int i = 0; i < NUM_THREADS; i++)
    {
        thread_data[i].thread_id = i;
        thread_data[i].a = a;
        thread_data[i].b = b;
        thread_data[i].result = result;
        thread_data[i].barrier = &barrier;
        pthread_create(&threads[i], NULL, matrixAddition, (void *)&thread_data[i]);
    }

    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);

    // Szálak befejezésének várása
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    gettimeofday(&end_time, NULL);

    // Barrier megsemmisítése
    pthread_barrier_destroy(&barrier);

    printf("Matrix A:\n");
    printMatrix(a, MATRIX_SIZE);
    printf("\n");

    printf("Matrix B:\n");
    printMatrix(b, MATRIX_SIZE);
    printf("\n");

    printf("Matrix Addition Result:\n");
    printMatrix(result, MATRIX_SIZE);
    printf("\n");

    // Az eltelt idő meghatározása és kiírása
    long start_sec = start_time.tv_sec;
    long start_usec = start_time.tv_usec;
    long end_sec = end_time.tv_sec;
    long end_usec = end_time.tv_usec;

    long seconds = end_sec - start_sec;
    long microseconds = end_usec - start_usec;
    double elapsed_time = seconds + microseconds / 1e6;

    printf("Elapsed Time: %.6f seconds\n", elapsed_time);

    return 0;
}