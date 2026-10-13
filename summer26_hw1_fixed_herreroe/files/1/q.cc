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

std::vector<int> Reverse(std::vector<int> input) {
  std::vector<int> output;
  for (int i = static_cast<int>(input.size()) - 1; i >= 0; --i) {
    output.push_back(input[i]);
  }
  return output;
}

std::vector<int> PlusOne(std::vector<int> input) {
  if (input.empty()) {
    return {};
  }

  for (int digit : input) {
    if (digit < 0 || digit > 9) {
      return {-1};
    }
  }

  int carry = 1;
  for (int i = static_cast<int>(input.size()) - 1; i >= 0; --i) {
    int sum = input[i] + carry;
    input[i] = sum % 10;
    carry = sum / 10;
    if (carry == 0) {
      break;
    }
  }

  if (carry > 0) {
    input.insert(input.begin(), carry);
  }

  return input;
}
