#include "q.h"

#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>
// TODO:
// 1. Implement the the functions in q.h.
// 2. Write some unit tests for them in student_test.cc

//test

namespace {

bool AreIncompatible(
    int a, int b,
    const std::vector<std::set<int>> &incompatible_students) {
  for (const std::set<int> &group : incompatible_students) {
    if (group.count(a) > 0 && group.count(b) > 0) {
      return true;
    }
  }
  return false;
}

bool Contains(const std::vector<int> &line, int student) {
  return std::find(line.begin(), line.end(), student) != line.end();
}

}

void PutInLineHelper(std::vector<int> &all_students,
                      std::vector<std::set<int>> &incompatible_students,
                      std::vector<int> &cur_line,
                      std::vector<std::vector<int>> &results) {
  if (cur_line.empty()) {
    std::sort(all_students.begin(), all_students.end());
  }

  if (cur_line.size() == all_students.size()) {
    results.push_back(cur_line);
    return;
  }

  for (int student : all_students) {
    if (Contains(cur_line, student)) {
      continue;
    }

    if (!cur_line.empty() &&
        AreIncompatible(cur_line.back(), student, incompatible_students)) {
      continue;
    }

    cur_line.push_back(student);
    PutInLineHelper(all_students, incompatible_students, cur_line, results);
    cur_line.pop_back();
  }
}

std::vector<std::vector<int>> PutInLine(
    std::vector<int> &all_students,
    std::vector<std::set<int>> &incompatible_students) {
  std::vector<std::vector<int>> results;
  std::vector<int> cur_line;
  std::vector<int> sorted_students = all_students;
  std::sort(sorted_students.begin(), sorted_students.end());

  PutInLineHelper(sorted_students, incompatible_students, cur_line, results);
  return results;
}