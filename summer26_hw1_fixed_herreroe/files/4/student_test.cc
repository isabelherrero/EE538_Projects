#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------

TEST(Flatten3DVectorTest, HandlesEmptyInput) {
  std::vector<std::vector<std::vector<int>>> in = {};
  std::vector<int> expected = {};
  EXPECT_EQ(Flatten3DVector(in), expected);
}

TEST(Flatten3DVectorTest, HandlesOnlyEmptyInnerVectors) {
  std::vector<std::vector<std::vector<int>>> in = {
      {}, {{}}, {{}, {}}
  };
  std::vector<int> expected = {};
  EXPECT_EQ(Flatten3DVector(in), expected);
}

TEST(Flatten3DVectorTest, HandlesOneValue) {
  std::vector<std::vector<std::vector<int>>> in = {
      {{{42}}}
  };
  std::vector<int> expected = {42};
  EXPECT_EQ(Flatten3DVector(in), expected);
}

TEST(Flatten3DVectorTest, HandlesMixedShape) {
  std::vector<std::vector<std::vector<int>>> in = {
      {{1, 2}, {3}},
      {{4}, {}, {5, 6}},
      {{7, 8}}
  };
  std::vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8};
  EXPECT_EQ(Flatten3DVector(in), expected);
}

TEST(Flatten3DVectorTest, HandlesNegativeValues) {
  std::vector<std::vector<std::vector<int>>> in = {
      {{-1, -2}, {-3}},
      {{-4}, {}, {-5, -6}}
  };
  std::vector<int> expected = {-1, -2, -3, -4, -5, -6};
  EXPECT_EQ(Flatten3DVector(in), expected);
}

TEST(Flatten3DVectorTest, HandlesEmptyOuterBlockInMiddle) {
  std::vector<std::vector<std::vector<int>>> in = {
      {{1}},
      {},
      {{2, 3}}
  };
  std::vector<int> expected = {1, 2, 3};
  EXPECT_EQ(Flatten3DVector(in), expected);
}

TEST(Flatten3DVectorTest, HandlesSingleEmptyRow) {
  std::vector<std::vector<std::vector<int>>> in = {
      {{}}
  };
  std::vector<int> expected = {};
  EXPECT_EQ(Flatten3DVector(in), expected);
}