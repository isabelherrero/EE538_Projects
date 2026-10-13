#include "q.h"

#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>
// TODO:
// 1. Implement the the functions in q.h.
// 2. Write some unit tests for them in student_test.cc

StudentMaxHeap::StudentMaxHeap(std::vector<Student>& input) {
  ConvertToHeap(input);
}

int StudentMaxHeap::GetParentIndex(int i) {
  if (i <= 0 || i >= static_cast<int>(data_.size())) {
    return INT_MAX;
  }
  return (i - 1) / 2;
}

int StudentMaxHeap::GetLeftIndex(int i) {
  if (i < 0 || i >= static_cast<int>(data_.size())) {
    return INT_MAX;
  }
  int left = 2 * i + 1;
  if (left >= static_cast<int>(data_.size())) {
    return INT_MAX;
  }
  return left;
}

int StudentMaxHeap::GetRightIndex(int i) {
  if (i < 0 || i >= static_cast<int>(data_.size())) {
    return INT_MAX;
  }
  int right = 2 * i + 2;
  if (right >= static_cast<int>(data_.size())) {
    return INT_MAX;
  }
  return right;
}

int StudentMaxHeap::GetLargestChildIndex(int i) {
  int left = GetLeftIndex(i);
  int right = GetRightIndex(i);

  if (left == INT_MAX && right == INT_MAX) {
    return INT_MAX;
  }
  if (right == INT_MAX) {
    return left;
  }
  if (left == INT_MAX) {
    return right;
  }
  return (data_[left] > data_[right]) ? left : right;
}

Student StudentMaxHeap::GetParent(int i) {
  int parent_index = GetParentIndex(i);
  if (parent_index == INT_MAX) {
    return Student();
  }
  return data_[parent_index];
}

Student StudentMaxHeap::GetLeft(int i) {
  int left_index = GetLeftIndex(i);
  if (left_index == INT_MAX) {
    return Student();
  }
  return data_[left_index];
}

Student StudentMaxHeap::GetRight(int i) {
  int right_index = GetRightIndex(i);
  if (right_index == INT_MAX) {
    return Student();
  }
  return data_[right_index];
}

Student StudentMaxHeap::top() {
  if (empty()) {
    return Student();
  }
  return data_[0];
}

void StudentMaxHeap::push(const Student& student) {
  data_.push_back(student);
  TrickleUp(static_cast<int>(data_.size()) - 1);
}

bool StudentMaxHeap::pop() {
  if (empty()) {
    return false;
  }
  std::swap(data_.front(), data_.back());
  data_.pop_back();
  if (!empty()) {
    TrickleDown(0);
  }
  return true;
}

void StudentMaxHeap::TrickleUp(int i) {
  while (true) {
    int parent_index = GetParentIndex(i);
    if (parent_index == INT_MAX) {
      break;
    }
    if (data_[i] > data_[parent_index]) {
      std::swap(data_[i], data_[parent_index]);
      i = parent_index;
    } else {
      break;
    }
  }
}

void StudentMaxHeap::TrickleDown(int i) {
  while (true) {
    int largest_index = GetLargestChildIndex(i);
    if (largest_index == INT_MAX) {
      break;
    }
    if (data_[largest_index] > data_[i]) {
      std::swap(data_[i], data_[largest_index]);
      i = largest_index;
    } else {
      break;
    }
  }
}

void StudentMaxHeap::ConvertToHeap(const std::vector<Student>& input) {
  data_ = input;
  for (int i = static_cast<int>(data_.size()) / 2 - 1; i >= 0; i--) {
    TrickleDown(i);
  }
}

void HeapSort(std::vector<Student>& input) {
  StudentMaxHeap heap(input);
  for (int i = static_cast<int>(input.size()) - 1; i >= 0; i--) {
    input[i] = heap.top();
    heap.pop();
  }
}