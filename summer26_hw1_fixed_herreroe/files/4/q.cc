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

std::vector<int> Flatten3DVector(
    std::vector<std::vector<std::vector<int>>> input) {
  std::vector<int> output;

  for (const auto& level1 : input) {
    for (const auto& level2 : level1) {
      for (int value : level2) {
        output.push_back(value);
      }
    }
  }

  return output;
}