#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------

int* make_array(std::initializer_list<int> vals, int &size) {
    size = vals.size();
    int *arr = new int[size];
    int i = 0;
    for (int v : vals) arr[i++] = v;
    return arr;
}  

TEST(PushBack, OntoEmptyArray) {
    int size = 0;
    int *arr = new int[0];
    push_back(arr, size, 42);
    EXPECT_EQ(size, 1);
    EXPECT_EQ(arr[0], 42);
    delete[] arr;
}

TEST(PushBack, OntoNonEmptyArray) {
    int size;
    int *arr = make_array({1, 2, 3}, size);
    push_back(arr, size, 4);
    EXPECT_EQ(size, 4);
    EXPECT_EQ(arr[3], 4);
    delete[] arr;
}

TEST(PushBack, PreservesExistingElements) {
    int size;
    int *arr = make_array({10, 20}, size);
    push_back(arr, size, 30);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
    delete[] arr;
}

TEST(PushBack, PushZero) {
    int size;
    int *arr = make_array({1, 2}, size);
    push_back(arr, size, 0);
    EXPECT_EQ(arr[2], 0);
    EXPECT_EQ(size, 3);
    delete[] arr;
}

TEST(PushBack, MultiplePushes) {
    int size = 0;
    int *arr = new int[0];
    for (int i = 0; i < 5; i++) push_back(arr, size, i);
    EXPECT_EQ(size, 5);
    for (int i = 0; i < 5; i++) EXPECT_EQ(arr[i], i);
    delete[] arr;
} 

TEST(PopBack, EmptyArrayNoOp) {
    int size = 0;
    int *arr = new int[0];
    pop_back(arr, size);   // should not crash
    EXPECT_EQ(size, 0);
    delete[] arr;
}

TEST(PopBack, SingleElement) {
    int size;
    int *arr = make_array({99}, size);
    pop_back(arr, size);
    EXPECT_EQ(size, 0);
    delete[] arr;
}

TEST(PopBack, RemovesLastElement) {
    int size;
    int *arr = make_array({1, 2, 3}, size);
    pop_back(arr, size);
    EXPECT_EQ(size, 2);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    delete[] arr;
}

TEST(PopBack, MultiplePopsThenEmpty) {
    int size;
    int *arr = make_array({1, 2}, size);
    pop_back(arr, size);
    pop_back(arr, size);
    EXPECT_EQ(size, 0);
    pop_back(arr, size);   // pop on empty — no crash
    EXPECT_EQ(size, 0);
    delete[] arr;
}  

TEST(Insert, AtBeginning) {
    int size;
    int *arr = make_array({2, 3, 4}, size);
    insert(arr, size, 1, 0);
    EXPECT_EQ(size, 4);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    delete[] arr;
}

TEST(Insert, AtEnd) {
    int size;
    int *arr = make_array({1, 2, 3}, size);
    insert(arr, size, 4, 3);
    EXPECT_EQ(size, 4);
    EXPECT_EQ(arr[3], 4);
    delete[] arr;
}

TEST(Insert, AtMiddle) {
    int size;
    int *arr = make_array({1, 3, 4}, size);
    insert(arr, size, 2, 1);
    EXPECT_EQ(size, 4);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
    EXPECT_EQ(arr[3], 4);
    delete[] arr;
}

TEST(Insert, IntoEmptyArray) {
    int size = 0;
    int *arr = new int[0];
    insert(arr, size, 7, 0);
    EXPECT_EQ(size, 1);
    EXPECT_EQ(arr[0], 7);
    delete[] arr;
}   

TEST(Erase, FirstElement) {
    int size;
    int *arr = make_array({1, 2, 3}, size);
    int ret = erase(arr, size, 0);
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(size, 2);
    EXPECT_EQ(arr[0], 2);
    EXPECT_EQ(arr[1], 3);
    delete[] arr;
}

TEST(Erase, LastElement) {
    int size;
    int *arr = make_array({1, 2, 3}, size);
    int ret = erase(arr, size, 2);
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(size, 2);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    delete[] arr;
}

TEST(Erase, MiddleElement) {
    int size;
    int *arr = make_array({1, 2, 3}, size);
    int ret = erase(arr, size, 1);
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(size, 2);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 3);
    delete[] arr;
}

TEST(Erase, IndexOutOfBoundsNegative) {
    int size;
    int *arr = make_array({1, 2, 3}, size);
    EXPECT_EQ(erase(arr, size, -1), -1);
    EXPECT_EQ(size, 3);  // unchanged
    delete[] arr;
}

TEST(Erase, IndexOutOfBoundsTooLarge) {
    int size;
    int *arr = make_array({1, 2, 3}, size);
    EXPECT_EQ(erase(arr, size, 5), -1);
    EXPECT_EQ(size, 3);  // unchanged
    delete[] arr;
}

TEST(Erase, SingleElement) {
    int size;
    int *arr = make_array({42}, size);
    int ret = erase(arr, size, 0);
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(size, 0);
    delete[] arr;
}

TEST(Find, ElementExists) {
    int size;
    int *arr = make_array({1, 2, 3, 4}, size);
    EXPECT_EQ(find(arr, size, 3), 2);
    delete[] arr;
}

TEST(Find, ElementNotFound) {
    int size;
    int *arr = make_array({1, 2, 3}, size);
    EXPECT_EQ(find(arr, size, 99), -1);
    delete[] arr;
}

TEST(Find, FirstOccurrenceOnly) {
    int size;
    int *arr = make_array({5, 3, 5, 5}, size);
    EXPECT_EQ(find(arr, size, 5), 0);  // returns first index
    delete[] arr;
}

TEST(Find, FirstElement) {
    int size;
    int *arr = make_array({7, 2, 3}, size);
    EXPECT_EQ(find(arr, size, 7), 0);
    delete[] arr;
}

TEST(Find, LastElement) {
    int size;
    int *arr = make_array({1, 2, 9}, size);
    EXPECT_EQ(find(arr, size, 9), 2);
    delete[] arr;
}

TEST(Find, EmptyArray) {
    int *arr = new int[0];
    EXPECT_EQ(find(arr, 0, 1), -1);
    delete[] arr;
}

TEST(Find, ZeroElement) {
    int size;
    int *arr = make_array({0, 1, 2}, size);
    EXPECT_EQ(find(arr, size, 0), 0);
    delete[] arr;
}

TEST(Insert, OutOfRangeNegative) {
    int size;
    int *arr = make_array({1, 2, 3}, size);
    insert(arr, size, 99, -1);
    EXPECT_EQ(size, 3);  // unchanged
    delete[] arr;
}

TEST(Insert, OutOfRangeTooLarge) {
    int size;
    int *arr = make_array({1, 2, 3}, size);
    insert(arr, size, 99, 50);
    EXPECT_EQ(size, 3);  // unchanged
    delete[] arr;
}

TEST(Insert, AfterPopToEmpty) {
    int size;
    int *arr = make_array({1}, size);
    pop_back(arr, size);
    insert(arr, size, 5, 0);
    EXPECT_EQ(size, 1);
    EXPECT_EQ(arr[0], 5);
    delete[] arr;
}