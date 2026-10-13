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

ErrorCode Calculator(float a, float b, float &sum, float &diff,
                     float &product, float &ratio) {
  sum = a + b;
  diff = a - b;
  product = a * b;

  if (b == 0.0f) {
    return ErrorCode::kDivideByZero;
  }

  ratio = a / b;
  return ErrorCode::kNoError;
}