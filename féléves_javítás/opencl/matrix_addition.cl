// OpenCL kernel function to perform matrix addition

__kernel void matrixAddition(__global const int* a,
                             __global const int* b,
                             __global int* result,
                             const int matrix_size)
{
    // Get the global ID of the current work-item
    int row = get_global_id(0);
    int col = get_global_id(1);

    // Calculate the index of the current element
    int index = row * matrix_size + col;

    // Perform matrix addition
    result[index] = a[index] + b[index];
}
