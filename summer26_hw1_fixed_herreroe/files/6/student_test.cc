#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------

TEST(CalculatorTest, NormalCase) {
  float sum, diff, product, ratio;

  ErrorCode result =
      Calculator(10.0f, 2.0f, sum, diff, product, ratio);

  EXPECT_EQ(result, ErrorCode::kNoError);
  EXPECT_FLOAT_EQ(sum, 12.0f);
  EXPECT_FLOAT_EQ(diff, 8.0f);
  EXPECT_FLOAT_EQ(product, 20.0f);
  EXPECT_FLOAT_EQ(ratio, 5.0f);
}

TEST(CalculatorTest, NegativeNumbers) {
  float sum, diff, product, ratio;

  ErrorCode result =
      Calculator(-6.0f, 3.0f, sum, diff, product, ratio);

  EXPECT_EQ(result, ErrorCode::kNoError);
  EXPECT_FLOAT_EQ(sum, -3.0f);
  EXPECT_FLOAT_EQ(diff, -9.0f);
  EXPECT_FLOAT_EQ(product, -18.0f);
  EXPECT_FLOAT_EQ(ratio, -2.0f);
}

TEST(CalculatorTest, DivideByZero) {
  float sum, diff, product, ratio = 0.0f;

  ErrorCode result =
      Calculator(5.0f, 0.0f, sum, diff, product, ratio);

  EXPECT_EQ(result, ErrorCode::kDivideByZero);
  EXPECT_FLOAT_EQ(sum, 5.0f);
  EXPECT_FLOAT_EQ(diff, 5.0f);
  EXPECT_FLOAT_EQ(product, 0.0f);
}

TEST(CalculatorTest, ZeroNumerator) {
  float sum, diff, product, ratio;

  ErrorCode result = Calculator(0.0f, 5.0f, sum, diff, product, ratio);

  EXPECT_EQ(result, ErrorCode::kNoError);
  EXPECT_FLOAT_EQ(sum, 5.0f);
  EXPECT_FLOAT_EQ(diff, -5.0f);
  EXPECT_FLOAT_EQ(product, 0.0f);
  EXPECT_FLOAT_EQ(ratio, 0.0f);
}

TEST(CalculatorTest, NegativeDenominator) {
  float sum, diff, product, ratio;

  ErrorCode result = Calculator(6.0f, -3.0f, sum, diff, product, ratio);

  EXPECT_EQ(result, ErrorCode::kNoError);
  EXPECT_FLOAT_EQ(sum, 3.0f);
  EXPECT_FLOAT_EQ(diff, 9.0f);
  EXPECT_FLOAT_EQ(product, -18.0f);
  EXPECT_FLOAT_EQ(ratio, -2.0f);
}

TEST(CalculatorTest, FractionalDivision) {
  float sum, diff, product, ratio;

  ErrorCode result = Calculator(1.0f, 2.0f, sum, diff, product, ratio);

  EXPECT_EQ(result, ErrorCode::kNoError);
  EXPECT_FLOAT_EQ(sum, 3.0f);
  EXPECT_FLOAT_EQ(diff, -1.0f);
  EXPECT_FLOAT_EQ(product, 2.0f);
  EXPECT_FLOAT_EQ(ratio, 0.5f);
}

TEST(CalculatorTest, BothZero) {
  float sum, diff, product, ratio;

  ErrorCode result = Calculator(0.0f, 0.0f, sum, diff, product, ratio);

  EXPECT_EQ(result, ErrorCode::kDivideByZero);
  EXPECT_FLOAT_EQ(sum, 0.0f);
  EXPECT_FLOAT_EQ(diff, 0.0f);
  EXPECT_FLOAT_EQ(product, 0.0f);
}