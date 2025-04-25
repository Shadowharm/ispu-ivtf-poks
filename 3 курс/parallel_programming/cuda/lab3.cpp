#include <cstdio>
#include <cmath>
#include <vector>
#include <omp.h>

#define LENGTH 100.0
#define h 0.1

void Yakobi(std::vector<std::vector<double>>& data, std::vector<std::vector<double>>& nextData, int height, int width)
{
    for (int y = 1; y < height - 1; y++)
    {
        for (int x = 1; x < width - 1; x++)
        {
            nextData[y][x] = 0.25 * (data[y - 1][x] + data[y + 1][x] + data[y][x - 1] + data[y][x + 1]);
        }
    }

    for (int y = 1; y < height - 1; y++)
    {
        for (int x = 1; x < width - 1; x++)
        {
            data[y][x] = nextData[y][x];
        }
    }
}

int cuda_lab3()
{
    const int rows = static_cast<int>(LENGTH);
    const int cols = rows;
    std::vector<std::vector<double>> data(rows, std::vector<double>(cols, 0.0));
    std::vector<std::vector<double>> tempData(rows, std::vector<double>(cols, 0.0));

    for (int j = 0; j < cols; ++j)
    {
        double y_val = j * h;
        data[0][j] = 30.0 * sin(M_PI * y_val);              
        data[rows - 1][j] = 20.0 * y_val;                   
    }

    for (int i = 0; i < rows; ++i)
    {
        double x_val = i * h;
        data[i][cols - 1] = 20.0 * x_val;                   
        data[i][0] = 30.0 * x_val * (100.0 - x_val);        
    }

    const int rounds = 1000;
    double start = omp_get_wtime();
    for (int t = 0; t < rounds; ++t)
    {
        Yakobi(data, tempData, rows, cols);
    }
    double stop = omp_get_wtime();

    printf("Затраченное время на последовательное выполнение: %.6f секунд\n\n", stop - start);
    for (int y = 0; y < /*rows*/ 50; ++y)
    {
        for (int x = 0; x < /*cols*/ 50; ++x)
        {
            printf("%8.2f ", data[y][x]);
        }
        printf("\n");
    }

    return 0;
}