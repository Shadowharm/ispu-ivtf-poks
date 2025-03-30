//
// Created by Максим Прохоров on 08.10.2024.
//

#include "lab3.h"

#include <stdio.h>
#include <mpi.h>

void FirstMethod(int rank, int size)
{
    int msgtag = 10;
    MPI_Status status;
    int* a = new int[size];
    a[rank] = rank;
    if (!rank)
    {
        for (int i = 1; i < size; i++)
        {
            MPI_Recv(&a[i], 1, MPI_INT, i, msgtag, MPI_COMM_WORLD, &status);
        }

        for (int i = 1; i < size; i++)
        {
            MPI_Send(a, size, MPI_INT, i, msgtag, MPI_COMM_WORLD);
        }
    }
    else
    {
        MPI_Send(&a[rank], 1, MPI_INT, 0, msgtag, MPI_COMM_WORLD);
        MPI_Recv(a, size, MPI_INT, 0, msgtag, MPI_COMM_WORLD, &status);
    }

    char name[20];
    sprintf(name, "rank1_%d.txt", rank);
    FILE* f;
    if (fopen(name, "w") == nullptr) {  // fopen_s returns 0 on success
        for (int i = 0; i < size; i++)
        {
            fprintf(f, "rank: %d \n", a[i]);
        }
        fclose(f);
    }
    delete[] a;
}

void SecondMethod(int rank, int size)
{
    int* a = new int[size];
    int msgtag = 10;
    a[rank] = rank;

    for (int i = 0; i < size; i++)
    {
        MPI_Bcast(&a[i], 1, MPI_INT, i, MPI_COMM_WORLD);
    }

    char name[20];
    sprintf(name, "rank2_%d.txt", rank);
    FILE* f;
    if (fopen(name, "w") == 0) {  // fopen_s returns 0 on success
        for (int i = 0; i < size; i++)
        {
            fprintf(f, "rank: %d \n", a[i]);
        }
        fclose(f);
    }
    delete[] a;
}