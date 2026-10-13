#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------

TEST(ReverseTest, HandlesEmptyVector) {
  std::vector<int> input = {};
  std::vector<int> expected = {};
  EXPECT_EQ(Reverse(input), expected);
}

TEST(ReverseTest, HandlesSingleElement) {
  std::vector<int> input = {5};
  std::vector<int> expected = {5};
  EXPECT_EQ(Reverse(input), expected);
}

TEST(ReverseTest, HandlesMultipleElements) {
  std::vector<int> input = {1, 2, 3};
  std::vector<int> expected = {3, 2, 1};
  EXPECT_EQ(Reverse(input), expected);
}

TEST(PlusOneTest, HandlesSimpleIncrement) {
  std::vector<int> input = {1, 2, 3};
  std::vector<int> expected = {1, 2, 4};
  EXPECT_EQ(PlusOne(input), expected);
}

TEST(PlusOneTest, HandlesCarry) {
  std::vector<int> input = {1, 9};
  std::vector<int> expected = {2, 0};
  EXPECT_EQ(PlusOne(input), expected);
}

TEST(PlusOneTest, HandlesAllNines) {
  std::vector<int> input = {9, 9, 9};
  std::vector<int> expected = {1, 0, 0, 0};
  EXPECT_EQ(PlusOne(input), expected);
}

TEST(PlusOneTest, HandlesInvalidInput) {
  std::vector<int> input = {12};
  std::vector<int> expected = {-1};
  EXPECT_EQ(PlusOne(input), expected);
}

TEST(PlusOneTest, HandlesZero) {
  std::vector<int> input = {0};
  std::vector<int> expected = {1};
  EXPECT_EQ(PlusOne(input), expected);
}

TEST(PlusOneTest, HandlesEmptyVector) {
  std::vector<int> input = {};
  std::vector<int> expected = {};
  EXPECT_EQ(PlusOne(input), expected);
}

TEST(PlusOneTest, HandlesNegativeInvalidInput) {
  std::vector<int> input = {-1};
  std::vector<int> expected = {-1};
  EXPECT_EQ(PlusOne(input), expected);
}

TEST(PlusOneTest, HandlesMixedInvalidInput) {
  std::vector<int> input = {1, -3, 4};
  std::vector<int> expected = {-1};
  EXPECT_EQ(PlusOne(input), expected);
}

TEST(PlusOneTest, HandlesCarryThroughMiddle) {
  std::vector<int> input = {1, 9, 9};
  std::vector<int> expected = {2, 0, 0};
  EXPECT_EQ(PlusOne(input), expected);
}