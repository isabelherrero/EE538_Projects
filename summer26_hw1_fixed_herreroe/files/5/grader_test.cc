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
TEST(ClimbStairs, Test1) {
  EXPECT_EQ(ClimbStairs(-1), -1);
  EXPECT_EQ(ClimbStairs(0), 0);
  EXPECT_EQ(ClimbStairs(1), 1);
}

TEST(ClimbStairs, Test2) {
  std::vector<int> expected_vector{0, 1, 2, 4, 7, 13, 24, 44, 81};
  for (int i = 0; i < expected_vector.size(); ++i) {
    auto output = ClimbStairs(i);
    std::cout << "input: " << i << ", output: " << output << std::endl;
    int expected = expected_vector[i];
    EXPECT_EQ(output, expected);
  }
}
//-----------------------------------------------------------------------------