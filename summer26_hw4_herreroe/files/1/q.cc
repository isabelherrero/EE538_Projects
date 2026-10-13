#include "q.h"

#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <algorithm>
// TODO:
// 1. Implement the the functions in q.h.
// 2. Write some unit tests for them in student_test.cc

std::vector<int> ProductOfKHighestNumbers(const std::vector<int> &input, int k) {
  std::vector<int> result;

  int n = static_cast<int>(input.size());

  if (k <= 0 || n < k) {
    return result;
  }

  result.reserve(n - k + 1);

  for (int i = k - 1; i < n; i++) {
    std::vector<int> window(input.begin(), input.begin() + i + 1);
    std::sort(window.begin(), window.end(), std::greater<int>());

    int product = 1;
    for (int j = 0; j < k; j++) {
      product *= window[j];
    }
    result.push_back(product);
  }

  return result;
}
