#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------

using MaxSubarrayFn = int (*)(const std::vector<int> &);

class MaxSubarraySumTest : public ::testing::TestWithParam<MaxSubarrayFn> {};

TEST_P(MaxSubarraySumTest, ExampleFromSpec) {
  std::vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
  EXPECT_EQ(GetParam()(nums), 6);
}

TEST_P(MaxSubarraySumTest, EmptyArray) {
  std::vector<int> nums = {};
  EXPECT_EQ(GetParam()(nums), 0);
}

TEST_P(MaxSubarraySumTest, SinglePositiveElement) {
  std::vector<int> nums = {5};
  EXPECT_EQ(GetParam()(nums), 5);
}

TEST_P(MaxSubarraySumTest, SingleNegativeElement) {
  std::vector<int> nums = {-5};
  EXPECT_EQ(GetParam()(nums), -5);
}

TEST_P(MaxSubarraySumTest, SingleZeroElement) {
  std::vector<int> nums = {0};
  EXPECT_EQ(GetParam()(nums), 0);
}

TEST_P(MaxSubarraySumTest, AllNegative) {
  std::vector<int> nums = {-8, -3, -6, -2, -5, -4};
  EXPECT_EQ(GetParam()(nums), -2);
}

TEST_P(MaxSubarraySumTest, AllNegativeDecreasing) {
  std::vector<int> nums = {-1, -2, -3, -4, -5};
  EXPECT_EQ(GetParam()(nums), -1);
}

TEST_P(MaxSubarraySumTest, AllPositive) {
  std::vector<int> nums = {1, 2, 3, 4, 5};
  EXPECT_EQ(GetParam()(nums), 15);
}

TEST_P(MaxSubarraySumTest, AllZero) {
  std::vector<int> nums = {0, 0, 0, 0};
  EXPECT_EQ(GetParam()(nums), 0);
}

TEST_P(MaxSubarraySumTest, NegativesWithZero) {
  std::vector<int> nums = {-1, -2, 0, -3};
  EXPECT_EQ(GetParam()(nums), 0);
}

TEST_P(MaxSubarraySumTest, TwoElementsPositiveThenNegative) {
  std::vector<int> nums = {1, -1};
  EXPECT_EQ(GetParam()(nums), 1);
}

TEST_P(MaxSubarraySumTest, TwoElementsNegativeThenPositive) {
  std::vector<int> nums = {-1, 1};
  EXPECT_EQ(GetParam()(nums), 1);
}

TEST_P(MaxSubarraySumTest, TwoElementsBothNegative) {
  std::vector<int> nums = {-1, -2};
  EXPECT_EQ(GetParam()(nums), -1);
}

TEST_P(MaxSubarraySumTest, EntireArrayIsBest) {
  std::vector<int> nums = {2, -1, 2, -1, 3};
  EXPECT_EQ(GetParam()(nums), 5);
}

TEST_P(MaxSubarraySumTest, MiddleSubarrayIsBest) {
  std::vector<int> nums = {-5, 4, 6, -2, 100, -300, 5};
  EXPECT_EQ(GetParam()(nums), 108);
}

TEST_P(MaxSubarraySumTest, LargerArray) {
  std::vector<int> nums(1000, -1);
  nums[500] = 2000;
  EXPECT_EQ(GetParam()(nums), 2000);
}

INSTANTIATE_TEST_SUITE_P(AllImplementations, MaxSubarraySumTest,
                          ::testing::Values(&maxSubarraySumRecursive,
                                             &maxSubarraySumMemoization,
                                             &maxSubarraySumTabulation));