//
// Created by Максим Прохоров on 01.11.2024.
//

#include "lab1.h"
#include <stdexcept>
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

template <class T>
struct Node {
    T data;
    Node* next;
};

template <class T>
class Stack {
private:
    Node<T>* top;

public:
    Stack();
    ~Stack();

    bool Push(T d);
    bool Pop(T &d);
    bool IsEmpty() const;
};

template <class T>
Stack<T>::Stack() {
    top = nullptr;
}

template <class T>
Stack<T>::~Stack() {
    T value;
    while (!IsEmpty()) {
        Pop(value);
    }
}

template <class T>
bool Stack<T>::Push(T d) {
    auto* t = new Node<T>;
    t->data = d;
    t->next = top;
    top = t;
    return true;
}

template <class T>
bool Stack<T>::Pop(T &d) {
    if (IsEmpty()) {
        return false;
    }
    const Node<T>* t = top;
    d = top->data;
    top = top->next;
    delete t;
    return true;
}

template <class T>
bool Stack<T>::IsEmpty() const {
    return top == nullptr;
}

void TestStack()
{
    Stack<int> s;
    int value;

    cout << "Is stack empty? " << s.IsEmpty() << endl;

    for (int i = 0; i < 20; ++i)
    {
        s.Push(i);
        cout << "Pushed to stack: " << i << endl;
    }

    cout << "Is stack empty? " << s.IsEmpty() << endl;

    while (!s.IsEmpty())
    {
        cout << "Popped from stack: success - " << s.Pop(value) << "; value - " << value << endl;
    }

    cout << "Is stack empty? " << s.IsEmpty() << endl;

    cout << "Popped from stack: success - " << s.Pop(value) << endl;
}

const int n = 5;
int graph[n+1][n+1]  = {
        {0, 1, 1, 1},
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {1, 1, 1, 0}
};

void depth_find(int start_v, int skeleton[][2], int *k) {
    Stack<int> stack;
    stack.Push(start_v); // помещаем стартовую вершину в стек

    vector<bool> visited(n + 1, false);
    visited[start_v] = true; // отмечаем start_v как посещённую

    while (!stack.IsEmpty()) {
        int v;
        stack.Pop(v);

        // перебираем все вершины
        for (int r = 0; r <= n; r++) {
            if (graph[v][r] != 0 && !visited[r]) {
                skeleton[*k][0] = v; // добавляем в остов ребро (v, r)
                skeleton[*k][1] = r;
                (*k)++; // увеличиваем счётчик рёбер

                visited[r] = true; // помечаем вершину r как посещённую

                stack.Push(r);
            }
        }
    }
}

void lab1 () {



    int skeleton[n - 1][2];
    int k = 0;

    depth_find(0, skeleton, &k);

    cout << "Вершины остова графа:\n";
    for (int i = 0; i < k; i++) {
        cout << skeleton[i][0] + 1 << " - " << skeleton[i][1] + 1 << endl;
    }
}