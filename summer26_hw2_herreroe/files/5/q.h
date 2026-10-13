#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

// TODO: Implement these functions in q.cc

// We are writing these functions to be used on a dynamic array of non-negative
// integers.

// Note that these functions take a reference to a pointer so that you can
// modify the value of the pointer.
// Also note that some functions should change the value of both array AND size.

// Function to add an element to the back of the array. Updates both array and
// size.
void push_back(int *&array, int &size, int element);

// Function to remove the last element from the array. Updates both array and
// size.
// No operations if array is empty.
void pop_back(int *&array, int &size);

// Function to insert an element at a specific index in the array. Updates both
// array and size.
void insert(int *&array, int &size, int element, int index);

// Function to erase an element at a specific index from the array.
// Returns -1 for errors (index out of bound) and 0 otherwise. Updates both
// array and size.
int erase(int *&array, int &size, int index);

// Function to find the first occurrence of an element in the array.
// Return -1 if it didn't exist.
int find(const int *array, int size, int element);

#endif