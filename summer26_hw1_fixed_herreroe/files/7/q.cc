#include "q.h"

#include <climits>
#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>

// TODO:
// 1. Implement the the functions in q.h.
// 2. Write some unit tests for them in student_test.cc

bool CanBecome(const std::string &s, const std::string &goal) {
  if (s.size() != goal.size()) {
    return false;
  }

  std::string doubled = s + s;
  return doubled.find(goal) != std::string::npos;
}