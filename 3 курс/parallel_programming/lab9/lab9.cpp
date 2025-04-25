//
// Created by Максим Прохоров on 09.12.2024.
//

#include "lab9.h"
#include <iostream>
#include <cmath>
#include <omp.h>
#include <mpi.h>

const int N = 2;

int PredictorCorrector(double (*f[])(double*, double), double y[], double startTime, double endTime, double tau, int n) {
    double* yy = new double[n] {0.0};
    double* fk = new double[n] {0.0};
    double* ff = new double[n] {0.0};
    double start = omp_get_wtime();

    for (double t = startTime; t <= endTime; t += tau) {
        for (int i = 0; i < n; i++) {
            fk[i] = f[i](y, t);
        }

        for (int i = 0; i < n; i++) {
            yy[i] = y[i] + tau * fk[i];
        }

        for (int i = 0; i < n; i++) {
            ff[i] = f[i](yy, t);
        }

        for (int i = 0; i < n; i++) {
            y[i] = y[i] + 0.5 * tau * (fk[i] + ff[i]);
        }

    }
    printf("Затраченное время на последовательное выполнение: %f\n", omp_get_wtime() - start);
    delete[] yy;
    delete[] fk;
    delete[] ff;
    return 1;
}


double F1(double * y, double x) {
    return sin(x + y[0] * y[1]);
}

double F2(double* y, double x) {
    return cos(x * x - y[0] + y[1]);
}

double (*f[N])(double*, double) = { F1, F2 };



void lab9(int rank, int size, int root) {
    int omp = 0;
    int mpi = 1;
    int basic = 0;

    double tmax = 10.0;
    double tau = 0.001;
    if (basic){
        double y[N] = {2.0, 1.0};
        double t = 0.0;
        PredictorCorrector(f, y, t, tmax, tau, N);
        for (int i = 0; i < N; i++) {
            printf("y[%d]: %f ", i, y[i]);
        }
    }
    if (mpi){
        double y[N] = {2.0, 1.0};
        double yy[N] = {0.0, 0.0};
        double fk = 0.0;
        double ff = 0.0;
        double t = 0.0;

        double tstart = omp_get_wtime();

        int items_per_proc = (N + size) / size;
        int start = rank * items_per_proc;
        int end = (start + items_per_proc > N) ? N : start + items_per_proc;

        do {
            for (int i = start; i < end; i++) {
                fk = f[i](y, t);
            }

//            MPI_Allgather(MPI_IN_PLACE, 0, MPI_DATATYPE_NULL,
//                          fk, items_per_proc, MPI_DOUBLE, MPI_COMM_WORLD);

            for (int i = start; i < end; i++) {
                yy[i] = y[i] + tau * fk;
            }

            MPI_Allgather(MPI_IN_PLACE, 0, MPI_DATATYPE_NULL,
                          yy, items_per_proc, MPI_DOUBLE, MPI_COMM_WORLD);

            for (int i = start; i < end; i++) {
                ff = f[i](yy, t + tau);
            }

//            MPI_Allgather(MPI_IN_PLACE, 0, MPI_DATATYPE_NULL,
//                          ff, items_per_proc, MPI_DOUBLE, MPI_COMM_WORLD);

            for (int i = start; i < end; i++) {
                y[i] += tau * (fk + ff) / 2.0;
            }

            MPI_Allgather(MPI_IN_PLACE, 0, MPI_DATATYPE_NULL,
                          y, items_per_proc, MPI_DOUBLE, MPI_COMM_WORLD);

            t += tau;

        } while (t <= tmax);

        double tend = omp_get_wtime();

        if (rank == 0) {
            printf("\nЗатраченное время на MPI параллельное выполнение: %f\n", tend - tstart);
            for (int i = 0; i < N; i++) {
                printf("y[%d]: %f ", i, y[i]);
            }
            printf("\n");
        }

    }

    if (omp) {
        double y[N] = {2.0, 1.0};
        double yy[N] = {0.0, 0.0};
        double fk[N] = {0.0};
        double ff[N] = {0.0};
        double t = 0.0;
        double tstart = omp_get_wtime();

#pragma omp parallel num_threads(2)
        {

            do {

#pragma omp for schedule(dynamic)
                for (int i = 0; i < N; i++) {
                    fk[i] = f[i](y, t);
                }

#pragma omp for schedule(dynamic)
                for (int i = 0; i < N; i++) {
                    yy[i] = y[i] + tau * fk[i];
                }


#pragma omp for schedule(dynamic)
                for (int i = 0; i < N; i++) {
                    ff[i] = f[i](yy, t + tau);
                }


#pragma omp for schedule(dynamic)
                for (int i = 0; i < N; i++) {
                    y[i] += tau * (fk[i] + ff[i]) / 2.0;
                }
#pragma omp master
                t += tau;
#pragma omp barrier
            } while (t <= tmax);
        }

        double tend = omp_get_wtime();

        printf("\nЗатраченное время на OMP параллельное выполнение: %f\n", tend - tstart);

        for (int i = 0; i < N; i++) {
            printf("y[%d]: %f ", i, y[i]);
        }
    }
}