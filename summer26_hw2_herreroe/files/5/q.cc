#include "q.h"

#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>
// TODO:
// 1. Implement the the functions in q.h.
// 2. Write some unit tests for them in student_test.cc

void push_back(int *&array, int &size, int element) {
    int *new_array = new int[size + 1];
    for (int i = 0; i < size; i++) {
        new_array[i] = array[i];
    }
    new_array[size] = element;
    delete[] array;
    array = new_array;
    size++;
}

void pop_back(int *&array, int &size) {
    if (size == 0) return;
    int *new_array = new int[size - 1];
    for (int i = 0; i < size - 1; i++) {
        new_array[i] = array[i];
    }
    delete[] array;
    array = new_array;
    size--;
}

void insert(int *&array, int &size, int element, int index) {
    // guard against out-of-range index
    if (index < 0 || index > size) return;
    int *new_array = new int[size + 1];
    for (int i = 0; i < index; i++) {
        new_array[i] = array[i];
    }
    new_array[index] = element;
    for (int i = index; i < size; i++) {
        new_array[i + 1] = array[i];
    }
    delete[] array;
    array = new_array;
    size++;
}

int erase(int *&array, int &size, int index) {
    if (index < 0 || index >= size) return -1;
    int *new_array = new int[size - 1];
    for (int i = 0; i < index; i++) {
        new_array[i] = array[i];
    }
    for (int i = index + 1; i < size; i++) {
        new_array[i - 1] = array[i];
    }
    delete[] array;
    array = new_array;
    size--;
    return 0;
}

int find(const int *array, int size, int element) {
    for (int i = 0; i < size; i++) {
        if (array[i] == element) return i;
    }
    return -1;
}