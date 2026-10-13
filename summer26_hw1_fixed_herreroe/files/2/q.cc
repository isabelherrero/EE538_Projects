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

bool IsPrime(int number) {
  if (number <= 1) {
    return false;
  }

  if (number == 2) {
    return true;
  }

  if (number % 2 == 0) {
    return false;
  }

  for (int i = 3; i * i <= number; i += 2) {
    if (number % i == 0) {
      return false;
    }
  }

  return true;
}