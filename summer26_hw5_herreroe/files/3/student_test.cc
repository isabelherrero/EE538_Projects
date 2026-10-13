#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------

namespace {

bool IsValidLine(const std::vector<int> &line,
                  const std::vector<std::set<int>> &incompatible_students) {
  for (size_t i = 0; i + 1 < line.size(); ++i) {
    for (const std::set<int> &group : incompatible_students) {
      if (group.count(line[i]) > 0 && group.count(line[i + 1]) > 0) {
        return false;
      }
    }
  }
  return true;
}

int CountValidPermutationsBruteForce(
    std::vector<int> all_students,
    const std::vector<std::set<int>> &incompatible_students) {
  if (all_students.empty()) {
    return 1;
  }
  std::sort(all_students.begin(), all_students.end());
  int count = 0;
  do {
    if (IsValidLine(all_students, incompatible_students)) {
      ++count;
    }
  } while (std::next_permutation(all_students.begin(), all_students.end()));
  return count;
}

void ExpectAllValidAndComplete(
    std::vector<int> all_students,
    std::vector<std::set<int>> incompatible_students) {
  std::vector<int> students_arg = all_students;
  std::vector<std::set<int>> incompatible_arg = incompatible_students;
  std::vector<std::vector<int>> results =
      PutInLine(students_arg, incompatible_arg);

  std::vector<int> sorted_students = all_students;
  std::sort(sorted_students.begin(), sorted_students.end());

  for (const std::vector<int> &line : results) {
    EXPECT_EQ(line.size(), all_students.size());
    std::vector<int> sorted_line = line;
    std::sort(sorted_line.begin(), sorted_line.end());
    EXPECT_EQ(sorted_line, sorted_students);
    EXPECT_TRUE(IsValidLine(line, incompatible_students));
  }

  std::vector<std::vector<int>> sorted_results = results;
  std::sort(sorted_results.begin(), sorted_results.end());
  EXPECT_EQ(std::adjacent_find(sorted_results.begin(), sorted_results.end()),
            sorted_results.end())
      << "PutInLine returned a duplicate arrangement.";

  int expected_count =
      CountValidPermutationsBruteForce(all_students, incompatible_students);
  EXPECT_EQ(static_cast<int>(results.size()), expected_count);
}

} 

TEST(PutInLineTest, Example1_TwoStudentsNoIncompatibility) {
  std::vector<int> all_students = {0, 1};
  std::vector<std::set<int>> incompatible_students = {};
  std::vector<std::vector<int>> expected = {{0, 1}, {1, 0}};
  EXPECT_EQ(PutInLine(all_students, incompatible_students), expected);
}

TEST(PutInLineTest, Example2_ThreeStudentsNoIncompatibility) {
  std::vector<int> all_students = {0, 1, 2};
  std::vector<std::set<int>> incompatible_students = {};
  std::vector<std::vector<int>> expected = {{0, 1, 2}, {0, 2, 1}, {1, 0, 2},
                                             {1, 2, 0}, {2, 0, 1}, {2, 1, 0}};
  EXPECT_EQ(PutInLine(all_students, incompatible_students), expected);
}

TEST(PutInLineTest, Example3_ThreeStudentsOneIncompatiblePair) {
  std::vector<int> all_students = {0, 1, 2};
  std::vector<std::set<int>> incompatible_students = {{0, 1}};
  std::vector<std::vector<int>> expected = {{0, 2, 1}, {1, 2, 0}};
  EXPECT_EQ(PutInLine(all_students, incompatible_students), expected);
}

TEST(PutInLineTest, EmptyStudentList) {
  std::vector<int> all_students = {};
  std::vector<std::set<int>> incompatible_students = {};
  std::vector<std::vector<int>> results =
      PutInLine(all_students, incompatible_students);
  ASSERT_EQ(results.size(), 1u);
  EXPECT_TRUE(results[0].empty());
}

TEST(PutInLineTest, SingleStudent) {
  std::vector<int> all_students = {7};
  std::vector<std::set<int>> incompatible_students = {};
  std::vector<std::vector<int>> expected = {{7}};
  EXPECT_EQ(PutInLine(all_students, incompatible_students), expected);
}

TEST(PutInLineTest, TwoStudentsAlwaysIncompatible) {
  std::vector<int> all_students = {0, 1};
  std::vector<std::set<int>> incompatible_students = {{0, 1}};
  std::vector<std::vector<int>> results =
      PutInLine(all_students, incompatible_students);
  EXPECT_TRUE(results.empty());
}

TEST(PutInLineTest, ThreeMutuallyIncompatibleNoBuffer) {
  std::vector<int> all_students = {0, 1, 2};
  std::vector<std::set<int>> incompatible_students = {{0, 1, 2}};
  std::vector<std::vector<int>> results =
      PutInLine(all_students, incompatible_students);
  EXPECT_TRUE(results.empty());
}

TEST(PutInLineTest, ThreeMutuallyIncompatibleOneBufferStillImpossible) {
  std::vector<int> all_students = {0, 1, 2, 3};
  std::vector<std::set<int>> incompatible_students = {{0, 1, 2}};
  std::vector<std::vector<int>> results =
      PutInLine(all_students, incompatible_students);
  EXPECT_TRUE(results.empty());
}

TEST(PutInLineTest, ThreeMutuallyIncompatibleTwoBuffersPossible) {
  ExpectAllValidAndComplete({0, 1, 2, 3, 4}, {{0, 1, 2}});
}

TEST(PutInLineTest, TwoDisjointIncompatiblePairs) {
  ExpectAllValidAndComplete({0, 1, 2, 3}, {{0, 1}, {2, 3}});
}

TEST(PutInLineTest, FiveStudentsNoIncompatibility) {
  ExpectAllValidAndComplete({0, 1, 2, 3, 4}, {});
}

TEST(PutInLineTest, OneStudentIncompatibleWithAllOthers) {
  ExpectAllValidAndComplete({0, 1, 2, 3},
                             {{0, 1}, {0, 2}, {0, 3}});
}

TEST(PutInLineTest, OverlappingIncompatibilityGroups) {
  ExpectAllValidAndComplete({0, 1, 2, 3, 4}, {{0, 1}, {1, 2}, {2, 3}});
}