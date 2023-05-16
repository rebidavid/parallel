#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <CL/cl.h>

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

// OpenCL hibakezelő függvény
void checkError(cl_int err, const char *message)
{
    if (err != CL_SUCCESS)
    {
        printf("Error: %s (%d)\n", message, err);
        exit(EXIT_FAILURE);
    }
}

int main()
{
    cl_platform_id platform;
    cl_device_id device;
    cl_context context;
    cl_command_queue queue;
    cl_program program;
    cl_kernel kernel;
    int matrix_size;
    int num_threads;

    printf("Enter matrix size: ");
    scanf("%d", &matrix_size);

    printf("Enter number of threads: ");
    scanf("%d", &num_threads);
    
    struct timeval start, end;
    gettimeofday(&start, NULL); // Start timing

    // OpenCL platform inicializálása
    cl_int err = clGetPlatformIDs(1, &platform, NULL);
    checkError(err, "Failed to get platform IDs");

    // OpenCL eszköz inicializálása
    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
    checkError(err, "Failed to get device IDs");

    // OpenCL kontextus létrehozása
    context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
    checkError(err, "Failed to create context");

    // OpenCL parancs sor létrehozása
    queue = clCreateCommandQueue(context, device, 0, &err);
    checkError(err, "Failed to create command queue");

    // OpenCL kernel forrás beolvasása és program létrehozása
    FILE *file = fopen("matrix_addition.cl", "r");
    if (!file)
    {
        printf("Failed to open kernel source file");
        exit(EXIT_FAILURE);
    }
    fseek(file, 0, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);
    char *source = (char *)malloc(fileSize + 1);
    fread(source, sizeof(char), fileSize, file);
    source[fileSize] = '\0';
    fclose(file);

    program = clCreateProgramWithSource(context, 1, (const char **)&source, &fileSize, &err);
    checkError(err, "Failed to create program with source");

    // OpenCL program fordítása és kernel létrehozása
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS)
    {
        size_t logSize;
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &logSize);
        char *log = (char *)malloc(logSize);
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, logSize, log, NULL);
        printf("Build log:\n%s\n", log);
        free(log);
        exit(EXIT_FAILURE);
    }
    kernel = clCreateKernel(program, "matrixAddition", &err);
    checkError(err, "Failed to create kernel");

    // Mátrixok létrehozása és inicializálása
    int *a = (int *)malloc(matrix_size * matrix_size * sizeof(int));
    int *b = (int *)malloc(matrix_size * matrix_size * sizeof(int));
    int *result = (int *)malloc(matrix_size * matrix_size * sizeof(int));
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

    // OpenCL bufferek létrehozása és adatok feltöltése
    cl_mem aBuffer = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                    matrix_size * matrix_size * sizeof(int), a, &err);
    checkError(err, "Failed to create buffer for Matrix A");

    cl_mem bBuffer = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                    matrix_size * matrix_size * sizeof(int), b, &err);
    checkError(err, "Failed to create buffer for Matrix B");

    cl_mem resultBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                         matrix_size * matrix_size * sizeof(int), NULL, &err);
    checkError(err, "Failed to create buffer for Result Matrix");

    // Kernel argumentumok beállítása
    err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &aBuffer);
    checkError(err, "Failed to set kernel argument 0");

    err = clSetKernelArg(kernel, 1, sizeof(cl_mem), &bBuffer);
    checkError(err, "Failed to set kernel argument 1");

    err = clSetKernelArg(kernel, 2, sizeof(cl_mem), &resultBuffer);
    checkError(err, "Failed to set kernel argument 2");

    err = clSetKernelArg(kernel, 3, sizeof(int), &matrix_size);
    checkError(err, "Failed to set kernel argument 3");

    // Kernel indítása
    size_t globalSize[2] = {matrix_size, matrix_size};

    err = clEnqueueNDRangeKernel(queue, kernel, 2, NULL, globalSize, NULL, 0, NULL, NULL);
    checkError(err, "Failed to enqueue kernel");

    // Eredmény átmásolása a host memóriába
    err = clEnqueueReadBuffer(queue, resultBuffer, CL_TRUE, 0,
                              matrix_size * matrix_size * sizeof(int), result, 0, NULL, NULL);
    checkError(err, "Failed to read buffer");

    // Mátrixok kiírása
    printf("Matrix A:\n");
    printMatrix(a, matrix_size);
    printf("\n");

    printf("Matrix B:\n");
    printMatrix(b, matrix_size);
    printf("\n");
    printf("Matrix Addition Result:\n");
    printMatrix(result, matrix_size);
    printf("\n");
    
    gettimeofday(&end, NULL); // End timing
    double elapsedTime = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    printf("Execution Time: %.6f seconds\n", elapsedTime);

    // OpenCL erőforrások felszabadítása
    clReleaseMemObject(aBuffer);
    clReleaseMemObject(bBuffer);
    clReleaseMemObject(resultBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);

    // Dinamikusan foglalt memória felszabadítása
    free(a);
    free(b);
    free(result);

    return 0;
}