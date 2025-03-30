//
// Created by Максим Прохоров on 04.12.2024.
//

#include "lab7.h"

#include <omp.h>
#include <ctime>
#include <fstream>
#include <string>

void lab7()
{
    int nthreads, tid;

#pragma omp parallel private(nthreads, tid)
    {
        nthreads = omp_get_num_threads();
        tid = omp_get_thread_num();

        std::ofstream ofile("lab7/thread" + std::to_string(tid) + ".txt");
        ofile << "Поток #" << tid << " из " << nthreads << " потоков" << std::endl;
    }
}
