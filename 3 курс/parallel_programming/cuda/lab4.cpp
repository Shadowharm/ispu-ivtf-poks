#include <mpi.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <vector>
#include <map>
#include <omp.h>


namespace fs = std::filesystem;

void create_file(const std::string& filename) {
    std::ofstream file(filename);
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    for (int i = 0; i < 100; ++i) {
        int value = std::rand() % 50 + 1;
        file << value << "\n";
    }
    file.close();
}

// 1 ready, 2 data, 4 finish, 3 count
void cuda_lab4(int rank, int size) {
    const std::string filename = "cuda/rand_numbers.txt";

    if (rank == 0) {
        create_file(filename);


        std::ifstream in(filename);
        int working = size - 1;
        int request;

        double tstart = omp_get_wtime();

        while (working > 0) {
            MPI_Status status;
            MPI_Recv(&request, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);
            int worker = status.MPI_SOURCE;

            std::vector<int> nums;
            int temp;
            for (int i = 0; i < 500 && (in >> temp); ++i)
                nums.push_back(temp);

            if (!nums.empty()) {
                MPI_Send(nums.data(), nums.size(), MPI_INT, worker, 2, MPI_COMM_WORLD);
            } else {
                MPI_Send(nullptr, 0, MPI_INT, worker, 4, MPI_COMM_WORLD);
                --working;
            }
        }

        std::map<int, int> all_counts;
        for (int i = 1; i < size; ++i) {
            int count_size;
            MPI_Recv(&count_size, 1, MPI_INT, i, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            std::vector<int> raw(count_size * 2);
            MPI_Recv(raw.data(), count_size * 2, MPI_INT, i, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            for (int j = 0; j < count_size; ++j) {
                int number = raw[j * 2];
                int count = raw[j * 2 + 1];
                all_counts[number] += count;
            }
        }


        double tend = omp_get_wtime();

        printf("\nЗатраченное время на MPI параллельное выполнение: %f\n", tend - tstart);

        printf("Уникальные числа: ");
        for (auto it = all_counts.begin(); it != all_counts.end(); ++it) {
            if (it->second == 1) {
                printf("%d, ", it->first);
            }
        }

        printf("\nЧисло повторений каждого числа:\n");
        for (auto it = all_counts.begin(); it != all_counts.end(); ++it) {
            printf("%d: %d\n", it->first, it->second);
        }

    } else {
        int dummy = 0;
        std::map<int, int> local_count;

        while (true) {
            MPI_Send(&dummy, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);

            MPI_Status status;
            MPI_Probe(0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

            if (status.MPI_TAG == 4) {
                MPI_Recv(nullptr, 0, MPI_INT, 0, 4, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                break;
            }

            int count;
            MPI_Get_count(&status, MPI_INT, &count);
            std::vector<int> data(count);
            MPI_Recv(data.data(), count, MPI_INT, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            for (int value : data) {
                local_count[value]++;
            }
        }

        int n = local_count.size();
        std::vector<int> packed(n * 2);
        int i = 0;
        for (const auto& [key, val] : local_count) {
            packed[i * 2] = key;
            packed[i * 2 + 1] = val;
            ++i;
        }

        MPI_Send(&n, 1, MPI_INT, 0, 3, MPI_COMM_WORLD);
        MPI_Send(packed.data(), n * 2, MPI_INT, 0, 3, MPI_COMM_WORLD);
    }
}