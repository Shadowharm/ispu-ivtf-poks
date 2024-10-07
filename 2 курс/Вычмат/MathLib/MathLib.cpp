#include "pch.h"
#include <stdio.h>      
#include <stdlib.h>     
#include <omp.h>
#include <iostream>
#include <omp.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <cstring>
#include <cmath>
#include <complex>
#include "MathLib.h"

using namespace std;


void printFile(double array[], int n, FILE* file) {
    for (int i = 0; i < n; i++) {
        fprintf(file, "%lf ", array[i]);
    }
    fprintf(file, "\n");
}


int Eiler(double (*f[])(double*, double), double y[], double startTime, double endTime, double tau, int n, FILE* file) {
    double* yy = new double[n] {0.0};
    double start = omp_get_wtime();
    for (double t = startTime; t <= endTime; t += tau) {
        printFile(y, n, file);
        for (int i = 0; i < n; i++) {
            yy[i] = y[i] + tau * f[i](y, t);
        }
        for (int i = 0; i < n; i++) {
            y[i] = yy[i];
        }
    }

    printf_s("Затраченное время на функцию Эйлера: %f\n", omp_get_wtime() - start);
    delete[] yy;
    return 0;
}


int RungeKutt2(double (*f[])(double*, double), double y[], double startTime, double endTime, double tau, int n, FILE* file) {
    double* yy = new double[n] {0.0};
    double* fk = new double[n] {0.0};
    double* ff = new double[n] {0.0};
    double start = omp_get_wtime();

    for (double t = startTime; t <= endTime; t += tau) {
        printFile(y, n, file);
        for (int i = 0; i < n; i++) {
            fk[i] = f[i](y, t);
        }

        for (int i = 0; i < n; i++) {
            yy[i] = y[i] + 0.5 * tau * fk[i];
        }

        for (int i = 0; i < n; i++) {
            ff[i] = f[i](yy, t);
        }

        for (int i = 0; i < n; i++) {
            y[i] = y[i] + tau * ff[i];
        }

    }
    printf_s("Затраченное время на функцию Рунге-Кутта-2: %f\n", omp_get_wtime() - start);
    delete[] yy;
    delete[] fk;
    delete[] ff;
    return 1;
}

int PredictorCorrector(double (*f[])(double*, double), double y[], double startTime, double endTime, double tau, int n, FILE* file) {
    double* yy = new double[n] {0.0};
    double* fk = new double[n] {0.0};
    double* ff = new double[n] {0.0};
    double start = omp_get_wtime();

    for (double t = startTime; t <= endTime; t += tau) {
        printFile(y, n, file);
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
    printf_s("Затраченное время на функцию Предиктор-корректор: %f\n", omp_get_wtime() - start);
    delete[] yy;
    delete[] fk;
    delete[] ff;
    return 1;
}


int RungeKutta4(double (*f[])(double*, double), double y[], double startTime, double endTime, double tau, int n, FILE* file) {
    const int m = 4;
    double* yy = new double [n] { 0.0 };
    double* ff = new double [n] { 0.0 };
    double** R = new double* [m] {};
    for (int i = 0; i < m; i++)
    {
        R[i] = new double[n] {0.0};
    }

    double start = omp_get_wtime();
    for (double t = startTime; t < endTime; t += tau)
    {
        printFile(y, n, file);
        for (int i = 0; i < n; i++)
        {
            R[0][i] = tau * f[i](y, t);
        }

        for (int i = 0; i < n; i++)
        {
            yy[i] = y[i] + 0.5 * R[0][i];
        }

        for (int i = 0; i < n; i++)
        {
            R[1][i] = tau * f[i](yy, t + 0.5 * tau);

        }

        for (int i = 0; i < n; i++)
        {
            yy[i] = y[i] + 0.5 * R[1][i];
        }

        for (int i = 0; i < n; i++)
        {
            R[2][i] = tau * f[i](yy, t + 0.5 * tau);
        }

        for (int i = 0; i < n; i++)
        {
            yy[i] = y[i] + R[2][i];
        }

        for (int i = 0; i < n; i++)
        {
            R[3][i] = tau * f[i](yy, t + tau);
        }

        for (int i = 0; i < n; i++)
        {
            y[i] += (R[0][i] + 2.0 * R[1][i] + 2.0 * R[2][i] + R[3][i]) / 6.0;
        }
    }
    printf_s("Затраченное время на функцию Рунге-Кутта-4: %f\n", omp_get_wtime() - start);
    for (int i = 0; i < m; i++)
    {
        delete[] R[i];
    }
    delete[] R;
    delete[] yy;
    delete[] ff;
    return 1;

}


void ImplictEiler(double (*f[])(double*, double), double y[], double startTime, double endTime, double tau, int n, FILE* file)
{
    double* yy = new double[n] {0.0};
    double* b = new double[n] {0.0};
    double* p = new double[n] {0.0};
    double* opredelitelN = new double[n] { 0.0 };
    double** a = new double* [n];
    for (int i = 0; i < n; i++)
    {
        a[i] = new double[n] {0.0};
    }

    double deltaH = 0.0001, opredelitel;


    double start = omp_get_wtime();
    for (double t = startTime; t < endTime; t += tau)
    {
        printFile(y, n, file);
        for (int i = 0; i < n; i++)
        {
            b[i] = -f[i](y, t);
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                memcpy(yy, y, sizeof(y) * n);
                yy[j] += deltaH;
                a[i][j] = (f[i](yy, t) + b[i]) / deltaH;
            }
        }

        a[0][0] -= (double)(1.0 / tau);
        a[1][1] -= (double)(1.0 / tau);

        opredelitel = a[0][0] * a[1][1] - a[0][1] * a[1][0];
        if (!opredelitel)
        {
            exit(1);
        }

        opredelitelN[0] = b[0] * a[1][1] - b[1] * a[0][1];
        opredelitelN[1] = b[1] * a[0][0] - b[0] * a[1][0];

        for (int i = 0; i < n; i++)
        {
            p[i] = opredelitelN[i] / opredelitel;
        }

        for (int i = 0; i < n; i++)
        {
            y[i] += p[i];
        }
    }
    printf_s("Затраченное время на функцию Неявный метод Эйлера: %f\n", omp_get_wtime() - start);
    for (int i = 0; i < n; i++)
    {
        delete[] a[i];
    }
    delete[] a;
    delete[] yy;
    delete[] opredelitelN;
    delete[] b;
    delete[] p;
}

