#pragma once
#ifndef MathLib_H
#define MathLib_H

#include <iostream>
#include <omp.h>
#include <cstdio>
#include <fstream>

// Макрос для экспорта функций из DLL
#ifdef MATHLIB_EXPORTS
#define MathLib_API __declspec(dllexport)
#else
#define MathLib_API __declspec(dllimport)
#endif

using namespace std;

extern "C" {
    MathLib_API void printFile(double array[], int n, FILE* file);
    MathLib_API int Eiler(double (*f[])(double*, double), double y[], double startTime, double endTime, double tau, int n, FILE* file);
    MathLib_API int RungeKutt2(double (*f[])(double*, double), double y[], double startTime, double endTime, double tau, int n, FILE* file);
    MathLib_API int PredictorCorrector(double (*f[])(double*, double), double y[], double startTime, double endTime, double tau, int n, FILE* file);
    MathLib_API int RungeKutta4(double (*f[])(double*, double), double y[], double startTime, double endTime, double tau, int n, FILE* file);
    MathLib_API void ImplictEiler(double (*f[])(double*, double), double y[], double startTime, double endTime, double tau, int n, FILE* file);
    MathLib_API void Yakobi(int N, ifstream& matrA, ifstream& matrB, ofstream& matrX, double eps);
    MathLib_API void YakobiComplex(int N, ifstream& matrA, ifstream& matrB, ofstream& matrX, double eps);
    MathLib_API void GausZeydel(int N, ifstream& matrA, ifstream& matrB, ofstream& matrX, double eps);
    MathLib_API void GausZeydelComplex(int N, ifstream& matrA, ifstream& matrB, ofstream& matrX, double eps);
    MathLib_API void Gaus(int N, ifstream& matrA, ifstream& matrB, ofstream& matrX);
    MathLib_API void GausComplex(int N, ifstream& matrA, ifstream& matrB, ofstream& matrX);
    MathLib_API void ScanFunc(double (*Func)(double, double), double xmin, double xmax, double ymin, double ymax, double x, double y, double h1, double h2);
    MathLib_API void Gradient(double (*Func)(double, double), double X, double Y, double eps, double h, double xmin, double xmax, double ymin, double ymax);
    MathLib_API void CoordinatedDescent(double (*Func)(double, double), double xmin, double xmax, double ymin, double ymax, double x, double y, double eps, double h);
}

#endif