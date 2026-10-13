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

int CountNumberOfSpaces(std::string input) {
  int count = 0;
  for (char ch : input) {
    if (ch == ' ') {
      ++count;
    }
  }
  return count;
}