void CreateMatrix(int matrixSizes[], int n)
{
    srand(time(0));

    std::system("mkdir matrix");

    char filenameA[256];
    char filenameB[256];

    for (int k = 0; k < n; k++)
    {
        int N = matrixSizes[k];
        sprintf_s(filenameA, "matrix/matrixA_%d.txt", N);
        sprintf_s(filenameB, "matrix/matrixB_%d.txt", N);
        ofstream matrixA(filenameA);
        ofstream matrixB(filenameB);

        if (!matrixA.is_open() || !matrixB.is_open()) return;

        double* matrA = new double[N];
        double* matrB = new double[N];
        for (int i = 0; i < N; i++)
        {
            double sum = 0.0;
            for (int j = 0; j < N; j++)
            {
                matrA[j] = rand() % 100;
                sum += matrA[j];
            }
            matrA[i] = sum + 1;
            for (int j = 0; j < N; j++)
            {
                matrixA << matrA[j] << "\t";
            }
            matrixA << endl;
            matrB[i] = rand() % 100;
            matrixB << matrB[i] << "\t";
        }
        matrixB.close();
        matrixA.close();
        delete[] matrB;
        delete[] matrA;
    }
}

void CreateComplexMatrix(int matrixSizes[], int n)
{
    srand(time(0));

    char filenameA[256];
    char filenameB[256];


    for (int k = 0; k < n; k++)
    {
        int N = matrixSizes[k];
        sprintf_s(filenameA, "matrix/matrixA-complex_%d.txt", N);
        sprintf_s(filenameB, "matrix/matrixB-complex_%d.txt", N);
        ofstream matrixA(filenameA);
        ofstream matrixB(filenameB);

        if (!matrixA.is_open() || !matrixB.is_open()) return;

        complex<double>* matrA = new complex<double>[N];
        complex<double>* matrB = new complex<double>[N];
        for (int i = 0; i < N; i++)
        {
            complex<double> sum = 0.0;
            for (int j = 0; j < N; j++)
            {
                matrA[j].real(rand() % 100);
                matrA[j].imag(rand() % 100);
                sum += matrA[j];
            }
            matrA[i] = sum + 1.0;
            for (int j = 0; j < N; j++)
            {
                matrixA << matrA[j] << "\t";
            }
            matrixA << endl;
            matrB[i].real(rand() % 100);
            matrB[i].imag(rand() % 100);
            matrixB << matrB[i] << "\t";
        }
        matrixB.close();
        matrixA.close();
        delete[] matrB;
        delete[] matrA;
    }
}

