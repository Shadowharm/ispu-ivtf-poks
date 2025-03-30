//
// Created by Максим Прохоров on 06.11.2024.
//

//Вариант 2. Задача о голодных птенцах.
//Есть n птенцов и их мать. Птенцы едят из общей миски, в которой F порций пищи. Каждый птенец съедает порцию еды, спит некоторое время, затем снова ест.  Когда кончается еда, птенец, евший последним, зовет мать. Птица наполняет миску 0<M≤F порциями еды и снова ждет, пока миска опустеет. Эти действия повторяются без конца.
//Представить птиц процессами, разработать код, моделирующий их действия. Использовать алгоритм «портфель задач». Написать программы на MPI и OpenMP.

#include "task1.h"

#include <mpi.h>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <random>
#include <ctime>
#include <stdio.h>
#include <unistd.h>



using namespace std;


const int maxIterationsNumber = 7;
const int dishCapacity = 8;

void task1(int rank, int size, const int root = 0)
{
    srand(time(NULL));

    FILE* file;
    char fileName[30];
    int emptiesCount = 0;
    int portionCount = 6;
    int dishState = 0;
    MPI_Status status;
    const int msgtag = 0;

    if (rank == 0)
    {
        sprintf(fileName, "task1/Dish_rank_%d.txt", rank);
        file = fopen(fileName, "w");
        if (file == nullptr)
        {
            fprintf(stderr, "File error\n");
        }

        dishState = 1;
        portionCount = rand() % dishCapacity + 1;
        int bird = 2;
        int last;

        while (true)
        {
            while (portionCount > 0)
            {
                MPI_Send(&dishState, 1, MPI_INT, bird, msgtag, MPI_COMM_WORLD);
                --portionCount;
                fprintf(file, "%d-й птенец поел из миски, еды в миске сейчас: %d\n", -1 + bird, portionCount);

                ++bird;
                if (bird >= size)
                {
                    bird = 2;
                }
            }

            fprintf(file, "Миска опустела в %d-й раз\n", emptiesCount + 1);
            dishState = -1;

            if (bird == 2)
            {
                last = size - 1;
            }
            else
            {
                last = bird - 1;
            }

            MPI_Send(&dishState, 1, MPI_INT, last, msgtag, MPI_COMM_WORLD);
            ++emptiesCount;
            MPI_Recv(&portionCount, 1, MPI_INT, 1, msgtag, MPI_COMM_WORLD, &status);

            if (portionCount > 0)
            {
                fprintf(file, "Теперь в миске %d порций\n", portionCount);
                dishState = 1;
            }

            if (emptiesCount >= maxIterationsNumber)
            {
                dishState = 0;
                for (int i = 1; i < size; ++i)
                {
                    MPI_Send(&dishState, 1, MPI_INT, i, msgtag, MPI_COMM_WORLD);
                }

                break;
            }
        }
    }
    else if (rank == 1)
    {
        sprintf(fileName, "task1/Mother_rank_%d.txt", rank);
        file = fopen(fileName, "w");
        if (file == nullptr)
        {
            fprintf(stderr, "File error\n");
        }

        dishState = 0, portionCount = 0;

        while (true)
        {
            MPI_Recv(&dishState, 1, MPI_INT, MPI_ANY_SOURCE, msgtag, MPI_COMM_WORLD, &status);
            if (dishState == -1)
            {
                fprintf(file, "Птенец № %d позвал маму в %d раз\n", status.MPI_SOURCE - 1, emptiesCount + 1);
                portionCount = rand() % dishCapacity + 1;

                // Повар заполняет горшок
                fprintf(file, "Мама в %d-й раз заполнила миску %d порциями еды.\n", ++emptiesCount, portionCount);
                MPI_Send(&portionCount, 1, MPI_INT, 0, msgtag, MPI_COMM_WORLD);
            }
            else if (dishState == 0)
            {
                break;
            }
        }
    }
    else
    {
        sprintf(fileName, "task1/Bird-%d_rank_%d.txt", rank - 1, rank);
        file = fopen(fileName, "w");
        if (file == nullptr)
        {
            fprintf(stderr, "File error\n");
        }
        dishState = 0;;
        while (true)
        {
            MPI_Recv(&dishState, 1, MPI_INT, 0, msgtag, MPI_COMM_WORLD, &status);
            if (dishState == 1)
            {
                fprintf(file, "%d-й птенец поел из миски\n", -1 + rank);
                sleep(0.05);
            }
            else if (dishState == -1)
            {
                fprintf(file, "%d-й птенец начинает звать маму\n", -1 + rank);
                MPI_Send(&dishState, 1, MPI_INT, 1, msgtag, MPI_COMM_WORLD);
            }
            else
            {
                break;
            }
        }
    }
    fclose(file);
    MPI_Finalize();
}
