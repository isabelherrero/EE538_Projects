#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Writing student test is optional!
//-----------------------------------------------------------------------------

// Single character string
TEST(IndexOfFirstSpace, SingleChar) {
  std::string test_string = "a";
  std::cout << "test_string: " << test_string << std::endl;
  EXPECT_EQ(IndexOfFirstSpace(test_string), -1);
}

// Only spaces
TEST(IndexOfFirstSpace, OnlySpaces) {
  std::string test_string = "   ";
  std::cout << "test_string: " << test_string << std::endl;
  EXPECT_EQ(IndexOfFirstSpace(test_string), 0);
}

// Single character full name
TEST(SeparateFirstAndLastNames, SingleChar) {
  std::string full_name = "T";
  std::string first_name;
  std::string last_name;

  std::cout << "full_name: " << full_name << std::endl;
  SeparateFirstAndLastNames(full_name, first_name, last_name);
  EXPECT_EQ(first_name, "T");
  EXPECT_TRUE(last_name.empty());
}

// Single word
TEST(SplitStringTest, SingleWord) {
  std::vector<std::string> expected = {"apple"};
  ASSERT_EQ(SplitString("apple"), expected);
}

// Only spaces
TEST(SplitStringTest, OnlySpaces) {
  std::vector<std::string> expected = {};
  ASSERT_EQ(SplitString("   "), expected);
}

// Single word frequency
TEST(CalculateFrequencyTest, SingleWord) {
  std::map<std::string, int> expected = {{"apple", 1}};
  ASSERT_EQ(CalculateFrequency("apple"), expected);
}

// All same words
TEST(CalculateFrequencyTest, AllSameWords) {
  std::map<std::string, int> expected = {{"apple", 3}};
  ASSERT_EQ(CalculateFrequency("apple apple apple"), expected);
}