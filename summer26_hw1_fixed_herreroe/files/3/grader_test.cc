#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------s
template <class T>
void PrintCollection(T& input) {
  std::cout << "{ ";
  unsigned int count = 0;
  for (auto n : input) {
    count++;
    std::cout << n;
    if (count < input.size()) std::cout << ", ";
  }
  std::cout << " }" << std::endl;
}
//-----------------------------------------------------------------------------
// Write some test cases for each function.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
TEST(CountNumberOfSpaces, Empty) { EXPECT_EQ(CountNumberOfSpaces(""), 0); }

TEST(CountNumberOfSpaces, OneSpace) {
  EXPECT_EQ(CountNumberOfSpaces("this is"), 1);
}

TEST(CountNumberOfSpaces, TwoSpaces) {
  EXPECT_EQ(CountNumberOfSpaces("this is a"), 2);
}

TEST(CountNumberOfSpaces, ThreeSpaces) {
  EXPECT_EQ(CountNumberOfSpaces("this is a test"), 3);
}

TEST(CountNumberOfSpaces, MultipleSpaces) {
  EXPECT_EQ(CountNumberOfSpaces("this    is a"), 5);
}