void Yakobi(int N, ifstream& matrA, ifstream& matrB, ofstream& matrX, double eps)
{
    double sum1 = 0.0;
    double sum2 = 0.0;
    double xmax = -1.0;
    double tmp = 0.0;
    double tn;


    double** matrixA = new double* [N];
    double* matrixB = new double[N];
    double* matrixX = new double[N];
    double* matrixXX = new double[N];

    if (!matrA.is_open() || !matrB.is_open() || !matrX.is_open()) return;

    for (int i = 0; i < N; i++)
    {
        matrixA[i] = new double[N];
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrA >> matrixA[i][j];
        }
        matrB >> matrixB[i];
        matrixX[i] = matrixXX[i] = 1.0;
    }

    tn = omp_get_wtime();
    do {
        xmax = -1.0;
        for (int i = 0; i < N; i++)
        {
            sum1 = 0.0;
            sum2 = 0.0;
            for (int j = 0; j < N; j++)
            {
                if (j < i)
                    sum1 += matrixA[i][j] * matrixX[j];
                if (j > i)
                    sum2 += matrixA[i][j] * matrixX[j];
            }
            matrixXX[i] = (1.0 / matrixA[i][i]) * (matrixB[i] - sum1 - sum2);
            tmp = abs(matrixX[i] - matrixXX[i]);
            if (tmp > xmax) xmax = tmp;
        }
        for (int i = 0; i < N; i++)
            matrixX[i] = matrixXX[i];
    } while (xmax > eps);

    printf("Затраченное время на метод Якоби для %d-размерной матрицы: %f c\n", N, omp_get_wtime() - tn);

    for (int i = 0; i < N; i++)
    {
        matrX << "x[" << i << "] = " << matrixX[i] << endl;
    }

    matrA.close();
    matrB.close();
    matrX.close();

    for (int i = 0; i < N; i++)
    {
        delete[] matrixA[i];
    }
    delete[] matrixA;
    delete[] matrixB;
    delete[] matrixX;

}

void YakobiComplex(int N, ifstream& matrA, ifstream& matrB, ofstream& matrX, double eps)
{
    complex<double> sum1 = 0.0;
    complex<double> sum2 = 0.0;
    double xmax = -1.0;
    double tmp = 0.0;
    double tn;


    complex<double>** matrixA = new complex<double>*[N];
    complex<double>* matrixB = new complex<double>[N];
    complex<double>* matrixX = new complex<double>[N];
    complex<double>* matrixXX = new complex<double>[N];

    if (!matrA.is_open() || !matrB.is_open() || !matrX.is_open()) return;

    for (int i = 0; i < N; i++)
    {
        matrixA[i] = new complex<double>[N];
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrA >> matrixA[i][j];
        }
        matrB >> matrixB[i];
        matrixX[i] = matrixXX[i] = 1.0;
    }
    tn = omp_get_wtime();

    do {
        xmax = -1.0;
        for (int i = 0; i < N; i++)
        {
            sum1 = 0.0;
            sum2 = 0.0;
            for (int j = 0; j < N; j++)
            {
                if (j < i)
                    sum1 += matrixA[i][j] * matrixX[j];
                if (j > i)
                    sum2 += matrixA[i][j] * matrixX[j];
            }
            matrixXX[i] = (1.0 / matrixA[i][i]) * (matrixB[i] - sum1 - sum2);
            tmp = abs(matrixX[i] - matrixXX[i]);
            if (tmp > xmax) xmax = tmp;
        }
        for (int i = 0; i < N; i++)
            matrixX[i] = matrixXX[i];
    } while (xmax > eps);

    printf("Затраченное время на метод Якоби для %d-размерной комплексной матрицы: %f c\n", N, omp_get_wtime() - tn);


    for (int i = 0; i < N; i++)
    {
        matrX << "x[" << i << "] = " << matrixX[i] << endl;
    }

    matrA.close();
    matrB.close();
    matrX.close();

    for (int i = 0; i < N; i++)
    {
        delete[] matrixA[i];

    }
    delete[] matrixA;
    delete[] matrixB;
    delete[] matrixX;
    delete[] matrixXX;
}

