#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <omp.h>
#include <cmath>
#include <iostream>
#include <cstring>

#include <stdio.h>

void lab1() {
	cudaDeviceProp prop;

	if (cudaGetDeviceProperties(&prop, 0) != cudaSuccess) {
		printf("Could not get device properties");
		return;
	}

	FILE* f = fopen("results.txt", "w");

	fprintf(f, "Имя устройства %s\n", prop.name);
	fprintf(f, "Глобальная память = %d\n", prop.totalGlobalMem);
	fprintf(f, "Общая память на блок = %d\n", prop.sharedMemPerBlock);
	fprintf(f, "Количество 32-битных регистров на блок = %d\n", prop.regsPerBlock);
	fprintf(f, "Размер варпа = %d\n", prop.warpSize);
	fprintf(f, "Максимальный Pitch для функции cudaMallocpitch = %d\n ", prop.memPitch);
	fprintf(f, "Max число активных нитей в блоке = %d\n", prop.maxThreadsPerBlock);
	fprintf(f, "Max размер блока по каждому измерению = %d %d %d\n", prop.maxThreadsDim[0], prop.maxThreadsDim[1], prop.maxThreadsDim[2]);
	fprintf(f, "Max размер сетки по каждому измерению = %d %d %d\n", prop.maxGridSize[0], prop.maxGridSize[1], prop.maxGridSize[2]);
	fprintf(f, "Частота в килогерцах = %d\n", prop.clockRate);
	fprintf(f, "Объем константной памяти в байтах= %d\n", prop.totalConstMem);
	fprintf(f, "Compute Capability = %d.%d\n", prop.major, prop.minor);
	fprintf(f, "Выравнивание памяти для текстур = %d\n", prop.textureAlignment);
	fprintf(f, "Можно ли копировать и вычислять одновременно = %d\n", prop.deviceOverlap);
	fprintf(f, "Количество мультипроцессоров в GPU = %d\n", prop.multiProcessorCount);
	fprintf(f, "Ограничение на время выполнения ядра = %d\n", prop.kernelExecTimeoutEnabled);

	fclose(f);
}

const int n = 2;
const double tau = 0.01;
const double t0 = 0.0;
double t_max = 100.0;
double y[n] = { 0.0, 0.0 };
double yy[n], ff[n], ffk[n];

double f(double* y, double x, int i) {
	double w = 0.0, a;

	switch (i)
	{
	case 0:
		w = y[1];
		for (int i = 0; i < 10000; ++i) { a = sin((double)i); }
		break;

	case 1:
		for (int i = 0; i < 10000; ++i) { a = sin((double)i); }
		w = expf(-x * y[0]);
		break;
	}

	return w;
}

void lab2() {
	double time_begin, time_end, time_elapsed;

	time_begin = omp_get_wtime();

	for (double t = t0; t < t_max; t += tau)
	{
		for (int i = 0; i < n; ++i)
			ffk[i] = f(y, t, i);

		for (int i = 0; i < n; ++i)
			yy[i] = y[i] + tau * ffk[i];

		for (int i = 0; i < n; ++i)
			ff[i] = f(yy, t + tau, i);

		for (int i = 0; i < n; ++i)
			y[i] += tau * (ffk[i] + ff[i]) / 2.0;
	}

	time_end = omp_get_wtime();
	time_elapsed = time_end - time_begin;
	std::cout << "Time elapsed: " << time_elapsed << std::endl;

	for (int i = 0; i < n; ++i)
	{
		std::cout << "Array[" << i << "]: " << y[i] << std::endl;
	}
}




int main() {
	lab2();
	return 0;
}
