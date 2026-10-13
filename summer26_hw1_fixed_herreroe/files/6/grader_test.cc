#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------s
TEST(CalculatorTest, TestNegativeInputs) {
  float a = -2;
  float b = -3;
  float sum, diff, product, ratio;
  ErrorCode error_code = Calculator(a, b, sum, diff, product, ratio);
  EXPECT_EQ(error_code, ErrorCode::kNoError);
  EXPECT_FLOAT_EQ(sum, -5);
  EXPECT_FLOAT_EQ(diff, 1);
  EXPECT_FLOAT_EQ(product, 6);
  EXPECT_FLOAT_EQ(ratio, 2 / 3.0);
}

TEST(CalculatorTest, TestPositiveAndNegativeInputs) {
  float a = 2;
  float b = -3;
  float sum, diff, product, ratio;
  ErrorCode error_code = Calculator(a, b, sum, diff, product, ratio);
  EXPECT_EQ(error_code, ErrorCode::kNoError);
  EXPECT_FLOAT_EQ(sum, -1);
  EXPECT_FLOAT_EQ(diff, 5);
  EXPECT_FLOAT_EQ(product, -6);
  EXPECT_FLOAT_EQ(ratio, 2 / (-3.0));
}

TEST(CalculatorTest, TestSmallInputs) {
  float a = 0.1;
  float b = 0.2;
  float sum, diff, product, ratio;
  ErrorCode error_code = Calculator(a, b, sum, diff, product, ratio);
  EXPECT_EQ(error_code, ErrorCode::kNoError);
  EXPECT_FLOAT_EQ(sum, 0.3);
  EXPECT_FLOAT_EQ(diff, -0.1);
  EXPECT_FLOAT_EQ(product, 0.02);
  EXPECT_FLOAT_EQ(ratio, 0.1 / 0.2);
}