void GausZeydel(int N, ifstream& matrA, ifstream& matrB, ofstream& matrX, double eps)
{
    double sum1 = 0.0;
    double sum2 = 0.0;
    double xmax = -1.0;
    double tmp = 0.0;
    double tn;
    double xv;


    double** matrixA = new double* [N] { 0 };
    double* matrixB = new double[N];
    double* matrixX = new double[N];


    if (!matrA.is_open() || !matrB.is_open() || !matrX.is_open()) return;

    for (int i = 0; i < N; i++)
    {
        matrixA[i] = new double[N] { 0 };
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrA >> matrixA[i][j];
        }
        matrB >> matrixB[i];
        matrixX[i] = 1.0;
    }

    tn = omp_get_wtime();
    do {
        xmax = -1.0;
        for (int i = 0; i < N; i++)
        {
            xv = matrixX[i];
            sum1 = 0.0;
            sum2 = 0.0;
            for (int j = 0; j < N; j++)
            {
                if (j < i)
                    sum1 += matrixA[i][j] * matrixX[j];
                if (j > i)
                    sum2 += matrixA[i][j] * matrixX[j];
            }
            matrixX[i] = (1.0 / matrixA[i][i]) * (matrixB[i] - sum1 - sum2);
            tmp = abs(matrixX[i] - xv);
            if (tmp > xmax) xmax = tmp;
        }
    } while (xmax > eps);

    printf("Затраченное время на метод Гаусса-Зейделя для %d-размерной матрицы: %f c\n", N, omp_get_wtime() - tn);


    for (int i = 0; i < N; i++)
    {
        matrX << "x[" << i << "] = " << matrixX[i] << endl;
    }

    matrA.close();
    matrB.close();
    matrX.close();

    for (int i = 0; i < N; i++)
    {
        delete[] matrixA[i];

    }
    delete[] matrixA;
    delete[] matrixB;
    delete[] matrixX;
}

void GausZeydelComplex(int N, ifstream& matrA, ifstream& matrB, ofstream& matrX, double eps)
{
    complex<double> sum1 = 0.0;
    complex<double> sum2 = 0.0;
    double xmax = -1.0;
    double tmp = 0.0;
    double tn;
    complex<double> xv;


    complex<double>** matrixA = new complex<double>*[N] { 0 };
    complex<double>* matrixB = new complex<double>[N];
    complex<double>* matrixX = new complex<double>[N];

    if (!matrA.is_open() || !matrB.is_open() || !matrX.is_open()) return;

    for (int i = 0; i < N; i++)
    {
        matrixA[i] = new complex<double>[N] { 0 };
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrA >> matrixA[i][j];
        }
        matrB >> matrixB[i];
        matrixX[i] = 1.0;
    }

    tn = omp_get_wtime();
    do {
        xmax = -1.0;
        for (int i = 0; i < N; i++)
        {
            xv = matrixX[i];
            sum1 = 0.0;
            sum2 = 0.0;
            for (int j = 0; j < N; j++)
            {
                if (j < i)
                    sum1 += matrixA[i][j] * matrixX[j];
                if (j > i)
                    sum2 += matrixA[i][j] * matrixX[j];
            }
            matrixX[i] = (1.0 / matrixA[i][i]) * (matrixB[i] - sum1 - sum2);
            tmp = abs(matrixX[i] - xv);
            if (tmp > xmax) xmax = tmp;
        }
    } while (xmax > eps);

    printf("Затраченное время на метод Гаусса-Зейделя для %d-размерной комплексной матрицы: %f c\n", N, omp_get_wtime() - tn);

    for (int i = 0; i < N; i++)
    {
        matrX << "x[" << i << "] = " << matrixX[i] << endl;
    }

    matrA.close();
    matrB.close();
    matrX.close();

    for (int i = 0; i < N; i++)
    {
        delete[] matrixA[i];

    }
    delete[] matrixA;
    delete[] matrixB;
    delete[] matrixX;
}


