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

double F1(double * y, double x) {
    return sin(x + y[0] * y[1]);
}

double F2(double* y, double x) {
    return cos(x*x - y[0] + y[1]);
}

const double A = 14.2;
const double B = -0.1;
const double C = 1.05;
const double D = 0.24;
const int N = 2;


double objectiveFunc(double x1, double x2) {
    return A * x1 + B * x2 + exp(C * x1 * x1 + D * x2 * x2);
}


int main() {
	setlocale(LC_ALL, "Russian");

    const int n = 2;
    double y[n] = { 2.0, 1.0 }, y_temp[n], t0 = 0.0, tmax = 10.0, tau = 0.001;

    double (*f[n])(double*, double) = { F1, F2 };

    FILE* file = nullptr;


    fopen_s(&file, "Eiler.txt", "w");
    memcpy(&y_temp, &y, sizeof(y));
    Eiler(f, y_temp, t0, tmax, tau, n, file);
    fclose(file);

 
    fopen_s(&file, "RungeKutt2.txt", "w");
    memcpy(&y_temp, &y, sizeof(y));
    RungeKutt2(f, y_temp, t0, tmax, tau, n, file);
    fclose(file);


    fopen_s(&file, "PredictorCorrector.txt", "w");
    memcpy(&y_temp, &y, sizeof(y));
    PredictorCorrector(f, y_temp, t0, tmax, tau, n, file);
    fclose(file);

    fopen_s(&file, "RungeKutta4.txt", "w");
    memcpy(&y_temp, &y, sizeof(y));
    RungeKutta4(f, y_temp, t0, tmax, tau, n, file);
    fclose(file);

    fopen_s(&file, "ImplictEiler.txt", "w");
    memcpy(&y_temp, &y, sizeof(y));
    ImplictEiler(f, y_temp, t0, tmax, tau, n, file);
    fclose(file);
    rewind(stdin);

    int matrixSizes[] = { 250 };
    for (int size : matrixSizes) {
        char filenameA[256];
        char filenameB[256];
        char filenameX[256];

        sprintf_s(filenameA, "matrix/matrixA_%d.txt", size);
        sprintf_s(filenameB, "matrix/matrixB_%d.txt", size);
        sprintf_s(filenameX, "matrix/matrixGausZeydelX_%d.txt", size);
        ifstream matrA(filenameA);
        ifstream matrB(filenameB);
        ofstream matrX(filenameX);

        GausZeydel(size, matrA, matrB, matrX, 0.0001);
    }

    int matrixComplexSizes[] = { 250 };
    for (int size : matrixComplexSizes) {
        char filenameA[256];
        char filenameB[256];
        char filenameX[256];

        sprintf_s(filenameA, "matrix/matrixA-complex_%d.txt", size);
        sprintf_s(filenameB, "matrix/matrixB-complex_%d.txt", size);
        sprintf_s(filenameX, "matrix/matrixGausX-complex_%d.txt", size);
        ifstream matrA(filenameA);
        ifstream matrB(filenameB);
        ofstream matrX(filenameX);
        GausComplex(size, matrA, matrB, matrX);
    }

    ScanFunc(objectiveFunc, -5.0, 5.0, -5.0, 5.0, 0, 0, 0.1, 0.001);
    CoordinatedDescent(objectiveFunc, -5.0, 5.0, -5.0, 5.0, 0.0, 0.0, 0.000001, 0.0001);
    Gradient(objectiveFunc, 0.0, 0.0, 0.00001, 0.000001, -5.0, 5.0, -5.0, 5.0);
    return 0;
}

