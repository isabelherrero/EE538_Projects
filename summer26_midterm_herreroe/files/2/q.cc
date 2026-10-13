#include "q.h"

#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>
// TODO:
// 1. Implement the the functions in q.h.
// 2. Write some unit tests for them in student_test.cc

float Calculate(int a, int b, Operation operation) {
    // Operation addition
    if (operation == Operation::kAdd) {
        return a + b;
    // Operation subtraction
    } else if (operation == Operation::kSubtract) {
        return a - b;
    // Operation multiplication
    } else if (operation == Operation::kMultiplication) {
        return a * b;
    // Operation division
    // Assumption: division by zero is not handled in this implementation because you can't divide by zero in real life that is undefined. If you want to handle division by zero, you can add a check for b == 0 and return an error code or throw an exception.
    // Float division is used to return a float result
    } else if (operation == Operation::kDivision) {
        return (float)(a) / b;
    // Operation bitwise AND
    } else if (operation == Operation::kBitwise_AND) {
        return a & b;
    // Operation bitwise OR
    } else if (operation == Operation::kBitwise_OR) {
        return a | b;
    // Operation bitwise XOR
    } else if (operation == Operation::kBitwise_XOR) {
        return a ^ b;
    // Operation shift left
    } else if (operation == Operation::kShift_left) {
        return a << b;
    // Operation shift right
    } else if (operation == Operation::kShift_right) {
        return a >> b;
    }
    // If the operation is not recognized, return -1 as an error code
    return -1;
}
