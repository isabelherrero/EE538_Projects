#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------

TEST(CountNumberOfSpacesTest, HandlesEmptyString) {
  EXPECT_EQ(CountNumberOfSpaces(""), 0);
}

TEST(CountNumberOfSpacesTest, HandlesNoSpaces) {
  EXPECT_EQ(CountNumberOfSpaces("hello"), 0);
}

TEST(CountNumberOfSpacesTest, HandlesSingleSpace) {
  EXPECT_EQ(CountNumberOfSpaces("hello world"), 1);
}

TEST(CountNumberOfSpacesTest, HandlesMultipleSpaces) {
  EXPECT_EQ(CountNumberOfSpaces("a b  c   d"), 6);
}

TEST(CountNumberOfSpacesTest, HandlesLeadingAndTrailingSpaces) {
  EXPECT_EQ(CountNumberOfSpaces("  hello world  "), 5);
}

TEST(CountNumberOfSpacesTest, HandlesOnlySpaces) {
  EXPECT_EQ(CountNumberOfSpaces("     "), 5);
}

TEST(CountNumberOfSpacesTest, SingleSpaceString) {
  EXPECT_EQ(CountNumberOfSpaces(" "), 1);
}

TEST(CountNumberOfSpacesTest, CountsOnlyActualSpaces) {
  EXPECT_EQ(CountNumberOfSpaces("a\tb c\n"), 1);
}