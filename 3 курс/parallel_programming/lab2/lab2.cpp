//
// Created by Максим Прохоров on 20.09.2024.
//

#include "lab2.h"

#include <mpi.h>
#include <stdio.h>

int lab2(int size, int rank) {
    if (rank == 0) {
        FILE* file = fopen("output.txt", "w");
        if (file == NULL) {
            printf("Ошибка при открытии файла\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        fprintf(file, "Общее количество процессов: %d\n", size);
        fclose(file);
    }

    for (int i = 0; i < size; i++) {

        if (i == rank) {
            FILE* file = fopen("output.txt", "a");
            if (file == NULL) {
                printf("Ошибка при открытии файла\n");
                MPI_Abort(MPI_COMM_WORLD, 1);
            }
            fprintf(file, "Процесс %d из %d\n", rank , size);
            fclose(file);
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}