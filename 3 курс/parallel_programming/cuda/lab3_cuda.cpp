//
// Created by Максим Прохоров on 24.04.2025.
//
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <iostream>
#include <iomanip>

#define LENGTH 100.0
#define h 0.1
#define BLOCK_SIZE 32

__global__ void Kernel(double* data, double* nextData, int rows, int cols) {
    int x = blockDim.x * blockIdx.x + threadIdx.x + 1;
    int y = blockDim.y * blockIdx.y + threadIdx.y + 1;

    __syncthreads();

    if (x < rows - 1 && y < cols - 1) {
        nextData[x * cols + y] = 0.25 * (
                data[(x - 1) * cols + y] +
                data[(x + 1) * cols + y] +
                data[x * cols + (y - 1)] +
                data[x * cols + (y + 1)]
        );
    }

    __syncthreads();

    if (x < rows - 1 && y < cols - 1) {
        data[x * cols + y] = nextData[x * cols + y];
    }
}

int main() {
    int rows = LENGTH;
    int cols = LENGTH;
    int dataSize = rows * cols * sizeof(double);

    double* hostGrid = new double[rows * cols];
    double* deviceGrid = nullptr;
    double* deviceNext = nullptr;

    std::fill(hostGrid, hostGrid + rows * cols, 0.0);

    for (int j = 0; j < cols; ++j) {
        double y = j * h;
        hostGrid[j] = 30.0 * sin(M_PI * y);
    }

    for (int i = 0; i < rows; ++i) {
        double x = i * h;
        hostGrid[i * cols + (cols - 1)] = 20.0 * x;
    }

    for (int j = 0; j < cols; ++j) {
        double y = j * h;
        hostGrid[(rows - 1) * cols + j] = 20.0 * y;
    }

    for (int i = 0; i < rows; ++i) {
        double x = i * h;
        hostGrid[i * cols] = 30.0 * x * (100.0 - x);
    }

    cudaMalloc((void**)&deviceGrid, dataSize);
    cudaMalloc((void**)&deviceNext, dataSize);
    cudaMemcpy(deviceGrid, hostGrid, dataSize, cudaMemcpyHostToDevice);
    cudaMemcpy(deviceNext, hostGrid, dataSize, cudaMemcpyHostToDevice);

    cudaEvent_t start, stop;
    float t = 0.0;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start, 0);

    int LMax = 1000;
    dim3 threads(BLOCK_SIZE, BLOCK_SIZE);
    dim3 blocks((rows + BLOCK_SIZE - 1) / BLOCK_SIZE, (cols + BLOCK_SIZE - 1) / BLOCK_SIZE);

    for (int k = 0; k < LMax; k++) {
        Kernel<<<blocks, threads>>>(deviceGrid, deviceNext, rows, cols);
        cudaDeviceSynchronize();
    }

    cudaEventRecord(stop, 0);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&t, start, stop);

    cudaMemcpy(hostGrid, deviceGrid, dataSize, cudaMemcpyDeviceToHost);

    printf("Затраченное время на CUDA выполнение: %.6f секунд\n", t / 1000.0f);

    for (int i = 0; i < 50 && i < rows; ++i) {
        for (int j = 0; j < 50 && j < cols; ++j) {
            printf("%8.2f ", hostGrid[i * cols + j]);
        }
        printf("\n");
    }

    cudaFree(deviceGrid);
    cudaFree(deviceNext);
    delete[] hostGrid;

    return 0;
}