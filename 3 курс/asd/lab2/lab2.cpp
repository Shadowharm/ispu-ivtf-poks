//
// Created by Максим Прохоров on 01.11.2024.
//
// 2. АТД «дерево» - поиск кратчайшего пути на графе методом полного перебора в
// ширину
// результат записывать в дерево

#include "lab2.h"
#include <stdexcept>
#include <iostream>
#include <vector>

using namespace std;

template <class T>
struct Node {
    T data;
    int cost; // Накопленное расстояние
    Node* left;
    Node* right;

    Node(T data, int cost = 0) : data(data), cost(cost), left(nullptr), right(nullptr) {}
};

template <class T>
class BinaryTree
{
protected:
    Node<T> *root;
public:
    BinaryTree()
    {
        root = NULL;
    }
    void DelTree(Node <T> *&node)
    {
        if (node != nullptr)
        {
            DelTree(node->left);
            DelTree(node->right);
            delete node;
            node = NULL;
        }
    }
    ~BinaryTree()
    {
        DelTree(root);
    }
    void SetRoot(Node<T>* node) {
        root = node;
    }
    Node<T>* CreateNode(T data, int cost = 0) {
        return new Node<T>(data, cost);
    }
    Node<T> *GetRoot()
    {
        return root;
    }
    void CreateTree()
    {
        this->root = this->CreateNode(1);
        this->root->left = this->CreateNode(2);
        this->root->right = this->CreateNode(3);
        this->root->left->left = this->CreateNode(4);
        this->root->left->right = this->CreateNode(5);
    };
};


// Производный класс для тестирования, с реализацией CreateTree
template <class T>
class TestBinaryTree : public BinaryTree<T>
{
};

// Функция тестирования
void TestBinaryTreeStructure()
{
    TestBinaryTree<int> tree;
    tree.CreateTree();

    Node<int>* root = tree.GetRoot();

    if (root == NULL || root->data != 1) {
        std::cout << "Ошибка: корневой узел некорректен." << std::endl;
        return;
    }

    if (root->left == NULL || root->left->data != 2) {
        std::cout << "Ошибка: левый дочерний узел корня некорректен." << std::endl;
        return;
    }

    if (root->right == NULL || root->right->data != 3) {
        std::cout << "Ошибка: правый дочерний узел корня некорректен." << std::endl;
        return;
    }

    if (root->left->left == NULL || root->left->left->data != 4) {
        std::cout << "Ошибка: левый дочерний узел узла 2 некорректен." << std::endl;
        return;
    }

    if (root->left->right == NULL || root->left->right->data != 5) {
        std::cout << "Ошибка: правый дочерний узел узла 2 некорректен." << std::endl;
        return;
    }


    std::cout << "Все тесты пройдены успешно." << std::endl;
}

//class Graph {
//private:
//    unordered_map<int, vector<pair<int, int>>> adjList;
//
//public:
//    void AddEdge(int u, int v, int weight) {
//        adjList[u].push_back({v, weight});
//        adjList[v].push_back({u, weight}); // Для неориентированного графа
//    }
//
//    vector<pair<int, int>> GetNeighbors(int node) {
//        return adjList[node];
//    }
//};

// Функция поиска кратчайшего пути
//void FindShortestPath(Graph& graph, int start, int target) {
//    BinaryTree<int> tree;
//    Node<int>* root = tree.CreateNode(start, 0);
//    tree.SetRoot(root);
//
//    // Очередь для BFS
//    queue<Node<int>*> q;
//    q.push(root);
//
//    unordered_map<int, int> visited; // Хранение минимальной стоимости для каждой вершины
//    visited[start] = 0;
//
//    while (!q.empty()) {
//        Node<int>* current = q.front();
//        q.pop();
//
//        int currentNode = current->data;
//        int currentCost = current->cost;
//
//        // Если нашли целевую вершину
//        if (currentNode == target) {
//            cout << "Кратчайший путь: " << currentCost << endl;
//            return;
//        }
//
//        // Проходим по соседям
//        for (pair<int, int> neighbor : graph.GetNeighbors(currentNode)) {
//            int nextNode = neighbor.first;
//            int edgeCost = neighbor.second;
//            int newCost = currentCost + edgeCost;
//
//            // Если нашли более дешевый путь
//            if (visited.find(nextNode) == visited.end() || newCost < visited[nextNode]) {
//                visited[nextNode] = newCost;
//                Node<int>* childNode = tree.CreateNode(nextNode, newCost);
//                if (!current->left) {
//                    current->left = childNode;
//                } else {
//                    Node<int>* temp = current->left;
//                    while (temp->right) {
//                        temp = temp->right;
//                    }
//                    temp->right = childNode;
//                }
//                q.push(childNode);
//            }
//        }
//    }
//
//    cout << "Нет пути" << endl;
//}

void lab2() {
//    Graph graph;
//    graph.AddEdge(1, 2, 1);
//    graph.AddEdge(1, 3, 4);
//    graph.AddEdge(2, 3, 2);
//    graph.AddEdge(2, 4, 7);
//    graph.AddEdge(3, 4, 3);
//
//    int start = 1;
//    int target = 4;

//    FindShortestPath(graph, start, target);
}

