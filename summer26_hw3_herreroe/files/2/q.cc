#include "q.h"

#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>
// TODO:
// 1. Implement the the functions in q.h.
// 2. Write some unit tests for them in student_test.cc

bool CPPLib::CheckValidExpression(const std::string& input) {
  std::vector<char> open_brackets;

  for (char c : input) {
    if (c == '(' || c == '[' || c == '{') {
      open_brackets.push_back(c);
      continue;
    }
    if (c == ')' || c == ']' || c == '}') {
      if (open_brackets.empty()) {
        return false;
      }
      char last_open = open_brackets.back();
      bool matches = (c == ')' && last_open == '(') ||
                     (c == ']' && last_open == '[') ||
                     (c == '}' && last_open == '{');
      if (!matches) {
        return false;
      }
      open_brackets.pop_back();
    }
  }
  return open_brackets.empty();
}

bool CPPLib::IsPalindrome(const std::string& input) {
  size_t left = 0;
  size_t right = input.length() == 0 ? 0 : input.length() - 1;

  while (left < right) {
    if (input[left] != input[right]) {
      return false;
    }
    left++;
    right--;
  }

  return true;
}

int CPPLib::OddChar(const std::string& input) {
  if (input.empty()) {
    return -1;
  }

  unsigned char result = 0;
  for (char c : input) {
    result ^= static_cast<unsigned char>(c);
  }
  return static_cast<int>(result);
}