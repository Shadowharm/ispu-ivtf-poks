//
// Created by Максим Прохоров on 08.10.2024.
//

#include "lab3.h"

#include <stdio.h>
#include <mpi.h>

void useRecv(int rank, int size)
{
    MPI_Status status;
    int* a = new int[size];
    a[rank] = rank;
    if (!rank) // если нулевой процесс
    {
        for (int i = 1; i < size; i++)
        {
            MPI_Recv(&a[i], 1, MPI_INT, i, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        }

        for (int i = 1; i < size; i++)
        {
            MPI_Send(a, size, MPI_INT, i, 1, MPI_COMM_WORLD);
        }
    }
    else
    {
        MPI_Send(&a[rank], 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
        MPI_Recv(a, size, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    }

    char name[20];
    sprintf(name, "rank_recv_%d.txt", rank);
    FILE* f = fopen(name, "w");
    if (f != nullptr) {
        for (int i = 0; i < size; i++)
        {
            fprintf(f, "rank: %d \n", a[i]);
        }
        fclose(f);
    }
    delete[] a;
}

void useBcast(int rank, int size)
{
    int* a = new int[size];
    a[rank] = rank;

    for (int i = 0; i < size; i++)
    {
        MPI_Bcast(&a[i], 1, MPI_INT, i, MPI_COMM_WORLD);
    }

    char name[20];
    sprintf(name, "rank_bcast_%d.txt", rank);
    FILE* f = fopen(name, "w");
    if (f != nullptr) {
        for (int i = 0; i < size; i++)
        {
            fprintf(f, "rank: %d \n", a[i]);
        }
        fclose(f);
    }
    delete[] a;
}