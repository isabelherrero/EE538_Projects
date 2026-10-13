#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------

namespace {

std::vector<std::vector<int>> Normalize(std::vector<std::vector<int>> combos) {
  for (auto &combo : combos) {
    std::sort(combo.begin(), combo.end());
  }
  std::sort(combos.begin(), combos.end());
  return combos;
}

void ExpectCombinationsEqual(std::vector<std::vector<int>> actual,
                              std::vector<std::vector<int>> expected) {
  EXPECT_EQ(Normalize(std::move(actual)), Normalize(std::move(expected)));
}

}

TEST(FindResourceTest, EmptyTasksListReturnsNoCombinations) {
  std::vector<int> tasks = {};
  EXPECT_TRUE(findResource(tasks, 10).empty());
}

TEST(FindResourceTest, ZeroLimitReturnsNoCombinations) {
  // A limit of 0 has no valid combination of positive cost tasks
  std::vector<int> tasks = {2, 3, 5};
  EXPECT_TRUE(findResource(tasks, 0).empty());
}

TEST(FindResourceTest, NegativeLimitReturnsNoCombinations) {
  std::vector<int> tasks = {2, 3, 5};
  EXPECT_TRUE(findResource(tasks, -7).empty());
}

TEST(FindResourceTest, EmptyTasksAndZeroLimitReturnsNoCombinations) {
  std::vector<int> tasks = {};
  EXPECT_TRUE(findResource(tasks, 0).empty());
}

TEST(FindResourceTest, AllTasksLargerThanLimitReturnsNoCombinations) {
  std::vector<int> tasks = {20, 30, 40};
  EXPECT_TRUE(findResource(tasks, 5).empty());
}

TEST(FindResourceTest, UnreachableLimitReturnsNoCombinations) {
  // 4 and 6 can only ever combine to even sums
  // 1 is unreachable
  std::vector<int> tasks = {4, 6};
  EXPECT_TRUE(findResource(tasks, 1).empty());
}

TEST(FindResourceTest, NonPositiveTaskCostsAreIgnored) {
  // 0 and negative costs aren't meaningful resource consumption
  // Should be filtered out rather than causing infinite looping behavior
  std::vector<int> tasks = {0, -2, 3};
  std::vector<std::vector<int>> expected = {{3, 3}};
  ExpectCombinationsEqual(findResource(tasks, 6), expected);
}

TEST(FindResourceTest, DuplicateTaskValuesAreTreatedAsOne) {
  std::vector<int> tasks = {3, 3, 5};
  std::vector<std::vector<int>> expected = {{3, 3}};
  ExpectCombinationsEqual(findResource(tasks, 6), expected);
}

TEST(FindResourceTest, SingleTaskExactMultipleOfLimit) {
  std::vector<int> tasks = {5};
  std::vector<std::vector<int>> expected = {{5, 5, 5}};
  ExpectCombinationsEqual(findResource(tasks, 15), expected);
}

TEST(FindResourceTest, SingleTaskWithNoSolution) {
  std::vector<int> tasks = {5};
  EXPECT_TRUE(findResource(tasks, 12).empty());
}

TEST(FindResourceTest, SingleTaskEqualsLimitExactlyOnce) {
  std::vector<int> tasks = {7, 3};
  std::vector<std::vector<int>> expected = {{7}};
  ExpectCombinationsEqual(findResource(tasks, 7), expected);
}

TEST(FindResourceTest, ThreeTaskTypesMultipleCombinations) {
  // 1*a + 2*b + 3*c == 4:
  // [1,1,1,1], [1,1,2], [2,2], [1,3]
  std::vector<int> tasks = {1, 2, 3};
  std::vector<std::vector<int>> expected = {
      {1, 1, 1, 1}, {1, 1, 2}, {2, 2}, {1, 3}};
  ExpectCombinationsEqual(findResource(tasks, 4), expected);
}

TEST(FindResourceTest, HeaderExampleOne) {
  std::vector<int> tasks = {3, 4, 7};
  std::vector<std::vector<int>> expected = {
      {3, 3, 4, 4}, {3, 4, 7}, {7, 7}};
  ExpectCombinationsEqual(findResource(tasks, 14), expected);
}

TEST(FindResourceTest, HeaderExampleTwo) {
  std::vector<int> tasks = {2, 5, 9};
  std::vector<std::vector<int>> expected = {
      {2, 2, 2, 2, 2, 2, 2, 2, 2}, {2, 2, 2, 2, 5, 5}, {2, 2, 5, 9}, {9, 9}};
  ExpectCombinationsEqual(findResource(tasks, 18), expected);
}

TEST(FindResourceTest, InputTasksVectorIsNotMutated) {
  // findResource takes tasks by non-const reference 
  // Makes sure it doesn't reorder or otherwise mutate the caller's vector.
  std::vector<int> tasks = {7, 3, 4};
  std::vector<int> originalOrder = tasks;
  findResource(tasks, 14);
  EXPECT_EQ(tasks, originalOrder);
}