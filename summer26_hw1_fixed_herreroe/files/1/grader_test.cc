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
TEST(Reverse, Empty) {
  std::vector<int> in = {};
  std::cout << "in:" << std::endl;
  PrintCollection(in);
  auto out = Reverse(in);
  std::cout << "out:" << std::endl;
  PrintCollection(out);

  std::vector<int> expected = {};
  EXPECT_EQ(out, expected);
}

TEST(Reverse, Test1) {
  std::vector<int> in = {1, 2, 3};
  std::cout << "in:" << std::endl;
  PrintCollection(in);
  auto out = Reverse(in);
  std::cout << "out:" << std::endl;
  PrintCollection(out);

  std::vector<int> expected = {3, 2, 1};
  EXPECT_EQ(out, expected);
}

TEST(Reverse, Test2) {
  std::vector<int> in = {1, 2, 3, -7, 5, 2, 2};
  std::cout << "in:" << std::endl;
  PrintCollection(in);
  auto out = Reverse(in);
  std::cout << "out:" << std::endl;
  PrintCollection(out);

  std::vector<int> expected = {2, 2, 5, -7, 3, 2, 1};
  EXPECT_EQ(out, expected);
}
//-----------------------------------------------------------------------------
TEST(PlusOne, Empty) {
  std::vector<int> in = {};
  std::cout << "in:" << std::endl;
  PrintCollection(in);
  auto out = PlusOne(in);
  std::cout << "out:" << std::endl;
  PrintCollection(out);

  std::vector<int> expected = {};
  EXPECT_EQ(out, expected);
}

TEST(PlusOne, Zero) {
  std::vector<int> in = {0};
  std::cout << "in:" << std::endl;
  PrintCollection(in);

  auto out = PlusOne(in);
  std::cout << "out:" << std::endl;

  PrintCollection(out);

  std::vector<int> expected = {1};
  EXPECT_EQ(out, expected);
}

TEST(PlusOne, One) {
  std::vector<int> in = {1};
  std::cout << "in:" << std::endl;
  PrintCollection(in);
  auto out = PlusOne(in);
  std::cout << "out:" << std::endl;
  PrintCollection(out);

  std::vector<int> expected = {2};
  EXPECT_EQ(out, expected);
}

TEST(PlusOne, N29) {
  std::vector<int> in = {2, 9};
  std::cout << "in:" << std::endl;
  PrintCollection(in);
  auto out = PlusOne(in);
  std::cout << "out:" << std::endl;
  PrintCollection(out);

  std::vector<int> expected = {3, 0};
  EXPECT_EQ(out, expected);
}

TEST(PlusOne, N9) {
  std::vector<int> in = {9};
  std::cout << "in:" << std::endl;
  PrintCollection(in);
  auto out = PlusOne(in);
  std::cout << "out:" << std::endl;
  PrintCollection(out);

  std::vector<int> expected = {1, 0};
  EXPECT_EQ(out, expected);
}

TEST(PlusOne, N99) {
  std::vector<int> in = {9, 9};
  std::cout << "in:" << std::endl;
  PrintCollection(in);
  auto out = PlusOne(in);
  std::cout << "out:" << std::endl;
  PrintCollection(out);

  std::vector<int> expected = {1, 0, 0};
  EXPECT_EQ(out, expected);
}

TEST(PlusOne, N899) {
  std::vector<int> in = {8, 9, 9};
  std::cout << "in:" << std::endl;
  PrintCollection(in);
  auto out = PlusOne(in);
  std::cout << "out:" << std::endl;
  PrintCollection(out);

  std::vector<int> expected = {9, 0, 0};
  EXPECT_EQ(out, expected);
}