//
// Created by Максим Прохоров on 13.12.2024.
//

#include "lab4.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <iterator>

// Структура для представления рёбер между преподавателями и классами
struct Edge {
    int x, y;  // x - преподаватель, y - класс
    int weight; // количество занятий
};

// Структура для представления графа
class BipartiteGraph {
public:
    std::vector<int> X, Y; // Множества вершин X и Y (преподаватели и классы)
    std::vector<Edge> edges; // Рёбра графа

    // Добавить ребро в граф
    void addEdge(int x, int y, int weight) {
        edges.push_back({x, y, weight});
    }

    // Найти максимальную степень вершины из X
    int maxDegreeX() {
        std::map<int, int> degreeMap;
        for (const auto& edge : edges) {
            degreeMap[edge.x] += edge.weight;
        }
        return std::max_element(degreeMap.begin(), degreeMap.end(),
                                [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                                    return a.second < b.second;
                                })->second;
    }

    // Найти максимальную степень вершины из Y
    int maxDegreeY() {
        std::map<int, int> degreeMap;
        for (const auto& edge : edges) {
            degreeMap[edge.y] += edge.weight;
        }
        return std::max_element(degreeMap.begin(), degreeMap.end(),
                                [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                                    return a.second < b.second;
                                })->second;
    }

    // Строим подграф G1, G2, и G* в зависимости от найденных максимальных степеней
    void constructSubgraph(int maxDegreeX, int maxDegreeY) {
        // Реализовать построение подграфа G1 и G2
    }

    // Найти паросочетание для графа
    std::set<std::pair<int, int>> findMatching() {
        std::set<std::pair<int, int>> matching;
        // Реализовать алгоритм нахождения максимального паросочетания (например, через поиск в ширину)
        return matching;
    }

    // Удалить рёбра, которые входят в паросочетание
    void removeMatching(const std::set<std::pair<int, int>>& matching) {
        edges.erase(std::remove_if(edges.begin(), edges.end(),
                                   [&matching](const Edge& e) {
                                       return matching.count({e.x, e.y}) > 0;
                                   }), edges.end());
    }
};

void lab4() {
    BipartiteGraph graph;

    // Пример добавления рёбер
    graph.addEdge(0, 0, 2); // Преподаватель 0, класс 0, 2 занятия
    graph.addEdge(1, 0, 3); // Преподаватель 1, класс 0, 3 занятия
    graph.addEdge(0, 1, 4); // Преподаватель 0, класс 1, 4 занятия
    graph.addEdge(2, 1, 5); // Преподаватель 2, класс 1, 5 занятий

    // Печать максимальной степени
    int maxDegreeX = graph.maxDegreeX();
    int maxDegreeY = graph.maxDegreeY();
    std::cout << "Максимальная степень X: " << maxDegreeX << std::endl;
    std::cout << "Максимальная степень Y: " << maxDegreeY << std::endl;

    // Строим подграфы G1 и G2, используя максимальные степени
    graph.constructSubgraph(maxDegreeX, maxDegreeY);

    // Находим паросочетания M1 и M2
    auto matching1 = graph.findMatching();
    std::cout << "Паросочетание M1: ";
    for (const auto& m : matching1) {
        std::cout << "(" << m.first << ", " << m.second << ") ";
    }
    std::cout << std::endl;

    // Удаляем рёбра из графа, которые были в паросочетаниях
    graph.removeMatching(matching1);

    // Повторяем поиск паросочетания на обновлённом графе
    auto matching2 = graph.findMatching();
    std::cout << "Паросочетание M2: ";
    for (const auto& m : matching2) {
        std::cout << "(" << m.first << ", " << m.second << ") ";
    }
    std::cout << std::endl;

    // Строим объединённый граф G* и находим паросочетание для него
    graph.constructSubgraph(maxDegreeX, maxDegreeY);
    auto matchingStar = graph.findMatching();
    std::cout << "Паросочетание M* для G*: ";
    for (const auto& m : matchingStar) {
        std::cout << "(" << m.first << ", " << m.second << ") ";
    }
    std::cout << std::endl;

}