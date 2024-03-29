#define CL_TARGET_OPENCL_VERSION 220

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
void check_error(cl_int err, const char *message)
{
    if (err != CL_SUCCESS)
    {
        fprintf(stderr, "%s: %d\n", message, err);
        exit(EXIT_FAILURE);
    }
}

const char *kernelSource = "__kernel void matrixAddition(__global const int* a, \
                                                         __global const int* b, \
                                                         __global int* result, \
                                                         const int matrix_size) \
                            { \
                                int row = get_group_id(0) * get_local_size(0) + get_local_id(0); \
                                int col = get_group_id(1) * get_local_size(1) + get_local_id(1); \
                                int index = row * matrix_size + col; \
                                if (index < matrix_size * matrix_size) { \
                                    result[index] = a[index] + b[index]; \
                                } \
                            }";

int main()
{
    cl_platform_id platform;
    cl_device_id device;
    cl_context context;
    cl_command_queue queue;
    cl_program program;
    cl_kernel kernel;
    int matrix_size;
    unsigned int num_threads;

    printf("Enter matrix size: ");
    scanf("%d", &matrix_size);

    printf("Enter number of threads: ");
    scanf("%u", &num_threads);

    struct timeval start, end;
    gettimeofday(&start, NULL); // Start timing

    // OpenCL platform inicializálása
    cl_int err = clGetPlatformIDs(1, &platform, NULL);
    check_error(err, "Failed to get platform IDs");

    // OpenCL eszköz inicializálása
    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
    check_error(err, "Failed to get device IDs");

    // OpenCL kontextus létrehozása
    context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
    check_error(err, "Failed to create context");

    // OpenCL parancs sor létrehozása
    cl_queue_properties properties[] = {CL_QUEUE_PROPERTIES, CL_QUEUE_PROFILING_ENABLE, 0};
    queue = clCreateCommandQueueWithProperties(context, device, properties, &err);
    check_error(err, "Failed to create command queue");

    // OpenCL program létrehozása és fordítása
    program = clCreateProgramWithSource(context, 1, &kernelSource, NULL, &err);
    check_error(err, "Failed to create program with source");

    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS)
    {
        size_t logSize;
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &logSize);
        char *log = (char *)malloc(logSize);
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, logSize, log, NULL);
        printf("%s\n", log);
        free(log);
        exit(EXIT_FAILURE);
    }

    // OpenCL kernel létrehozása
    kernel = clCreateKernel(program, "matrixAddition", &err);
    check_error(err, "Failed to create kernel");

    // Munkacsoport méretének ellenőrzése
    size_t max_work_group_size;
    err = clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(size_t), &max_work_group_size, NULL);
    check_error(err, "Failed to get device max work group size");

    if (num_threads > max_work_group_size)
    {
        printf("Error: Number of threads exceeds the maximum work group size\n");
        exit(EXIT_FAILURE);
    }

    // Mátrix inicializálása és másolása a készülékre
    int matrix_size_squared = matrix_size * matrix_size;
    int *matrix_a = (int *)malloc(sizeof(int) * matrix_size_squared);
    int *matrix_b = (int *)malloc(sizeof(int) * matrix_size_squared);
    int *matrix_result = (int *)malloc(sizeof(int) * matrix_size_squared);

    for (int i = 0; i < matrix_size_squared; i++)
    {
        matrix_a[i] = i;
        matrix_b[i] = i;
    }

    // Mátrixok másolása a készülékre
    cl_mem matrix_a_dev = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                         sizeof(int) * matrix_size_squared, matrix_a, &err);
    check_error(err, "Failed to create buffer for matrix A");

    cl_mem matrix_b_dev = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                         sizeof(int) * matrix_size_squared, matrix_b, &err);
    check_error(err, "Failed to create buffer for matrix B");

    cl_mem matrix_result_dev = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                              sizeof(int) * matrix_size_squared, NULL, &err);
    check_error(err, "Failed to create buffer for matrix result");

    // Kernel argumentumok beállítása
    err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &matrix_a_dev);
    check_error(err, "Failed to set kernel argument 0");

    err = clSetKernelArg(kernel, 1, sizeof(cl_mem), &matrix_b_dev);
    check_error(err, "Failed to set kernel argument 1");

    err = clSetKernelArg(kernel, 2, sizeof(cl_mem), &matrix_result_dev);
    check_error(err, "Failed to set kernel argument 2");

    err = clSetKernelArg(kernel, 3, sizeof(int), &matrix_size);
    check_error(err, "Failed to set kernel argument 3");

    size_t global_size[2] = {((matrix_size + num_threads - 1) / num_threads) * num_threads, ((matrix_size + num_threads - 1) / num_threads) * num_threads};
    size_t local_size[2] = {num_threads, num_threads};

    // Ellenőrizzük, hogy a globális méret osztható-e a lokális mérettel
    if (global_size[0] % local_size[0] != 0 || global_size[1] % local_size[1] != 0)
    {
        printf("Error: Global size is not divisible by local size\n");
        exit(EXIT_FAILURE);
    }

    err = clEnqueueNDRangeKernel(queue, kernel, 2, NULL, global_size, local_size, 0, NULL, NULL);

    // Eredmény másolása a készülékről
    err = clEnqueueReadBuffer(queue, matrix_result_dev, CL_TRUE, 0,
                              sizeof(int) * matrix_size_squared, matrix_result, 0, NULL, NULL);
    check_error(err, "Failed to read buffer");

    gettimeofday(&end, NULL); // Stop timing
    double elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;

    printf("Elapsed time: %.6f seconds\n", elapsed_time);

    // Tisztítás és erőforrások felszabadítása
    clReleaseMemObject(matrix_a_dev);
    clReleaseMemObject(matrix_b_dev);
    clReleaseMemObject(matrix_result_dev);
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);
    free(matrix_a);
    free(matrix_b);
    free(matrix_result);

    return 0;
}