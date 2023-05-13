#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>

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
    cl_platform_id platform;
    cl_device_id device;
    cl_context context;
    cl_command_queue queue;
    cl_program program;
    cl_kernel kernel;
    cl_int err;

    // Platform kiválasztása
    err = clGetPlatformIDs(1, &platform, NULL);

    // Eszköz kiválasztása
    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_DEFAULT, 1, &device, NULL);

    // OpenCL kontextus létrehozása
    context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);

    // OpenCL parancssor létrehozása
    queue = clCreateCommandQueue(context, device, 0, &err);

    // Kernel program betöltése és fordítása
    const char *source = "__kernel void matrix_add(__global const int* a, __global const int* b, __global int* result) {\n"
                         "    int row = get_global_id(0);\n"
                         "    int col = get_global_id(1);\n"
                         "    int size = get_global_size(0);\n"
                         "    result[row * size + col] = a[row * size + col] + b[row * size + col];\n"
                         "}\n";
    program = clCreateProgramWithSource(context, 1, &source, NULL, &err);
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);

    // Kernel függvény létrehozása
    kernel = clCreateKernel(program, "matrix_add", &err);

    // Mátrixok létrehozása és adatok feltöltése
    int a[MATRIX_SIZE * MATRIX_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int b[MATRIX_SIZE * MATRIX_SIZE] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    int result[MATRIX_SIZE * MATRIX_SIZE];

    cl_mem a_buf = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int) * MATRIX_SIZE * MATRIX_SIZE, a, &err);
    cl_mem b_buf = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int) * MATRIX_SIZE * MATRIX_SIZE, b, &err);
    cl_mem result_buf = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(int) * MATRIX_SIZE * MATRIX_SIZE, NULL, &err);

    // Kernel argumentumok beállítása
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &a_buf);
        clSetKernelArg(kernel, 1, sizeof(cl_mem), &b_buf);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &result_buf);

    // Kernel futtatása
    size_t global_size[2] = {MATRIX_SIZE, MATRIX_SIZE};
    err = clEnqueueNDRangeKernel(queue, kernel, 2, NULL, global_size, NULL, 0, NULL, NULL);

    // Eredmények visszamásolása a hoszt memóriába
    err = clEnqueueReadBuffer(queue, result_buf, CL_TRUE, 0, sizeof(int) * MATRIX_SIZE * MATRIX_SIZE, result, 0, NULL, NULL);

    // Tisztítás és eredmények kiírása
    clReleaseMemObject(a_buf);
    clReleaseMemObject(b_buf);
    clReleaseMemObject(result_buf);
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);

    printf("Matrix A:\n");
    printMatrix(a, MATRIX_SIZE);
    printf("\n");

    printf("Matrix B:\n");
    printMatrix(b, MATRIX_SIZE);
    printf("\n");

    printf("Matrix Addition Result:\n");
    printMatrix(result, MATRIX_SIZE);
    printf("\n");

    return 0;
}