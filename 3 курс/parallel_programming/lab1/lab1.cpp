//
// Created by Максим Прохоров on 20.09.2024.
//
#include <iostream>
#include <mpi.h>
#include <cstdio>
#include "lab1.h"
using namespace std;

int lab1 (int size, int rank) {
    FILE* f;
    char name[20];
    sprintf(name, "rank_%d.txt", rank);

    if ((f = fopen(name, "w")) == nullptr) {
        fprintf(stderr, "File error\n");
        MPI_Finalize();
        return 4;
    }

    fprintf(f, "size=%d rank=%d\n", size, rank);
    fclose(f);

    return 0;
}
