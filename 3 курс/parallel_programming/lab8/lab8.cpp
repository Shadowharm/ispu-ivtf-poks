//
// Created by Максим Прохоров on 06.12.2024.
//

#include "lab8.h"

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

const int N = 100;

void writeMatrixToFile(const char* filename, int** matrix) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fprintf(file, "%d ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

int** generateMatrix (int n) {
    int** matrix = new int*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 100;
        }
    }

    return matrix;
}

void freeMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}


void lab8() {
    int** a = generateMatrix(N);
    int** b = generateMatrix(N);
    int** c = new int*[N];
    for (int i = 0; i < N; i++) {
        c[i] = new int[N];
    }

    writeMatrixToFile("lab8/matrix-a.txt", a);
    writeMatrixToFile("lab8/matrix-b.txt", b);


#pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }

    writeMatrixToFile("lab8/matrix-c.txt", c);

    freeMatrix(a, N);
    freeMatrix(b, N);
    freeMatrix(c, N);
}