void Gaus(int N, ifstream& matrA, ifstream& matrB, ofstream& matrX)
{
    double tn;
    double w = 0.0, sum = 0.0;


    double** matrixA = new double* [N] { 0 };
    double* matrixB = new double[N];
    double* matrixX = new double[N] { 0 };

    if (!matrA.is_open() || !matrB.is_open() || !matrX.is_open()) return;

    for (int i = 0; i < N; i++)
    {
        matrixA[i] = new double[N] { 0 };
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrA >> matrixA[i][j];
        }
        matrB >> matrixB[i];
    }

    tn = omp_get_wtime();
    for (int i = 0; i <= N - 1; i++)
    {
        for (int j = i + 1; j <= N - 1; j++)
        {
            w = matrixA[j][i] / matrixA[i][i];
            for (int k = i; k <= N - 1; k++)
            {
                matrixA[j][k] = matrixA[j][k] - w * matrixA[i][k];
            }
            matrixB[j] = matrixB[j] - w * matrixB[i];
        }
    }

    for (int i = N - 1; i >= 0; i--)
    {
        sum = 0.0;
        for (int j = i + 1; j < N; j++)
        {
            sum = sum + matrixA[i][j] * matrixX[j];
        }
        matrixX[i] = (matrixB[i] - sum) / matrixA[i][i];
    }

    printf("Затраченное время на метод Гаусса для %d-размерной матрицы: %f c\n", N, omp_get_wtime() - tn);


    for (int i = 0; i < N; i++)
    {
        matrX << "x[" << i << "] = " << matrixX[i] << endl;
    }

    matrA.close();
    matrB.close();
    matrX.close();

    for (int i = 0; i < N; i++)
    {
        delete[] matrixA[i];

    }
    delete[] matrixA;
    delete[] matrixB;
    delete[] matrixX;
}

void GausComplex(int N, ifstream& matrA, ifstream& matrB, ofstream& matrX)
{
    double tn;
    complex<double> w = 0.0, sum = 0.0;


    complex<double>** matrixA = new complex<double>*[N] { 0 };
    complex<double>* matrixB = new complex<double>[N];
    complex<double>* matrixX = new complex<double>[N] { 0 };

    if (!matrA.is_open() || !matrB.is_open() || !matrX.is_open()) return;

    for (int i = 0; i < N; i++)
    {
        matrixA[i] = new complex<double>[N] { 0 };
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrA >> matrixA[i][j];
        }
        matrB >> matrixB[i];
    }
    tn = omp_get_wtime();

    for (int i = 0; i <= N - 1; i++)
    {
        for (int j = i + 1; j <= N - 1; j++)
        {
            w = matrixA[j][i] / matrixA[i][i];
            for (int k = i; k <= N - 1; k++)
            {
                matrixA[j][k] = matrixA[j][k] - w * matrixA[i][k];
            }
            matrixB[j] = matrixB[j] - w * matrixB[i];
        }
    }

    for (int i = N - 1; i >= 0; i--)
    {
        sum = 0.0;
        for (int j = i + 1; j < N; j++)
        {
            sum = sum + matrixA[i][j + 1] * matrixX[j + 1];
        }
        matrixX[i] = (matrixB[i] - sum) / matrixA[i][i];
    }

    printf("Затраченное время на метод Гаусса для %d-размерной комплексной матрицы: %f c\n", N, omp_get_wtime() - tn);

    for (int i = 0; i < N; i++)
    {
        matrX << "x[" << i << "] = " << matrixX[i] << endl;
    }

    matrA.close();
    matrB.close();
    matrX.close();

    for (int i = 0; i < N; i++)
    {
        delete[] matrixA[i];

    }
    delete[] matrixA;
    delete[] matrixB;
    delete[] matrixX;
}

void ScanFunc(double (*Func)(double, double), double xmin, double xmax, double ymin, double ymax, double x, double y, double h1, double h2)
{
    double rez, w, scan_min, x_scan = xmin, y_scan = ymin;
    int count_sections = (int)((xmax - xmin) / h1) + 1;

    scan_min = 99999999.0;
    x = xmin; y = ymin;
    double tn = omp_get_wtime();
    for (int i = 0; i < count_sections; i++)
    {
        y = ymin;
        for (int j = 0; j < count_sections; j++)
        {
            w = Func(x, y);
            if (w < scan_min) {
                scan_min = w;
                x_scan = x;
                y_scan = y;
                rez = w;
            }
            y += h1;
        }
        x += h1;
    }
    printf("h1 = %1.3f rez = %f xsc = %1.3f ysc = % 1.3f\n", h1, rez, x_scan, y_scan);

    double xminh2 = x_scan - h1, xmaxh2 = x_scan + h1;
    if (xminh2 < xmin) xminh2 = xmin;
    if (xmaxh2 > xmax) xmaxh2 = xmax;
    double yminh2 = y_scan - h1, ymaxh2 = y_scan + h1;
    if (yminh2 < ymin) yminh2 = ymin;
    if (ymaxh2 > ymax) ymaxh2 = ymax;
    count_sections = (int)((xmaxh2 - xminh2) / h2) + 1;
    int count_lines = (int)((ymaxh2 - xminh2) / h2) + 1;
    scan_min = 99999999.0;
    x = xminh2; y = yminh2;
    for (int i = 0; i < count_sections; i++) {
        y = yminh2;
        for (int j = 0; j < count_lines; j++) {
            w = Func(x, y);
            if (w < scan_min) {
                scan_min = w;
                x_scan = x;
                y_scan = y;
                rez = w;
            }
            y += h2;
        }
        x += h2;
    }
    printf("h2 = % 1.3f rez = %f xsc = % 1.3f ysc = % 1.3f\n", h2, rez, x_scan, y_scan);

    printf("Затраченное время на сканирование: %f c.\n\n", omp_get_wtime() - tn);

}

