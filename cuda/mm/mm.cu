#include <stdio.h>
#include <stdlib.h>

__global__ 
void matrixMulKernel(double* a, double* b, double* c, int width) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    if (row < width && col < width) {
        double sum = 0;
        for (int k = 0; k < width; k++) {
            double x = a[row * width + k];
            double y = b[k * width + col];
            sum += x * y;
        }
        c[row * width + col] = sum;
    }
}

void matrixMulCPU(double* a, double* b, double* c, int width) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < width; j++) {
            double sum = 0;
            for (int k = 0; k < width; k++) {
                double x = a[i * width + k];
                double y = b[k * width + j];
                sum += x * y;
            }
            c[i * width + j] = sum;
        }
    }
}

int main() {
    int width = 2000;
    size_t size = width * width * sizeof(double);

    double *h_a = (double*) malloc(size);
    double *h_b = (double*) malloc(size);
    double *h_c = (double*) malloc(size);

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < width; j++) {
            h_a[i * width + j] = i;
            h_b[i * width + j] = j;
            h_c[i * width + j] = 0;
        }
    }

    double *d_a, *d_b, *d_c;
    cudaMalloc(&d_a, size);
    cudaMalloc(&d_b, size);
    cudaMalloc(&d_c, size);

    cudaMemcpy(d_a, h_a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, size, cudaMemcpyHostToDevice);

    dim3 dimBlock(16, 16);
    dim3 dimGrid((width + dimBlock.x - 1) / dimBlock.x, (width + dimBlock.y - 1) / dimBlock.y);

    matrixMulKernel<<<dimGrid, dimBlock>>>(d_a, d_b, d_c, width);

    cudaMemcpy(h_c, d_c, size, cudaMemcpyDeviceToHost);

    // Uncomment to check results
    // for (int i = 0; i < width; i++) {
    //     for (int j = 0; j < width; j++) {
    //         printf("c[%d][%d] = %f\n", i, j, h_c[i * width + j]);
    //     }
    // }

    free(h_a);
    free(h_b);
    free(h_c);
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    return 0;
}