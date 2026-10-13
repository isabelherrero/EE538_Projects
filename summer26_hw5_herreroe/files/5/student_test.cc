#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_set>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------

namespace {

std::vector<std::vector<int>> BruteForceAllPermutations(
    std::vector<int> nums) {
  std::sort(nums.begin(), nums.end());

  std::vector<std::vector<int>> result;
  if (nums.empty()) {
    result.push_back({});
    return result;
  }

  do {
    result.push_back(nums);
  } while (std::next_permutation(nums.begin(), nums.end()));
  return result;
}

void ExpectPermutationsMatch(const std::vector<int>& nums) {
  std::vector<std::vector<int>> actual = permute_with_duplicates(nums);
  std::vector<std::vector<int>> expected = BruteForceAllPermutations(nums);

  std::sort(actual.begin(), actual.end());
  std::sort(expected.begin(), expected.end());

  EXPECT_EQ(actual, expected);
}

} 

TEST(PermuteWithDuplicatesTest, ExampleFromSpec) {
  std::vector<int> nums = {1, 1, 2};
  std::vector<std::vector<int>> actual = permute_with_duplicates(nums);
  std::sort(actual.begin(), actual.end());

  std::vector<std::vector<int>> expected = {{1, 1, 2}, {1, 2, 1}, {2, 1, 1}};
  std::sort(expected.begin(), expected.end());

  EXPECT_EQ(actual, expected);
}

TEST(PermuteWithDuplicatesTest, EmptyInput) {
  std::vector<int> nums = {};
  std::vector<std::vector<int>> result = permute_with_duplicates(nums);
  ASSERT_EQ(result.size(), 1u);
  EXPECT_TRUE(result[0].empty());
}

TEST(PermuteWithDuplicatesTest, SingleElement) {
  std::vector<int> nums = {5};
  std::vector<std::vector<int>> expected = {{5}};
  EXPECT_EQ(permute_with_duplicates(nums), expected);
}

TEST(PermuteWithDuplicatesTest, TwoDistinctElements) {
  ExpectPermutationsMatch({1, 2});
}

TEST(PermuteWithDuplicatesTest, TwoIdenticalElements) {
  std::vector<int> nums = {4, 4};
  std::vector<std::vector<int>> expected = {{4, 4}};
  EXPECT_EQ(permute_with_duplicates(nums), expected);
}

TEST(PermuteWithDuplicatesTest, AllElementsIdentical) {
  std::vector<int> nums = {3, 3, 3, 3};
  std::vector<std::vector<int>> expected = {{3, 3, 3, 3}};
  EXPECT_EQ(permute_with_duplicates(nums), expected);
}

TEST(PermuteWithDuplicatesTest, ThreeDistinctElements) {
  ExpectPermutationsMatch({1, 2, 3});
}

TEST(PermuteWithDuplicatesTest, TwoDuplicatePairs) {
  ExpectPermutationsMatch({1, 1, 2, 2});
}

TEST(PermuteWithDuplicatesTest, TripleDuplicateWithSingles) {
  ExpectPermutationsMatch({1, 1, 1, 2, 3});
}

TEST(PermuteWithDuplicatesTest, NegativeNumbersWithDuplicates) {
  ExpectPermutationsMatch({-1, -1, 0, 2});
}

TEST(PermuteWithDuplicatesTest, LargerAllDistinctInput) {
  ExpectPermutationsMatch({1, 2, 3, 4, 5});
}

TEST(PermuteWithDuplicatesTest, UnsortedInput) {
  ExpectPermutationsMatch({3, 1, 2, 1});
}