void CoordinatedDescent(double (*Func)(double, double), double xmin, double xmax,
    double ymin, double ymax,
    double x, double y, double eps, double h)
{
    int countIteration = 0;
    double temp, resx, resy;
    double tempxmin = xmin, tempxmax = xmax, tempymin = ymin, tempymax = ymax;

    double tn = omp_get_wtime();

    do
    {
        temp = Func(x, y);
        double tempx1 = xmax - (xmax - xmin) / 1.618, tempx2 = xmin + (xmax - xmin) / 1.618;
        double FuncX1 = Func(tempx1, y), FuncX2 = Func(tempx2, y);
        while (fabs(tempx1 - tempx2) >= eps)
        {
            if (FuncX1 >= FuncX2) xmin = tempx1;
            else xmax = tempx2;
            tempx1 = xmax - (xmax - xmin) / 1.618;
            tempx2 = xmin + (xmax - xmin) / 1.618;
            FuncX1 = Func(tempx1, y);
            FuncX2 = Func(tempx2, y);
        }

        resx = (xmax + xmin) / 2.0;

        double tempy1 = ymax - (ymax - ymin) / 1.618, tempy2 = ymin + (ymax - ymin) / 1.618;
        double FuncY1 = Func(x, tempy1), FuncY2 = Func(x, tempy2);

        while (fabs(tempy1 - tempy2) >= eps)
        {
            if (FuncY1 >= FuncY2) ymin = tempy1; else ymax = tempy2;
            tempy1 = ymax - (ymax - ymin) / 1.618;
            tempy2 = ymin + (ymax - ymin) / 1.618;
            FuncY1 = Func(x, tempy1);
            FuncY2 = Func(x, tempy2);
        }

        resy = (ymax + ymin) / 2.0;
        countIteration++;

        x = resx;
        y = resy;

        xmin = tempxmin;
        xmax = tempxmax;
        ymin = tempymin;
        ymax = tempymax;

    } while (fabs(Func(x, y) - temp) >= h);


    printf("Затраченное время на координатный спуск: %f c.\n", omp_get_wtime() - tn);
    printf("Количество итераций координатного спуска: %d\n", countIteration);
    printf("X = %lf\tY = %lf\tMin -> Func(X, Y) = %lf\n\n", resx, resy, Func(resx, resy));
}

void Gradient(double (*Func)(double, double), double X, double Y, double eps, double h, double xmin, double xmax, double ymin, double ymax) {
    double x1 = X, x2 = Y, x1prev, x2prev, p1, p2;
    double sum = 100;
    double tn = omp_get_wtime();
    long countIteration = 0;
    while (sum > eps && x1 >= xmin && x1 <= xmax && x2 >= ymin && x2 <= ymax)
    {
        countIteration++;
        p1 = (Func(x1 + eps, x2) - Func(x1, x2)) / eps;
        p2 = (Func(x1, x2 + eps) - Func(x1, x2)) / eps;
        x1prev = x1;
        x1 -= h * p1;
        x2prev = x2;
        x2 -= h * p2;
        sum = sqrt(p1 * p1 + p2 * p2);
    }
    printf("x1 = % 1.9f x2 = %1.9f F = % 1.9f\n", x1prev, x2prev, Func(x1prev, x2prev));
    printf("Затраченное время на градиентный спуск: %f c.\n", omp_get_wtime() - tn);
    printf("Количество итераций градиентного спуска: %d\n\n", countIteration);

}
