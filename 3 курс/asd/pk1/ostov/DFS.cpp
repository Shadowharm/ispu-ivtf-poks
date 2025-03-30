//
// Created by Максим Прохоров on 09.11.2024.
//

#include "DFS.h"
#include <iostream>
#include <vector>

void dfsSpanningTree(int current, const int graph[][4], int size, std::vector<bool>& visited, std::vector<std::pair<int, int>>& spanningTreeEdges) {
    visited[current] = true; // Помечаем текущую вершину как посещённую

    // Проходим по всем вершинам, смежным с текущей
    for (int i = 0; i < size; i++) {
        if (graph[current][i] == 1 && !visited[i]) { // Если есть ребро и вершина не посещена
            spanningTreeEdges.push_back({current, i}); // Добавляем ребро в остов
            dfsSpanningTree(i, graph, size, visited, spanningTreeEdges); // Рекурсивный вызов для смежной вершины
        }
    }
}

void DFS() {
    const int SIZE = 4;
    int graph[SIZE][SIZE] = {
            {0, 1, 1, 1},
            {1, 0, 1, 1},
            {1, 1, 0, 1},
            {1, 1, 1, 0}
    };

    std::vector<bool> visited(SIZE, false); // Массив для отслеживания посещенных вершин
    std::vector<std::pair<int, int>> spanningTreeEdges; // Список рёбер остова

    // Запускаем DFS с начальной вершины
    dfsSpanningTree(0, graph, SIZE, visited, spanningTreeEdges);

    // Выводим рёбра остова графа
    std::cout << "Рёбра остова графа:" << std::endl;
    for (const auto& edge : spanningTreeEdges) {
        std::cout << edge.first << " - " << edge.second << std::endl;
    }
}