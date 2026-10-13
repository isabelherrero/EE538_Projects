#include <iostream>
#include <string>

#include "q.h"
#include "gtest/gtest.h"

//-----------------------------------------------------------------------------
// Write some test cases for each function.
//-----------------------------------------------------------------------------

TEST(IndexOfFirstSpace, EmptyString) {
  std::string test_string = "";
  std::cout << "test_string: " << test_string << std::endl;

  EXPECT_EQ(IndexOfFirstSpace(test_string), -1);
}

TEST(IndexOfFirstSpace, NoSpace) {
  std::string test_string = "ThisIsATest";
  std::cout << "test_string: " << test_string << std::endl;
  EXPECT_EQ(IndexOfFirstSpace(test_string), -1);
}

TEST(IndexOfFirstSpace, StringWithMultipleSpaces) {
  std::string test_string = "This is a test";
  std::cout << "test_string: " << test_string << std::endl;
  EXPECT_EQ(IndexOfFirstSpace(test_string), 4);
}
TEST(IndexOfFirstSpace, StringWithSingleSpace) {
  std::string test_string = "ThisIs aTest";
  std::cout << "test_string: " << test_string << std::endl;
  EXPECT_EQ(IndexOfFirstSpace(test_string), 6);
}

TEST(IndexOfFirstSpace, SpaceInTheBeginning) {
  std::string test_string = " This Is a Test";
  std::cout << "test_string: " << test_string << std::endl;
  EXPECT_EQ(IndexOfFirstSpace(test_string), 0);
}

TEST(IndexOfFirstSpace, SpaceInTheEnd) {
  std::string test_string = "ThisIsATest ";
  std::cout << "test_string: " << test_string << std::endl;
  EXPECT_EQ(IndexOfFirstSpace(test_string), 11);
}
//-----------------------------------------------------------------------------
TEST(SeparateFirstAndLastNames, Empty) {
  std::string full_name = "";
  std::string first_name;
  std::string last_name;

  std::cout << "full_name: " << full_name << std::endl;
  SeparateFirstAndLastNames(full_name, first_name, last_name);
  EXPECT_TRUE(first_name.empty());
  EXPECT_TRUE(last_name.empty());
}
TEST(SeparateFirstAndLastNames, NoSpace) {
  std::string full_name = "TommyTrojan";
  std::string first_name;
  std::string last_name;

  std::cout << "full_name: " << full_name << std::endl;
  SeparateFirstAndLastNames(full_name, first_name, last_name);
  EXPECT_EQ(first_name, "TommyTrojan");
  EXPECT_TRUE(last_name.empty());
}

TEST(SeparateFirstAndLastNames, SingleSpace) {
  std::string full_name = "Tommy Trojan";
  std::string first_name;
  std::string last_name;

  std::cout << "full_name: " << full_name << std::endl;
  SeparateFirstAndLastNames(full_name, first_name, last_name);
  EXPECT_EQ(first_name, "Tommy");
  EXPECT_EQ(last_name, "Trojan");
}

TEST(SeparateFirstAndLastNames, MultipleSpaces) {
  std::string full_name = "Tommy Trojan Second";
  std::string first_name;
  std::string last_name;

  std::cout << "full_name: " << full_name << std::endl;

  SeparateFirstAndLastNames(full_name, first_name, last_name);
  EXPECT_EQ(first_name, "Tommy");
  EXPECT_EQ(last_name, "Trojan Second");
}
//-----------------------------------------------------------------------------
TEST(SplitStringTest, NormalCase) {
  std::vector<std::string> expected = {"apple", "banana", "orange"};
  ASSERT_EQ(SplitString("apple banana orange"), expected);
}

TEST(SplitStringTest, ConsecutiveSpaces) {
  std::vector<std::string> expected = {"apple", "banana", "orange"};
  ASSERT_EQ(SplitString("apple  banana  orange"), expected);
}

TEST(SplitStringTest, LeadingSpaces) {
  std::vector<std::string> expected = {"apple", "banana"};
  ASSERT_EQ(SplitString(" apple banana"), expected);
}

TEST(SplitStringTest, TrailingSpaces) {
  std::vector<std::string> expected = {"apple", "banana"};
  ASSERT_EQ(SplitString("apple banana "), expected);
}

TEST(SplitStringTest, EmptyString) {
  std::vector<std::string> expected = {};
  ASSERT_EQ(SplitString(""), expected);
}
//-----------------------------------------------------------------------------
TEST(CalculateFrequencyTest, NormalCase) {
  std::map<std::string, int> expected = {
      {"apple", 3}, {"banana", 2}, {"orange", 1}};
  ASSERT_EQ(CalculateFrequency("apple banana orange apple apple banana"),
            expected);
}

TEST(CalculateFrequencyTest, ConsecutiveSpaces) {
  std::map<std::string, int> expected = {
      {"apple", 2}, {"banana", 1}, {"orange", 1}};
  ASSERT_EQ(CalculateFrequency("apple  banana apple  orange"), expected);
}

TEST(CalculateFrequencyTest, LeadingSpaces) {
  std::map<std::string, int> expected = {{"apple", 1}, {"banana", 1}};
  ASSERT_EQ(CalculateFrequency(" apple banana"), expected);
}

TEST(CalculateFrequencyTest, TrailingSpaces) {
  std::map<std::string, int> expected = {
      {"apple", 1},
      {"banana", 1},
  };
  ASSERT_EQ(CalculateFrequency("apple banana "), expected);
}

TEST(CalculateFrequencyTest, EmptyString) {
  std::map<std::string, int> expected = {};
  ASSERT_EQ(CalculateFrequency(""), expected);
}
