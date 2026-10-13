#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------

TEST(FibonacciTest, NegativeNumberReturnsOne) {
  EXPECT_EQ(Fibonacci(-1), 1);
  EXPECT_EQ(Fibonacci(-5), 1);
  EXPECT_EQ(Fibonacci(-100), 1);
}

TEST(FibonacciTest, ZeroReturnsOne) {
  EXPECT_EQ(Fibonacci(0), 1);
}

TEST(FibonacciTest, FirstTwoElementsAreOne) {
  EXPECT_EQ(Fibonacci(1), 1);
  EXPECT_EQ(Fibonacci(2), 1);
}

TEST(FibonacciTest, SmallValues) {
  EXPECT_EQ(Fibonacci(3), 2);
  EXPECT_EQ(Fibonacci(4), 3);
  EXPECT_EQ(Fibonacci(5), 5);
  EXPECT_EQ(Fibonacci(6), 8);
  EXPECT_EQ(Fibonacci(7), 13);
  EXPECT_EQ(Fibonacci(8), 21);
  EXPECT_EQ(Fibonacci(9), 34);
  EXPECT_EQ(Fibonacci(10), 55);
}

TEST(FibonacciTest, LargerValue) {
  EXPECT_EQ(Fibonacci(20), 6765);
  EXPECT_EQ(Fibonacci(30), 832040);
}

TEST(FibonacciTest, LargestValueThatFitsInInt) {
  EXPECT_EQ(Fibonacci(46), 1836311903);
}