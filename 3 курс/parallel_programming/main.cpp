#include <iostream>
#include <mpi.h>
#include "lab1/lab1.h"
#include "lab2/lab2.h"
#include "lab3/lab3.h"
#include "lab4/lab4.h"
#include "lab5/lab5.h"
#include "task1/task1.h"
#include "task2/task2.h"
#include "lab7/lab7.h"
#include "lab8/lab8.h"
#include "lab9/lab9.h"
#include "lab10/lab10.h"

using namespace std;

int main(int argc, char** argv) {
    if (MPI_Init(&argc, &argv) != MPI_SUCCESS) return 1;

    int size, rank;

    if (MPI_Comm_size(MPI_COMM_WORLD, &size) != MPI_SUCCESS) {
        MPI_Finalize();
        return 2;
    }

    if (MPI_Comm_rank(MPI_COMM_WORLD, &rank) != MPI_SUCCESS) {
        MPI_Finalize();
        return 3;
    }

     MPI_Barrier(MPI_COMM_WORLD);


    lab9(rank, size, 0);

    // MPI_Finalize();
    return 0;
}