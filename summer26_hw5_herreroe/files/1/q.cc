#include "q.h"

#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>
// TODO:
// 1. Implement the the functions in q.h.
// 2. Write some unit tests for them in student_test.cc

//test

int Fibonacci(int n) {
  if (n < 0) {
    return 1;
  }

  if (n == 0 || n == 1) {
    return 1;
  }

  unsigned long long prev = 1;
  unsigned long long curr = 1;

  for (long long int i = 3; i <= n; ++i) {
    unsigned long long next = prev + curr;
    prev = curr;
    curr = next;
  }

  return static_cast<int>(curr);
}