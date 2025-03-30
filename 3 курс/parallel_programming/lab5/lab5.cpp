//
// Created by Максим Прохоров on 01.11.2024.
//

#include "lab5.h"
#include <mpi.h>
#include <stdio.h>

int lab5(int rank, int size, const int root = 0)
{
    char name[20];
    sprintf(name, "result5.txt");
    FILE* f = fopen(name, "w");

    const int n = 8;
    const int m = 10;

    int arr[n][m];
    int bArr[n / 2][m / 2];
    int* count = new int[size];
    int* displacement = new int[size];

    if (rank == root)
    {
        for (int i = 0; i < n / 2; ++i)
        {
            for (int j = 0; j < m / 2; ++j)
            {
                arr[i][j] = 0;
            }
        }
        for (int i = n / 2; i < n; ++i)
        {
            for (int j = 0; j < m / 2; ++j)
            {
                arr[i][j] = 1;
            }
        }
        for (int i = 0; i < n / 2; ++i)
        {
            for (int j = m / 2; j < m; ++j)
            {
                arr[i][j] = 2;
            }
        }
        for (int i = n / 2; i < n; ++i)
        {
            for (int j = m / 2; j < m; ++j)
            {
                arr[i][j] = 3;
            }
        }
        if (f != nullptr)
        {
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < m; ++j)
                {
                    fprintf(f, "%d", arr[i][j]);
                }
                fprintf(f, "\n");
            }
            fprintf(f, "\n");
            fclose(f);
        }
    }

    for (int i = 0; i < size; ++i)
    {
        count[i] = m / 2;
    }

    displacement[0] = 0;
    displacement[1] = n / 2 * m;
    displacement[2] = m / 2;
    displacement[3] = n / 2 * m + m / 2;

    for (int i = 0; i < n / 2; ++i)
    {
        MPI_Scatterv(arr[i], count, displacement, MPI_INT, bArr[i], count[rank], MPI_INT, 0, MPI_COMM_WORLD);
    }

    for (int i = 0; i < size; ++i)
    {
        if (i == rank)
        {
            f = fopen(name, "a");
            if (f != nullptr)
            {
                fprintf(f, "RANK #%d\n", i);

                for (int i = 0; i < n / 2; ++i)
                {
                    for (int j = 0; j < m / 2; ++j)
                    {
                        fprintf(f, "%d", bArr[i][j]);
                    }
                    fprintf(f, "\n");
                }
                fprintf(f, "\n");
                fclose(f);
            }
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }

    MPI_Finalize();
    delete[] count;
    delete[] displacement;
    return 0;
}
