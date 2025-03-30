//
// Created by Максим Прохоров on 18.10.2024.
//

#include "lab4.h"

#include <mpi.h>
#include <stdio.h>
#include <random>
#include <time.h>

void lab4(int rank, int size, const int root)
{
    srand(time(NULL) + rank);
    int number = rand() % 10 + 1;

    int* arr = new int[number];
    for (int i = 0; i < number; i++)
    {
        arr[i] = rank * 10 + i;
    }

    int* countArray = new int[size];
    MPI_Allgather(&number, 1, MPI_INT, countArray, 1, MPI_INT, MPI_COMM_WORLD);
    int* displacement = new int[size] { 0 };

    for (int i = 1; i < size; ++i)
    {
        displacement[i] = displacement[i - 1] + countArray[i - 1];
    }

    int resultArraySize = 0;
    for (int i = 0; i < size; ++i)
    {
        resultArraySize += countArray[i];
    }

    int* resultArray = new int[resultArraySize];
    for (int i = 0; i < resultArraySize; ++i)
    {
        resultArray[i] = 0;
    }

    MPI_Gatherv(arr, number, MPI_INT, resultArray, countArray, displacement, MPI_INT, root, MPI_COMM_WORLD);

    if (rank == root)
    {
        char name[20];
        sprintf(name, "result.txt");
        FILE* f = fopen(name, "w");
        if (f != NULL)
        {
            for (int i = 0; i < resultArraySize; ++i)
            {
                fprintf(f, "b[%d]: %d \n", i, resultArray[i]);
            }
            fclose(f);
        }
    }

    MPI_Finalize();
    delete[] arr;
    delete[] countArray;
    delete[] displacement;
    delete[] resultArray;
}
