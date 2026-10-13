#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------

TEST(ClimbStairsTest, HandlesNegativeInput) {
  EXPECT_EQ(ClimbStairs(-1), -1);
}

TEST(ClimbStairsTest, HandlesZero) {
  EXPECT_EQ(ClimbStairs(0), 0);
}

TEST(ClimbStairsTest, HandlesOne) {
  EXPECT_EQ(ClimbStairs(1), 1);
}

TEST(ClimbStairsTest, HandlesTwo) {
  EXPECT_EQ(ClimbStairs(2), 2);
}

TEST(ClimbStairsTest, HandlesThree) {
  EXPECT_EQ(ClimbStairs(3), 4);
}

TEST(ClimbStairsTest, HandlesFour) {
  EXPECT_EQ(ClimbStairs(4), 7);
}

TEST(ClimbStairsTest, HandlesFive) {
  EXPECT_EQ(ClimbStairs(5), 13);
}

TEST(ClimbStairsTest, HandlesSix) {
  EXPECT_EQ(ClimbStairs(6), 24);
}

TEST(ClimbStairsTest, HandlesLargerNegativeInput) {
  EXPECT_EQ(ClimbStairs(-10), -1);
}