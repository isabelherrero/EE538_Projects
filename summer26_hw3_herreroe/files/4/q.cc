#include "q.h"

#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>
// TODO:
// 1. Implement the the functions in q.h.
// 2. Write some unit tests for them in student_test.cc

SizedMap::SizedMap(int capacity) : capacity_(capacity) {}

SizedMap::SizedMap(const SizedMap& other) : capacity_(other.capacity_), map_(other.map_), keys_(other.keys_) {}

std::string SizedMap::Get(int key) const {
  auto it = map_.find(key);
  if (it == map_.end()) {
    return "INVALID_KEY";
  }
  return it->second;
}

void SizedMap::Put(int key, std::string value) {
  if (map_.find(key) != map_.end()) {
    map_[key] = value;
    return;
  }

  if (static_cast<int>(map_.size()) >= capacity_) {
    int oldest_key = keys_.front();
    keys_.pop();
    map_.erase(oldest_key);
  }

  map_[key] = value;
  keys_.push(key);
}

int SizedMap::Size() const { return static_cast<int>(map_.size()); }

SizedMap SizedMap::operator+(const SizedMap& sm2) {
  SizedMap result(capacity_ + sm2.capacity_);

  std::queue<int> first_order = keys_;
  while (!first_order.empty()) {
    int key = first_order.front();
    first_order.pop();
    auto sm2_it = sm2.map_.find(key);
    std::string value =
        (sm2_it != sm2.map_.end()) ? sm2_it->second : map_.at(key);
    result.map_[key] = value;
    result.keys_.push(key);
  }

  std::queue<int> second_order = sm2.keys_;
  while (!second_order.empty()) {
    int key = second_order.front();
    second_order.pop();
    if (result.map_.find(key) == result.map_.end()) {
      result.map_[key] = sm2.map_.at(key);
      result.keys_.push(key);
    }
  }

  return result;
}

void SizedMap::Reverse() {
  std::vector<int> order;
  std::queue<int> temp = keys_;
  while (!temp.empty()) {
    order.push_back(temp.front());
    temp.pop();
  }
  
  int left = 0;
  int right = static_cast<int>(order.size()) - 1;
  while (left < right) {
    int swap_tmp = order[left];
    order[left] = order[right];
    order[right] = swap_tmp;
    left++;
    right--;
  }

  std::queue<int> reversed_queue;
  for (int key : order) {
    reversed_queue.push(key);
  }
  keys_ = reversed_queue;
}