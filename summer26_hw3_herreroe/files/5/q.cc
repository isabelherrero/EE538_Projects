#include "q.h"

#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>
// TODO:
// 1. Implement the the functions in q.h.
// 2. Write some unit tests for them in student_test.cc

MyVector::MyVector() : data_(nullptr), size_(0), error_(ErrorCode::kNoError) {}

MyVector::MyVector(int size) : error_(ErrorCode::kNoError) {
  if (size <= 0) {
    data_ = nullptr;
    size_ = 0;
  } else {
    data_ = new int[size]();
    size_ = size;
  }
}

MyVector::MyVector(const MyVector& rhs) : size_(rhs.size_), error_(ErrorCode::kNoError) {
  if (size_ > 0) {
    data_ = new int[size_];
    for (int i = 0; i < size_; i++) {
      data_[i] = rhs.data_[i];
    }
  } else {
    data_ = nullptr;
  }
}

MyVector::~MyVector() {
  delete[] data_;
  data_ = nullptr;
  size_ = 0;
}

void MyVector::push_back(int value) {
  int* new_data = new int[size_ + 1];
  for (int i = 0; i < size_; i++) {
    new_data[i] = data_[i];
  }
  new_data[size_] = value;

  delete[] data_;
  data_ = new_data;
  size_++;
  error_ = ErrorCode::kNoError;
}

int MyVector::pop_back() {
  if (size_ == 0) {
    error_ = ErrorCode::kPopFromEmptyVector;
    return -1;
  }

  int value = data_[size_ - 1];
  int* new_data = nullptr;
  if (size_ - 1 > 0) {
    new_data = new int[size_ - 1];
    for (int i = 0; i < size_ - 1; i++) {
      new_data[i] = data_[i];
    }
  }

  delete[] data_;
  data_ = new_data;
  size_--;
  error_ = ErrorCode::kNoError;
  return value;
}

void MyVector::push_front(int value) {
  int* new_data = new int[size_ + 1];
  new_data[0] = value;
  for (int i = 0; i < size_; i++) {
    new_data[i + 1] = data_[i];
  }

  delete[] data_;
  data_ = new_data;
  size_++;
  error_ = ErrorCode::kNoError;
}

int MyVector::pop_front() {
  if (size_ == 0) {
    error_ = ErrorCode::kPopFromEmptyVector;
    return -1;
  }

  int value = data_[0];
  int* new_data = nullptr;
  if (size_ - 1 > 0) {
    new_data = new int[size_ - 1];
    for (int i = 0; i < size_ - 1; i++) {
      new_data[i] = data_[i + 1];
    }
  }

  delete[] data_;
  data_ = new_data;
  size_--;
  error_ = ErrorCode::kNoError;
  return value;
}

void MyVector::insert(int value, int index) {
  if (index < -1 || index > size_ - 1) {
    error_ = ErrorCode::kIndexError;
    return;
  }

  int* new_data = new int[size_ + 1];
  int pos = 0;
  for (int i = 0; i <= index; i++) {
    new_data[pos++] = data_[i];
  }
  new_data[pos++] = value;
  for (int i = index + 1; i < size_; i++) {
    new_data[pos++] = data_[i];
  }

  delete[] data_;
  data_ = new_data;
  size_++;
  error_ = ErrorCode::kNoError;
}

int MyVector::at(int index) {
  if (index < 0 || index >= size_) {
    error_ = ErrorCode::kIndexError;
    return -1;
  }
  error_ = ErrorCode::kNoError;
  return data_[index];
}

int MyVector::find(int item) {
  for (int i = 0; i < size_; i++) {
    if (data_[i] == item) {
      error_ = ErrorCode::kNoError;
      return i;
    }
  }
  error_ = ErrorCode::kNotFound;
  return -1;
}

ErrorCode MyVector::get_error() const { return error_; }

int MyVector::size() const { return size_; }

std::vector<int> MyVector::ConvertToStdVector() {
  std::vector<int> result;
  for (int i = 0; i < size_; i++) {
    result.push_back(data_[i]);
  }
  return result;
}