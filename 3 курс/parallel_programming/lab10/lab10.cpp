//
// Created by Максим Прохоров on 11.12.2024.
// Вариант 14
//

#include "lab10.h"
#include <iostream>
#include <cmath>
#include <chrono>
#include <omp.h>
#include <mpi.h>

double func(double x) {
    return 1/x*log10(x);
}

double rectangle_method(double a, double b, double h) {
    double result = 0.0;
    for (double x = a + h / 2; x < b; x += h) {
        result += func(x) * h;
    }
    return result;
}

double trapezoidal_method(double a, double b, double h) {
    double result = (func(a) + func(b)) / 2.0;
    for (double x = a + h; x < b; x += h) {
        result += func(x);
    }
    result *= h;
    return result;
}


double rectangle_method_parallel(double a, double b, double h, int num_threads) {
    double result = 0.0;
    int n = static_cast<int>((b - a) / h);
#pragma omp parallel for reduction(+:result) num_threads(num_threads)
    for (int i = 0; i < n; ++i) {
        double x = a + (i + 0.5) * h;
        result += func(x) * h;
    }
    return result;
}

double trapezoidal_method_parallel(double a, double b, double h, int num_threads) {
    double result = (func(a) + func(b)) / 2.0;
    int n = static_cast<int>((b - a) / h);
#pragma omp parallel for reduction(+:result) num_threads(num_threads)
    for (int i = 1; i < n; ++i) {
        double x = a + i * h;
        result += func(x);
    }
    result *= h;
    return result;
}

double rectangle_method_mpi(double a, double b, double h, int rank, int size) {
    double local_result = 0.0;

    double local_a = a + rank * (b - a) / size;
    double local_b = a + (rank + 1) * (b - a) / size;

    for (double x = local_a + h / 2; x < local_b; x += h) {
        local_result += func(x) * h;
    }

    return local_result;
}

double trapezoidal_method_mpi(double a, double b, double h, int rank, int size) {
    double local_result = 0.0;

    double local_a = a + rank * (b - a) / size;
    double local_b = a + (rank + 1) * (b - a) / size;

    local_result += (func(local_a) + func(local_b)) / 2.0;
    for (double x = local_a + h; x < local_b; x += h) {
        local_result += func(x);
    }
    local_result *= h;

    return local_result;
}

void lab10(int rank, int size) {
    const double a = 2.0, b = 30.0;
    const double h = 0.00001;
    const int num_threads = 8;


    if (rank == 0) {
        std::cout << "=== Последовательные методы ===" << std::endl;

        auto start = std::chrono::high_resolution_clock::now();
        double seq_rectangle = rectangle_method(a, b, h);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Метод прямоугольника: " << seq_rectangle
                  << " (Время: " << std::chrono::duration<double>(end - start).count() << "с)" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        double seq_trapezoidal = trapezoidal_method(a, b, h);
        end = std::chrono::high_resolution_clock::now();
        std::cout << "Метод трапеции: " << seq_trapezoidal
                  << " (Время: " << std::chrono::duration<double>(end - start).count() << "с)" << std::endl;
    }

    double mpi_rectangle_result = rectangle_method_mpi(a, b, h, rank, size);
    double mpi_trapezoidal_result = trapezoidal_method_mpi(a, b, h, rank, size);

    double global_rectangle_result = 0.0, global_trapezoidal_result = 0.0;

    double mpi_start_time = MPI_Wtime();
    mpi_rectangle_result = rectangle_method_mpi(a, b, h, rank, size);
    double mpi_rectangle_time = MPI_Wtime() - mpi_start_time;

    mpi_start_time = MPI_Wtime();
    mpi_trapezoidal_result = trapezoidal_method_mpi(a, b, h, rank, size);
    double mpi_trapezoidal_time = MPI_Wtime() - mpi_start_time;

    MPI_Reduce(&mpi_rectangle_result, &global_rectangle_result, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&mpi_trapezoidal_result, &global_trapezoidal_result, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        std::cout << "\n=== Методы MPI ===" << std::endl;
        std::cout << "Метод прямогуьника (MPI): " << global_rectangle_result
                << " (Время: " << mpi_rectangle_time << "s)" << std::endl;
        std::cout << "Метод трапеции (MPI): " << global_trapezoidal_result
                << " (Время: " << mpi_trapezoidal_time << "s)" << std::endl;
    }

    if (rank == 0) {
        std::cout << "\n=== Методы OpenMP ===" << std::endl;

        double start = omp_get_wtime();
        double omp_rectangle = rectangle_method_parallel(a, b, h, num_threads);
        double end = omp_get_wtime();
        std::cout << "Метод прямогульника (OpenMP): " << omp_rectangle
                  << " (Время: " << end - start << "s)" << std::endl;

        start = omp_get_wtime();
        double omp_trapezoidal = trapezoidal_method_parallel(a, b, h, num_threads);
        end = omp_get_wtime();
        std::cout << "Метод трапеции (OpenMP): " << omp_trapezoidal
                  << " (Время: " << end - start << "s)" << std::endl;
    }

    MPI_Finalize();
}