#include <iostream>
#include <list>
#include <string>
#include <vector>

// TODO:
// 1. Implement the following functions in q.cc.
// 2. Write some unit tests for them in student_test.cc

//-----------------------------------------------------------------------------
// We defined the following enum class:
enum class ErrorCode { kNoError, kDivideByZero };

// Given two float values a, b, return their sum, difference, product, and ratio
// (i.e. a/b). User C++ references to return multiple values. The functions
// return value should be of   type ErrorCode. Use this as the signature of your
// function.
// For your unit tests use EXPECT_FLOAT_EQ instead of EXPECT_EQ.
ErrorCode Calculator(float a, float b, float &sum, float &diff, float &product,
                     float &ratio);
//-----------------------------------------------------------------------------
