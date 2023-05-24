<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>


//barrier: lehetővé teszi, hogy a szálak megálljanak addig, amíg minden szál el ne ért a barrierhez
// Az egyes szálak által használt adatstruktúra
struct ThreadData
{
    int thread_id;
    int *a;         //bemeneti mátrix
    int *b;
    int *result;    //eredmény mátrix
    int matrix_size; // mátrix méret
    int num_threads; // Hozzáadott adattag - szálak száma
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
    int start_row = data->thread_id * (data->matrix_size / data->num_threads);
    int end_row = (data->thread_id + 1) * (data->matrix_size / data->num_threads);

    // Mátrixok összeadása
    for (int i = start_row; i < end_row; i++)
    {
        for (int j = 0; j < data->matrix_size; j++)
        {
            data->result[i * data->matrix_size + j] = data->a[i * data->matrix_size + j] + data->b[i * data->matrix_size + j];
        }
    }

    // Szinkronizáció a barrier segítségével
    pthread_barrier_wait(data->barrier);

    return NULL;
}

int main()
{
    int matrix_size;
    int num_threads;

    //adatok bekérése
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
            a[i * matrix_size + j] = rand() % 10; // Random értékek 0 és 9 között
        }
    }

    printf("Generating random values for Matrix B...\n");
    for (int i = 0; i < matrix_size; i++)
    {
        for (int j = 0; j < matrix_size; j++)
        {
            b[i * matrix_size + j] = rand() % 10; // Random értékek 0 és 9 között
        }
    }

    pthread_t *threads = malloc(num_threads * sizeof(pthread_t));
    struct ThreadData *thread_data = malloc(num_threads * sizeof(struct ThreadData));
    pthread_barrier_t barrier;
    // Barrier inicializálása a szálak számával
    pthread_barrier_init(&barrier, NULL, num_threads);

    // Szálak létrehozása és adataik beállítása
    for (int i = 0; i < num_threads; i++)
    {
        thread_data[i].thread_id = i;
        thread_data[i].a = a;
        thread_data[i].b = b;
        thread_data[i].result = result;
        thread_data[i].matrix_size = matrix_size;
        thread_data[i].num_threads = num_threads; // Hozzáadott sor - szálak száma
        thread_data[i].barrier = &barrier;
        pthread_create(&threads[i], NULL, matrixAddition, (void *)&thread_data[i]);
    }

    // Szálak befejezésének várása
    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // Barrier megsemmisítése
    pthread_barrier_destroy(&barrier);

    /*printf("Matrix A:\n");
    printMatrix(a, matrix_size);
    printf("\n");

    printf("Matrix B:\n");
    printMatrix(b, matrix_size);
    printf("\n");

    printf("Matrix Addition Result:\n");
    printMatrix(result, matrix_size);
    printf("\n");*/

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

    printf("Elapsed Time: %.6f seconds\n", elapsed_time);

    // Dinamikusan foglalt memória felszabadítása
    free(a);
    free(b);
    free(result);
    free(threads);
    free(thread_data);

    return 0;
}
=======
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

// Az egyes szálak által használt adatstruktúra
struct ThreadData
{
    int thread_id;
    int *a;
    int *b;
    int *result;
    int matrix_size;
    int num_threads; // Hozzáadott adattag - szálak száma
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
    int start_row = data->thread_id * (data->matrix_size / data->num_threads);
    int end_row = (data->thread_id + 1) * (data->matrix_size / data->num_threads);

    // Mátrixok összeadása
    for (int i = start_row; i < end_row; i++)
    {
        for (int j = 0; j < data->matrix_size; j++)
        {
            data->result[i * data->matrix_size + j] = data->a[i * data->matrix_size + j] + data->b[i * data->matrix_size + j];
        }
    }

    // Szinkronizáció a barrier segítségével
    pthread_barrier_wait(data->barrier);

    return NULL;
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
            a[i * matrix_size + j] = rand() % 100; // Random értékek 0 és 99 között
        }
    }

    printf("Generating random values for Matrix B...\n");
    for (int i = 0; i < matrix_size; i++)
    {
        for (int j = 0; j < matrix_size; j++)
        {
            b[i * matrix_size + j] = rand() % 100; // Random értékek 0 és 99 között
        }
    }

    pthread_t *threads = malloc(num_threads * sizeof(pthread_t));
    struct ThreadData *thread_data = malloc(num_threads * sizeof(struct ThreadData));
    pthread_barrier_t barrier;
    // Barrier inicializálása a szálak számával
    pthread_barrier_init(&barrier, NULL, num_threads);

    // Szálak létrehozása és adataik beállítása
    for (int i = 0; i < num_threads; i++)
    {
        thread_data[i].thread_id = i;
        thread_data[i].a = a;
        thread_data[i].b = b;
        thread_data[i].result = result;
        thread_data[i].matrix_size = matrix_size;
        thread_data[i].num_threads = num_threads; // Hozzáadott sor - szálak száma
        thread_data[i].barrier = &barrier;
        pthread_create(&threads[i], NULL, matrixAddition, (void *)&thread_data[i]);
    }

    // Szálak befejezésének várása
    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // Barrier megsemmisítése
    pthread_barrier_destroy(&barrier);

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

    printf("Elapsed Time: %.6f seconds\n", elapsed_time);

    // Dinamikusan foglalt memória felszabadítása
    free(a);
    free(b);
    free(result);
    free(threads);
    free(thread_data);

    return 0;
}
>>>>>>> 83bdacbb457aa0c7f42d6d96a65a597821a58f9a
