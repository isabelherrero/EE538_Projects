#include "q.h"

#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <set>
// TODO:
// 1. Implement the the functions in q.h.
// 2. Write some unit tests for them in student_test.cc

SinglyLinkedList::SinglyLinkedList(const std::vector<int> &v) {
  head_ = nullptr;
  size_ = 0;
  for (int val : v) {
    push_back(val);
  }
}

SinglyLinkedList::SinglyLinkedList(const SinglyLinkedList &rhs) {
  head_ = nullptr;
  size_ = 0;
  for (ListNode *cur = rhs.head_; cur != nullptr; cur = cur->next) {
    push_back(cur->val);
  }
}

SinglyLinkedList::~SinglyLinkedList() {
  ListNode *cur = head_;
  while (cur != nullptr) {
    ListNode *next = cur->next;
    delete cur;
    cur = next;
  }
  head_ = nullptr;
  size_ = 0;
}

bool SinglyLinkedList::empty() { return size_ == 0; }

int SinglyLinkedList::size() { return size_; }

ListNode *SinglyLinkedList::head() { return head_; }

void SinglyLinkedList::push_back(int i) {
  ListNode *new_node = new ListNode(i);
  if (head_ == nullptr) {
    head_ = new_node;
  } else {
    ListNode *tail = GetBackPointer();
    tail->next = new_node;
  }
  size_++;
}

bool SinglyLinkedList::pop_back() {
  if (empty()) {
    return false;
  }
  if (size_ == 1) {
    delete head_;
    head_ = nullptr;
    size_ = 0;
    return true;
  }
  ListNode *second_last = GetIthPointer(size_ - 2);
  delete second_last->next;
  second_last->next = nullptr;
  size_--;
  return true;
}

int SinglyLinkedList::back() {
  if (empty()) {
    return -1;
  }
  return GetBackPointer()->val;
}

ListNode *SinglyLinkedList::GetBackPointer() {
  if (head_ == nullptr) {
    return nullptr;
  }
  ListNode *cur = head_;
  while (cur->next != nullptr) {
    cur = cur->next;
  }
  return cur;
}

ListNode *SinglyLinkedList::GetIthPointer(int i) {
  if (i < 0 || i >= size_) {
    return nullptr;
  }
  ListNode *cur = head_;
  for (int j = 0; j < i; j++) {
    cur = cur->next;
  }
  return cur;
}

int &SinglyLinkedList::operator[](int i) {
  ListNode *node = GetIthPointer(i);
  if (node == nullptr) {
    minusOne_ = -1;
    return minusOne_;
  }
  return node->val;
}

void SinglyLinkedList::print() {
  for (ListNode *cur = head_; cur != nullptr; cur = cur->next) {
    std::cout << cur->val;
    if (cur->next != nullptr) {
      std::cout << " -> ";
    }
  }
  std::cout << std::endl;
}

std::vector<int> SinglyLinkedList::convert_to_vector() {
  std::vector<int> result;
  for (ListNode *cur = head_; cur != nullptr; cur = cur->next) {
    result.push_back(cur->val);
  }
  return result;
}

ListNode *SinglyLinkedList::erase(int i) {
  if (i < 0 || i >= size_) {
    return nullptr;
  }

  if (i == 0) {
    ListNode *target = head_;
    head_ = head_->next;
    delete target;
    size_--;
    return nullptr;
  }

  ListNode *prev = GetIthPointer(i - 1);
  ListNode *target = prev->next;
  prev->next = target->next;
  delete target;
  size_--;
  return prev;
}

ListNode *SinglyLinkedList::GetPrevious(ListNode *p) {
  if (p == nullptr || head_ == nullptr || head_ == p) {
    return nullptr;
  }
  ListNode *cur = head_;
  while (cur->next != nullptr) {
    if (cur->next == p) {
      return cur;
    }
    cur = cur->next;
  }
  return nullptr;
}

ListNode *SinglyLinkedList::erase(ListNode *p) {
  if (p == nullptr || head_ == nullptr) {
    return nullptr;
  }

  if (head_ == p) {
    head_ = head_->next;
    delete p;
    size_--;
    return nullptr;
  }

  ListNode *prev = GetPrevious(p);
  if (prev == nullptr) {
    return nullptr;
  }
  prev->next = p->next;
  delete p;
  size_--;
  return prev;
}

void SinglyLinkedList::remove_duplicates() {
  if (head_ == nullptr) {
    return;
  }
  std::set<int> seen;
  seen.insert(head_->val);
  ListNode *cur = head_;
  while (cur->next != nullptr) {
    if (seen.count(cur->next->val)) {
      ListNode *dup = cur->next;
      cur->next = dup->next;
      delete dup;
      size_--;
    } else {
      seen.insert(cur->next->val);
      cur = cur->next;
    }
  }
}

void SinglyLinkedList::reverse() {
  ListNode *prev = nullptr;
  ListNode *cur = head_;
  while (cur != nullptr) {
    ListNode *next = cur->next;
    cur->next = prev;
    prev = cur;
    cur = next;
  }
  head_ = prev;
}