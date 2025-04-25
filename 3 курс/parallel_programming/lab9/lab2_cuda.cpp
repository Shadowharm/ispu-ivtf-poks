//
// Created by Максим Прохоров on 25.04.2025.
//
#include <stdio.h>
#include <cuda_runtime.h>

#define N 2
#define TAU 0.001f
#define TMAX 10.0f

__device__ float compute(float* y, float t, int i) {
    if (i == 0) {
        return __sinf(t + y[0] * y[1]);
    } else if (i == 1) {
        return __cosf(t * t - y[0] + y[1]);
    }
    return 0.0f;
}

__global__ void Kernel(float* y, float t) {
    int i = threadIdx.x;

    __shared__ float pred[N];
    float firstEval, secondEval;

    firstEval = compute(y, t, i);
    pred[i] = y[i] + TAU * firstEval;

    __syncthreads();

    secondEval = compute(pred, t + TAU, i);
    y[i] += TAU * 0.5f * (firstEval + secondEval);
}

void setInitialConditions(float* arr) {
    arr[0] = 2.0f;
    arr[1] = 1.0f;
}

int main() {
    float *yHost, *yDevice;
    cudaEvent_t evStart, evStop;
    float duration = 0.0f;

    size_t memSize = N * sizeof(float);

    cudaMalloc(&yDevice, memSize);
    yHost = (float*)malloc(memSize);

    setInitialConditions(yHost);
    cudaMemcpy(yDevice, yHost, memSize, cudaMemcpyHostToDevice);

    cudaEventCreate(&evStart);
    cudaEventCreate(&evStop);
    cudaEventRecord(evStart, 0);

    for (float t = 0.0f; t <= TMAX; t += TAU) {
        Kernel<<<1, N>>>(yDevice, t);
        cudaDeviceSynchronize();
    }

    cudaEventRecord(evStop, 0);
    cudaEventSynchronize(evStop);
    cudaEventElapsedTime(&duration, evStart, evStop);

    cudaMemcpy(yHost, yDevice, memSize, cudaMemcpyDeviceToHost);

    printf("y[0] = %f\n", yHost[0]);
    printf("y[1] = %f\n", yHost[1]);
    printf("Время расчета: %.6f секунд\n", duration / 1000.0f);

    free(yHost);
    cudaFree(yDevice);
    cudaEventDestroy(evStart);
    cudaEventDestroy(evStop);

    return 0;
}