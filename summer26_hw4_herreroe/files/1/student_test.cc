#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------

TEST(ProductOfKHighestNumbersTest, ExampleFromSpec) {
  std::vector<int> input = {1, 10, 5, 4, 8, 9};
  std::vector<int> expected = {50, 200, 400, 720};
  EXPECT_EQ(ProductOfKHighestNumbers(input, 3), expected);
}

TEST(ProductOfKHighestNumbersTest, KLargerThanInputSize) {
  std::vector<int> input = {1, 10, 5, 4, 8, 9};
  std::vector<int> expected = {};
  EXPECT_EQ(ProductOfKHighestNumbers(input, 13), expected);
}

TEST(ProductOfKHighestNumbersTest, KIsZero) {
  std::vector<int> input = {1, 2, 3};
  std::vector<int> expected = {};
  EXPECT_EQ(ProductOfKHighestNumbers(input, 0), expected);
}

TEST(ProductOfKHighestNumbersTest, KIsNegative) {
  std::vector<int> input = {1, 2, 3};
  std::vector<int> expected = {};
  EXPECT_EQ(ProductOfKHighestNumbers(input, -2), expected);
}

TEST(ProductOfKHighestNumbersTest, EmptyInput) {
  std::vector<int> input = {};
  std::vector<int> expected = {};
  EXPECT_EQ(ProductOfKHighestNumbers(input, 1), expected);
  EXPECT_EQ(ProductOfKHighestNumbers(input, 0), expected);
}

TEST(ProductOfKHighestNumbersTest, KEqualsInputSize) {
  std::vector<int> input = {2, 3, 4};
  std::vector<int> expected = {24};  // 2 * 3 * 4
  EXPECT_EQ(ProductOfKHighestNumbers(input, 3), expected);
}

TEST(ProductOfKHighestNumbersTest, KEqualsOne) {
  std::vector<int> input = {3, 1, 4, 1, 5, 9, 2, 6};
  std::vector<int> expected = {3, 3, 4, 4, 5, 9, 9, 9};
  EXPECT_EQ(ProductOfKHighestNumbers(input, 1), expected);
}

TEST(ProductOfKHighestNumbersTest, SingleElementInput) {
  std::vector<int> input = {7};
  std::vector<int> expected = {7};
  EXPECT_EQ(ProductOfKHighestNumbers(input, 1), expected);
}

TEST(ProductOfKHighestNumbersTest, AllIdenticalValues) {
  std::vector<int> input = {5, 5, 5, 5, 5};
  std::vector<int> expected = {125, 125, 125};
  EXPECT_EQ(ProductOfKHighestNumbers(input, 3), expected);
}

TEST(ProductOfKHighestNumbersTest, NegativeNumbers) {
  std::vector<int> input = {-1, -5, -3, -2};
  std::vector<int> expected = {5, 3, 2};
  EXPECT_EQ(ProductOfKHighestNumbers(input, 2), expected);
}

TEST(ProductOfKHighestNumbersTest, MixedSignsWithZero) {
  std::vector<int> input = {0, -2, 3, -4, 5};
  std::vector<int> expected = {0, 0, 0, 15};
  EXPECT_EQ(ProductOfKHighestNumbers(input, 2), expected);
}

TEST(ProductOfKHighestNumbersTest, DescendingInput) {
  std::vector<int> input = {9, 8, 7, 6, 5};
  std::vector<int> expected = {504, 504, 504};
  EXPECT_EQ(ProductOfKHighestNumbers(input, 3), expected);
}

TEST(ProductOfKHighestNumbersTest, AscendingInput) {
  std::vector<int> input = {1, 2, 3, 4, 5};
  std::vector<int> expected = {6, 24, 60};
  EXPECT_EQ(ProductOfKHighestNumbers(input, 3), expected);
}

TEST(ProductOfKHighestNumbersTest, OutputSizeMatchesSpec) {
  std::vector<int> input = {4, 2, 9, 7, 1, 6, 8};
  int k = 4;
  auto result = ProductOfKHighestNumbers(input, k);
  EXPECT_EQ(result.size(), input.size() - k + 1);
}