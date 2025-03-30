//
// Created by Максим Прохоров on 09.11.2024.
//

#include "findCyclesUtil.h"
#include <iostream>
#include <vector>

void findCyclesUtil(int v, int start, const int graph[][4], int size, std::vector<bool>& visited, std::vector<int>& path, std::vector<std::vector<int>>& cycles) {
    visited[v] = true;
    path.push_back(v);

    // Обходим все смежные вершины
    for (int i = 0; i < size; i++) {
        if (graph[v][i] == 1) {  // Если существует ребро
            if (i == start && path.size() > 2) { // Цикл найден
                path.push_back(start);
                cycles.push_back(path);
                path.pop_back();
            }
            else if (!visited[i]) { // Если вершина не была посещена
                findCyclesUtil(i, start, graph, size, visited, path, cycles);
            }
        }
    }

    // Убираем текущую вершину из пути и отмечаем как непосещённую
    path.pop_back();
    visited[v] = false;
}

void findCycles(const int graph[][4], int size) {
    std::vector<std::vector<int>> cycles;

    // Для каждой вершины ищем циклы
    for (int i = 0; i < size; i++) {
        std::vector<bool> visited(size, false);
        std::vector<int> path;
        findCyclesUtil(i, i, graph, size, visited, path, cycles);
    }

    // Выводим найденные циклы
    std::cout << "Независимые контуры (циклы) графа:" << std::endl;
    for (const auto& cycle : cycles) {
        for (int v : cycle) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Общее количество контуров: " << cycles.size() << std::endl;

}

void findCycles() {
    const int SIZE = 4;
    int graph[SIZE][SIZE] = {
            {0, 0, 1, 1},
            {0, 0, 1, 1},
            {1, 1, 0, 1},
            {1, 1, 1, 0}
    };

    findCycles(graph, SIZE);
}