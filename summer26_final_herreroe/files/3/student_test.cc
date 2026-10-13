#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------

TEST(FastestToTargetTest, ExampleOneYouAreCloser) {
  std::vector<std::vector<char>> grid = {
      {'y', '0', 'f'},
      {'0', '1', '0'},
      {'t', '0', '0'},
  };
  EXPECT_EQ(fastestToTarget(grid), 1);
}

TEST(FastestToTargetTest, ExampleTwoFriendIsBlockedOff) {
  std::vector<std::vector<char>> grid = {
      {'f', '0', '1', 't'},
      {'1', '1', '0', '0'},
      {'y', '0', '0', '0'},
  };
  EXPECT_EQ(fastestToTarget(grid), 1);
}

TEST(FastestToTargetTest, ExampleThreeBothBlockedOff) {
  std::vector<std::vector<char>> grid = {
      {'y', '0', 'f'},
      {'1', '1', '0'},
      {'t', '1', '0'},
  };
  EXPECT_EQ(fastestToTarget(grid), -1);
}

TEST(FastestToTargetTest, EmptyGridReturnsNegativeOne) {
  std::vector<std::vector<char>> grid = {};
  EXPECT_EQ(fastestToTarget(grid), -1);
}

TEST(FastestToTargetTest, MissingMarkersReturnsNegativeOne) {
  // No f anywhere on this grid so shouldn't happen per the problem's
  // constraints, but we shouldn't crash or read garbage if it does
  std::vector<std::vector<char>> grid = {
      {'y', '0', '0'},
      {'0', '0', '0'},
      {'0', '0', 't'},
  };
  EXPECT_EQ(fastestToTarget(grid), -1);
}

TEST(FastestToTargetTest, FriendReachesFirst) {
  std::vector<std::vector<char>> grid = {
      {'f', '0', 'y'},
      {'0', '1', '0'},
      {'t', '0', '0'},
  };
  EXPECT_EQ(fastestToTarget(grid), 2);
}

TEST(FastestToTargetTest, YouAreBlockedFriendIsNot) {
  std::vector<std::vector<char>> grid = {
      {'y', '0', '1', 't'},
      {'1', '1', '0', '0'},
      {'f', '0', '0', '0'},
  };
  EXPECT_EQ(fastestToTarget(grid), 2);
}

TEST(FastestToTargetTest, ExactTieBothArriveTogether) {
  // t sits dead center, y and f are mirrored the same distance away
  // on either side with nothing blocking either path
  std::vector<std::vector<char>> grid = {
      {'y', '0', 't', '0', 'f'},
  };
  EXPECT_EQ(fastestToTarget(grid), 3);
}

TEST(FastestToTargetTest, TargetAdjacentToBothStartsIsAlsoATie) {
  std::vector<std::vector<char>> grid = {
      {'y', 't', 'f'},
  };
  EXPECT_EQ(fastestToTarget(grid), 3);
}

TEST(FastestToTargetTest, WindingPathIsntFooledByStraightLineDistance) {
  std::vector<std::vector<char>> grid = {
      {'t', '1', '0', '0', '0'},
      {'0', '1', '0', '1', '0'},
      {'0', '1', '0', '1', '0'},
      {'0', '1', '0', '1', '0'},
      {'y', '0', '0', '1', 'f'},
  };
  EXPECT_EQ(fastestToTarget(grid), 1);
}

TEST(FastestToTargetTest, SingleRowGrid) {
  std::vector<std::vector<char>> grid = {{'y', '0', '0', '0', 't', '0', 'f'}};
  // y is 4 steps from t, f is 2 steps from t
  // Friend wins
  EXPECT_EQ(fastestToTarget(grid), 2);
}

TEST(FastestToTargetTest, SingleColumnGrid) {
  std::vector<std::vector<char>> grid = {{'y'}, {'0'}, {'t'}, {'0'}, {'f'}};
  // Both y and f are 2 steps from t
  // Tie
  EXPECT_EQ(fastestToTarget(grid), 3);
}

TEST(FastestToTargetTest, TargetImmediatelyAdjacentToOneStart) {
  std::vector<std::vector<char>> grid = {
      {'y', 't', '0', '0', 'f'},
  };
  // y is right next door (distance 1), f has to walk the whole row
  EXPECT_EQ(fastestToTarget(grid), 1);
}

TEST(FastestToTargetTest, LargerOpenGridSanityCheck) {
  // No walls at all
  // Double-checking plain BFS distance math on a bigger grid
  std::vector<std::vector<char>> grid = {
      {'y', '0', '0', '0', '0'},
      {'0', '0', '0', '0', '0'},
      {'0', '0', 't', '0', '0'},
      {'0', '0', '0', '0', '0'},
      {'0', '0', '0', '0', 'f'},
  };
  // y at (0,0) to t at (2,2): Manhattan distance 4
  // f at (4,4) to t at (2,2): Manhattan distance 4
  // Open grid, so BFS distance == Manhattan distance here so tie
  EXPECT_EQ(fastestToTarget(grid), 3);
}