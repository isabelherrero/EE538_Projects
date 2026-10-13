#include "q.h"

#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <algorithm>
// TODO:
// 1. Implement the the functions in q.h.
// 2. Write some unit tests for them in student_test.cc

namespace {

void FillSeats(std::map<int, int> &remaining, int totalSeats, bool hasLast,
                int lastCountry, std::vector<int> &current,
                std::vector<std::vector<int>> &result) {
  if (static_cast<int>(current.size()) == totalSeats) {
    // Every seat is filled and we never violated the no two neighbors from the same country rule
    result.push_back(current);
    return;
  }

  for (auto &[country, count] : remaining) {
    if (count == 0) continue;                        // Nobody left from this country
    if (hasLast && country == lastCountry) continue;  // Can't sit next to their own kind

    // Seat one student from this country and recurse
    count--;
    current.push_back(country);
    FillSeats(remaining, totalSeats, /*hasLast=*/true, country, current, result);
    current.pop_back();  // Undo, so we can try the next option
    count++;
  }
}

}

std::vector<std::vector<int>>
MovieTheaterAssignment(const std::vector<int> &students) {
  std::vector<std::vector<int>> result;
  const int n = static_cast<int>(students.size());

  // No students
  // There's exactly one way to seat zero people, the empty row
  if (n == 0) {
    result.push_back({});
    return result;
  }

  // Count how many students come from each country
  std::map<int, int> remaining;
  for (int country : students) {
    remaining[country]++;
  }

  int mostCommonCount = 0;
  for (const auto &[country, count] : remaining) {
    mostCommonCount = std::max(mostCommonCount, count);
  }
  if (mostCommonCount > (n + 1) / 2) {
    return result;  // Stays empty
  }

  std::vector<int> current;
  current.reserve(n);
  FillSeats(remaining, n, /*hasLast=*/false, /*lastCountry=*/0, current, result);
  return result;
}