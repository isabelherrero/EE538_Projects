#include <iostream>
#include <string>
#include <algorithm>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------

namespace {

std::vector<std::vector<int>> SortedCopy(std::vector<std::vector<int>> v) {
  std::sort(v.begin(), v.end());
  return v;
}

void ExpectArrangementsEqual(std::vector<std::vector<int>> actual,
                              std::vector<std::vector<int>> expected) {
  EXPECT_EQ(SortedCopy(std::move(actual)), SortedCopy(std::move(expected)));
}

// True if no two neighbors in the row are from the same country
bool IsValidSeating(const std::vector<int> &row) {
  for (size_t i = 1; i < row.size(); ++i) {
    if (row[i] == row[i - 1]) return false;
  }
  return true;
}

std::vector<std::vector<int>> BruteForceValidArrangements(std::vector<int> students) {
  std::vector<std::vector<int>> result;
  std::sort(students.begin(), students.end());
  do {
    if (IsValidSeating(students)) {
      result.push_back(students);
    }
  } while (std::next_permutation(students.begin(), students.end()));
  return result;
}

}

TEST(MovieTheaterAssignmentTest, EmptyInputGivesOneEmptyArrangement) {
  // Nobody to seat -> the empty row is a valid arrangement
  std::vector<int> students = {};
  std::vector<std::vector<int>> expected = {{}};
  ExpectArrangementsEqual(MovieTheaterAssignment(students), expected);
}

TEST(MovieTheaterAssignmentTest, SingleStudentGivesOneArrangement) {
  std::vector<int> students = {5};
  std::vector<std::vector<int>> expected = {{5}};
  ExpectArrangementsEqual(MovieTheaterAssignment(students), expected);
}

TEST(MovieTheaterAssignmentTest, TwoStudentsSameCountryIsImpossible) {
  // Only one seat pair, both taken by the same country -> always adjacent
  std::vector<int> students = {1, 1};
  EXPECT_TRUE(MovieTheaterAssignment(students).empty());
}

TEST(MovieTheaterAssignmentTest, TwoStudentsDifferentCountries) {
  std::vector<int> students = {1, 2};
  std::vector<std::vector<int>> expected = {{1, 2}, {2, 1}};
  ExpectArrangementsEqual(MovieTheaterAssignment(students), expected);
}

TEST(MovieTheaterAssignmentTest, OneCountryOverwhelminglyDominant) {
  // 4 students from country 1 and only 1 from country 2
  // No way to separate all the 1's with just a single spacer
  std::vector<int> students = {1, 1, 1, 1, 2};
  EXPECT_TRUE(MovieTheaterAssignment(students).empty());
}

TEST(MovieTheaterAssignmentTest, ExactlyEnoughSpacersIsStillPossible) {
  // 3 students from country 1, 2 from country 2: 1 2 1 2 1 works out
  // exactly, so this should NOT be empty (it's right at the boundary of
  // our early feasibility check)
  std::vector<int> students = {1, 1, 1, 2, 2};
  auto result = MovieTheaterAssignment(students);
  EXPECT_FALSE(result.empty());
  for (const auto &row : result) {
    EXPECT_TRUE(IsValidSeating(row));
  }
}

TEST(MovieTheaterAssignmentTest, ExampleOneAllDifferentCountries) {
  std::vector<int> students = {1, 2, 3};
  std::vector<std::vector<int>> expected = {
      {1, 2, 3}, {1, 3, 2}, {2, 1, 3}, {2, 3, 1}, {3, 1, 2}, {3, 2, 1}};
  ExpectArrangementsEqual(MovieTheaterAssignment(students), expected);
}

TEST(MovieTheaterAssignmentTest, ExampleTwoOnePairPlusTwoSingles) {
  std::vector<int> students = {1, 1, 2, 3};
  std::vector<std::vector<int>> expected = {
      {1, 2, 1, 3}, {1, 3, 1, 2}, {2, 1, 3, 1},
      {3, 1, 2, 1}, {1, 2, 3, 1}, {1, 3, 2, 1}};
  ExpectArrangementsEqual(MovieTheaterAssignment(students), expected);
}

TEST(MovieTheaterAssignmentTest, ExampleThreeTwoPairs) {
  std::vector<int> students = {1, 1, 2, 2};
  std::vector<std::vector<int>> expected = {{1, 2, 1, 2}, {2, 1, 2, 1}};
  ExpectArrangementsEqual(MovieTheaterAssignment(students), expected);
}

TEST(MovieTheaterAssignmentTest, ExampleFourImpossible) {
  std::vector<int> students = {1, 1, 1, 2};
  EXPECT_TRUE(MovieTheaterAssignment(students).empty());
}

TEST(MovieTheaterAssignmentTest, MatchesBruteForceThreeCountriesWithRepeats) {
  std::vector<int> students = {1, 1, 2, 2, 3};
  ExpectArrangementsEqual(MovieTheaterAssignment(students),
                           BruteForceValidArrangements(students));
}

TEST(MovieTheaterAssignmentTest, MatchesBruteForceEqualTriples) {
  std::vector<int> students = {1, 1, 1, 2, 2, 2};
  ExpectArrangementsEqual(MovieTheaterAssignment(students),
                           BruteForceValidArrangements(students));
}

TEST(MovieTheaterAssignmentTest, MatchesBruteForceAllSameCountry) {
  // Nobody to alternate with, every student is country 7
  std::vector<int> students = {7, 7, 7, 7};
  ExpectArrangementsEqual(MovieTheaterAssignment(students),
                           BruteForceValidArrangements(students));
}

TEST(MovieTheaterAssignmentTest, EveryReturnedRowIsAPermutationOfTheInput) {
  std::vector<int> students = {1, 1, 2, 3, 3};
  auto result = MovieTheaterAssignment(students);
  ASSERT_FALSE(result.empty());

  std::vector<int> sortedInput = students;
  std::sort(sortedInput.begin(), sortedInput.end());

  for (const auto &row : result) {
    std::vector<int> sortedRow = row;
    std::sort(sortedRow.begin(), sortedRow.end());
    EXPECT_EQ(sortedRow, sortedInput);
    EXPECT_TRUE(IsValidSeating(row));
  }
}

TEST(MovieTheaterAssignmentTest, NoDuplicateArrangementsInOutput) {
  std::vector<int> students = {1, 1, 2, 2, 3};
  auto result = MovieTheaterAssignment(students);
  auto sorted = SortedCopy(result);
  EXPECT_EQ(std::adjacent_find(sorted.begin(), sorted.end()), sorted.end());
}