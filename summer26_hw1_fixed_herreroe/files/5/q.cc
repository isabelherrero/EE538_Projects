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

int ClimbStairs(int n) {
  if (n < 0) {
    return -1;
  }

  if (n == 0) {
    return 0;
  }

  if (n == 1) {
    return 1;
  }

  if (n == 2) {
    return 2;
  }

  if (n == 3) {
    return 4;
  }

  return ClimbStairs(n - 1) +
         ClimbStairs(n - 2) +
         ClimbStairs(n - 3);
}