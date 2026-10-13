#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write some test cases for each function.
//-----------------------------------------------------------------------------
TEST(Calculate, SimpleTests) {
  int a = 10;
  int b = 9;

  EXPECT_EQ(Calculate(a, b, Operation::kAdd), 19);
  EXPECT_EQ(Calculate(a, b, Operation::kSubtract), 1);
  EXPECT_EQ(Calculate(a, b, Operation::kMultiplication), 90);
  EXPECT_NEAR(Calculate(a, b, Operation::kDivision), 1, 0.2);
  EXPECT_EQ(Calculate(a, b, Operation::kBitwise_AND), 0x8);
  EXPECT_EQ(Calculate(a, b, Operation::kBitwise_OR), 0xB);
  EXPECT_EQ(Calculate(a, b, Operation::kBitwise_XOR), 0x3);
  EXPECT_EQ(Calculate(a, b, Operation::kShift_left), 0x1400);
  EXPECT_EQ(Calculate(a, b, Operation::kShift_right), 0x0);
}
//-----------------------------------------------------------------------------
