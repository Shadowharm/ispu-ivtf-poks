//
// Created by Максим Прохоров on 09.11.2024.
//

#include "BFS.h"
#include <iostream>
#include <queue>
#include <vector>

void bfsSpanningTree(int start, const int graph[][4], int size) {
    std::vector<bool> visited(size, false); // Отмечаем посещённые вершины
    std::queue<int> q; // Очередь для BFS

    // Массив для хранения остова (список рёбер)
    std::vector<std::pair<int, int>> spanningTreeEdges;

    // Начинаем с начальной вершины
    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        // Проходим по всем смежным вершинам
        for (int i = 0; i < size; i++) {
            // Если есть ребро и вершина не была посещена
            if (graph[current][i] == 1 && !visited[i]) {
                visited[i] = true; // Отмечаем вершину как посещённую
                q.push(i); // Добавляем вершину в очередь
                spanningTreeEdges.push_back({current, i}); // Добавляем ребро в остов
            }
        }
    }

    // Выводим рёбра остова графа
    std::cout << "Рёбра остова графа:" << std::endl;
    for (const auto& edge : spanningTreeEdges) {
        std::cout << edge.first << " - " << edge.second << std::endl;
    }
}

void BFS() {
    const int SIZE = 4;
    int graph[SIZE][SIZE] = {
            {0, 1, 1, 1},
            {1, 0, 1, 1},
            {1, 1, 0, 1},
            {1, 1, 1, 0}
    };

    // Вызываем функцию поиска остова
    bfsSpanningTree(0, graph, SIZE);

}