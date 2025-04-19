//
// Created by Максим Прохоров on 09.12.2024.
//

#include "lab9.h"
#include <iostream>
#include <cmath>
#include <omp.h>
#include <fstream>
#include <math.h>
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

//void PredictorCorrectorMpi(int rank, int size, double (*f[])(double*, double), int n, double* yOrig, double t, double tMax, double tau)
//{
//    double* y = yOrig, * yy = new double[n] {0.0}, * ff = new double[n] {0.0}, * ffPred = new double[n] {0.0};
//    int mstag = 0;
//    MPI_Status status;
//
//    double tstart = omp_get_wtime();
//    do
//    {
//        if (!rank)
//        {
//            double tmp;
//            for (int i = 0; i < n; i++)
//            {
//                for (int j = 0; j < n; j++)
//                {
//                    MPI_Recv(&tmp, 1, MPI_DOUBLE, MPI_ANY_SOURCE, mstag, MPI_COMM_WORLD, &status);
//                    yy[status.MPI_SOURCE - 1] = tmp;
//                }
//                for (int j = 0; j < n; j++)
//                {
//                    MPI_Send(yy, n, MPI_DOUBLE, j + 1, mstag, MPI_COMM_WORLD);
//                }
//            }
//        }
//        else
//        {
//            ff[rank - 1] = f[rank - 1](y, t);
//            yy[rank - 1] = y[rank - 1] + tau * ff[rank - 1];
//
//            MPI_Send(&yy[rank - 1], 1, MPI_DOUBLE, 0, mstag, MPI_COMM_WORLD);
//            MPI_Recv(yy, n, MPI_DOUBLE, 0, mstag, MPI_COMM_WORLD, &status);
//
//            ffPred[rank - 1] = f[rank - 1](yy, t + tau);
//            yy[rank - 1] = y[rank - 1] + tau * (ffPred[rank - 1] + ff[rank - 1]) / 2.0;
//
//            MPI_Send(&yy[rank - 1], 1, MPI_DOUBLE, 0, mstag, MPI_COMM_WORLD);
//            MPI_Recv(y, n, MPI_DOUBLE, 0, mstag, MPI_COMM_WORLD, &status);
//        }
//        t += tau;
//    } while (t <= tMax);
//
//    double tend = omp_get_wtime();
//
//    printf("Затраченное время на MPI параллельное выполнение: %f\n", tend - tstart);
//    if (!rank) {
//        for (int i = 0; i < N; i++) {
//            printf("y[%d]: %f ", i, yy[i]);
//        }
//
//    }
//}

void predictor_corrector_mpi(double y[], double startTime, double endTime, double tau, int n, int rank, int size) {
    double yy[N] = {0.0};
    double fk[N] = {0.0};
    double ff[N] = {0.0};

    for (double t = startTime; t <= endTime; t += tau) {
        MPI_Bcast(y, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

        if (rank < n) {
            fk[rank] = f[rank](y, t);
            yy[rank] = y[rank] + tau * fk[rank];
            ff[rank] = f[rank](yy, t);
            y[rank] = y[rank] + 0.5 * tau * (fk[rank] + ff[rank]);
        }

        MPI_Allgather(MPI_IN_PLACE, 0, MPI_DATATYPE_NULL, y, 1, MPI_DOUBLE, MPI_COMM_WORLD);
    }
}


void lab9(int rank, int size, int root) {
//    {
//        double y[N] = {2.0, 1.0};
//        double tmax = 10.0;
//        double tau = 0.001;
//        double t = 0.0;
//        PredictorCorrector(f, y, t, tmax, tau, N);
//    }
//    {
//
//        double y[N] = {2.0, 1.0};
//        double tmax = 10.0;
//        double tau = 0.001;
//        double t = 0.0;
//        double startTime = 0.0, endTime = 10.0;
//        PredictorCorrectorMpi(rank, size, f, N, y, t, tmax, tau);
//    }
    {
        double y[N] = {2.0, 1.0};
        double tmax = 10.0;
        double tau = 0.001;
        double t = 0.0;
        predictor_corrector_mpi(y, t, tmax, tau, N, rank, size);
        if (rank == 0) {
//            printf("Затраченное время на OMP параллельное выполнение: %f\n", tend - tstart);
            for (int i = 0; i < N; i++) {
                printf("y[%d]: %f ", i, y[i]);
            }
        }
    }
//    {
//        double y[N] = {2.0, 1.0};
//        double yy[N] = {0.0, 0.0};
//        double tmax = 10.0;
//        double tau = 0.001;
//        double fk[N] = {0.0}; //текущий
//        double ff[N] = {0.0}; //прогнозируемый
//        double t = 0.0;
//        double tstart = omp_get_wtime();
//
//#pragma omp parallel num_threads(2)
//        {
//
//            do {
//
//#pragma omp for schedule(dynamic)
//                for (int i = 0; i < N; i++) {
//                    fk[i] = f[i](y, t);
//                }
//
//#pragma omp for schedule(dynamic)
//                for (int i = 0; i < N; i++) {
//                    yy[i] = y[i] + tau * fk[i];
//                }
//
//
//#pragma omp for schedule(dynamic)
//                for (int i = 0; i < N; i++) {
//                    ff[i] = f[i](yy, t + tau);
//                }
//
//
//#pragma omp for schedule(dynamic)
//                for (int i = 0; i < N; i++) {
//                    y[i] += tau * (fk[i] + ff[i]) / 2.0;
//                }
//#pragma omp master
//                t += tau;
//#pragma omp barrier
//            } while (t <= tmax);
//        }
//
//        double tend = omp_get_wtime();
//
//        printf("Затраченное время на OMP параллельное выполнение: %f\n", tend - tstart);
//
//        for (int i = 0; i < N; i++) {
//            printf("y[%d]: %f ", i, y[i]);
//        }
//    }
}