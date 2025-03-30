//Вариант 2. Задача о голодных птенцах.
//Есть n птенцов и их мать. Птенцы едят из общей миски, в которой F порций пищи. Каждый птенец съедает порцию еды, спит некоторое время, затем снова ест.  Когда кончается еда, птенец, евший последним, зовет мать. Птица наполняет миску 0<M≤F порциями еды и снова ждет, пока миска опустеет. Эти действия повторяются без конца.
//Представить птиц процессами, разработать код, моделирующий их действия. Использовать алгоритм «портфель задач». Написать программы на MPI и OpenMP.


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <unistd.h>

const int maxIterationsNumber = 7;
const int dishCapacity = 8;


void task2() {
    srand(time(NULL));
    int portionCount = 0;
    int emptiesCount = 0;
    int birdsCount = 5;
    int dishState = 0;
    omp_lock_t lock;

    omp_init_lock(&lock);
    
    FILE* file = fopen("task2/output.txt", "w");
    if (file == nullptr)
    {
        fprintf(stderr, "File error\n");
    }

#pragma omp parallel shared(portionCount, emptiesCount, dishState) num_threads(birdsCount + 1)
    {
        int thread_id = omp_get_thread_num();

        if (thread_id == 0) {

            while (true) {
                if (emptiesCount >= maxIterationsNumber) {
                    break;
                }

                if (!dishState) {
                    omp_set_lock(&lock);
                    portionCount = rand() % dishCapacity + 1;
                    fprintf(file, "Мама в %d-й раз заполнила миску %d порциями еды\n", emptiesCount + 1, portionCount);
                    emptiesCount++;
                    dishState = 1;
                    omp_unset_lock(&lock);
                }
            }
        }
        else {
            while (true) {
                if (emptiesCount >= maxIterationsNumber) {
                    break;
                }

                if (dishState) {
                    omp_set_lock(&lock);
                    if (portionCount > 0) {
                        portionCount--;
                        fprintf(file, "%d-й птенец поел из миски. Порций осталось: %d\n", thread_id, portionCount);
                        if (portionCount <= 0) {
                            if (emptiesCount < maxIterationsNumber) {
                                fprintf(file, "%d-й птенец начинает звать маму!\n", thread_id);
                            }
                            dishState = 0;
                        }
                    omp_unset_lock(&lock);
                    sleep(0.5);
                    }
                }
            }
        }
    }

    fclose(file);
    omp_destroy_lock(&lock);
}