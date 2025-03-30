//
// Created by Максим Прохоров on 09.12.2024.
//

#include "lab9.h"
#include <iostream>
#include <cmath>
#include <omp.h>
#include <fstream>
#include <math.h>

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


void lab9() {
    {
        double y[N] = {2.0, 1.0};
        double tmax = 10.0;
        double tau = 0.001;
        double t = 0.0;
        PredictorCorrector(f, y, t, tmax, tau, N);
    }
    double y[N] = {2.0, 1.0};
    double yy[N] = {0.0, 0.0};
    double tmax = 10.0;
    double tau = 0.001;
    double fk[N] = {0.0}; //текущий
    double ff[N] = {0.0}; //прогнозируемый
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

    printf("Затраченное время на параллельное выполнение: %f\n", tend - tstart);

    for (int i = 0; i < N; i++) {
        printf("y[%d]: %f ", i, y[i]);
    }

}