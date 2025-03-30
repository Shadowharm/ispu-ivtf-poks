//
// Created by Максим Прохоров on 24.02.2025.
//

#include "walk_down.h"
#include <iostream>
#include <vector>
#include <cassert>


using namespace std;

// Функция для преобразования поддерева в двоичную кучу (heapify)
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;      // Инициализируем наибольший элемент как корень
    int left = 2 * i + 1; // Левый потомок
    int right = 2 * i + 2; // Правый потомок

    // Если левый потомок больше корня
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // Если правый потомок больше, чем наибольший элемент на данный момент
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // Если наибольший элемент не корень, меняем местами и рекурсивно вызываем heapify
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

// Основная функция пирамидальной сортировки (Heap Sort)
void heapSort(vector<int>& arr) {
    int n = arr.size();

    // Построение кучи (перегруппировка массива)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Извлечение элементов из кучи по одному
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]); // Перемещаем текущий корень в конец
        heapify(arr, i, 0);   // Вызываем heapify на уменьшенной куче
    }
}

// Функция для вывода массива
void printArray(const vector<int>& arr) {
    for (int num : arr)
        cout << num << " ";
    cout << endl;
}

void testHeapSort() {
    vector<int> test1 = {12, 11, 13, 5, 6, 7};
    vector<int> expected1 = {5, 6, 7, 11, 12, 13};
    heapSort(test1);
    assert(test1 == expected1);

    vector<int> test2 = {4, 10, 3, 5, 1};
    vector<int> expected2 = {1, 3, 4, 5, 10};
    heapSort(test2);
    assert(test2 == expected2);

    vector<int> test3 = {1, 2, 3, 4, 5};
    vector<int> expected3 = {1, 2, 3, 4, 5};
    heapSort(test3);
    assert(test3 == expected3);

    vector<int> test4 = {5, 4, 3, 2, 1};
    vector<int> expected4 = {1, 2, 3, 4, 5};
    heapSort(test4);
    assert(test4 == expected4);

    vector<int> test5 = {100};
    vector<int> expected5 = {100};
    heapSort(test5);
    assert(test5 == expected5);

    vector<int> test6 = {};
    vector<int> expected6 = {};
    heapSort(test6);
    assert(test6 == expected6);

    cout << "Все тесты пройдены успешно!" << endl;
}

void walk_down() {
    vector<int> arr = {12, 11, 13, 5, 6, 7};
    cout << "Исходный массив: ";
    printArray(arr);

    heapSort(arr);

//    testHeapSort();

    cout << "Отсортированный массив: ";
    printArray(arr);
}
