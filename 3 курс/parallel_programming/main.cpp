#include <iostream>
#include <mpi.h>
#include "lab1/lab1.h"
#include "lab2/lab2.h"
#include "lab3/lab3.h"

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

    FirstMethod(rank, size);
    SecondMethod(rank, size);
    MPI_Finalize();
    return 0;
}