#include "q.h"

#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>
// TODO:
// 1. Implement the the functions in q.h.
// 2. Write some unit tests for them in student_test.cc

namespace {

// Recursively extends current using tasks[start..] to try to reach remaining
// Any complete combination found is appended to result
void FindCombinations(const std::vector<int> &tasks, int remaining, int start,
                       std::vector<int> &current,
                       std::vector<std::vector<int>> &result) {
  if (remaining == 0) {
    // Found a combination that sums exactly to the original limit
    result.push_back(current);
    return;
  }

  for (int i = start; i < static_cast<int>(tasks.size()); ++i) {
    // Tasks are sorted ascending, so once one task is too expensive,
    // every task after it is too expensive as well so stop this branch
    if (tasks[i] > remaining) {
      break;
    }

    current.push_back(tasks[i]);
    // Pass i so this same task can be reused again
    FindCombinations(tasks, remaining - tasks[i], i, current, result);
    current.pop_back();  // Backtrack undo the choice before trying the next task
  }
}

}

std::vector<std::vector<int>> findResource(std::vector<int> &tasks, int limit) {
  std::vector<std::vector<int>> result;

  // A non-positive resource limit has no valid combination
  // There's nothing to build up to (0) and negative budgets can never be reached
  // by adding positive costs
  if (limit <= 0) {
    return result;
  }

  std::vector<int> validTasks;
  std::unordered_set<int> seen;
  validTasks.reserve(tasks.size());
  for (int task : tasks) {
    if (task > 0 && seen.insert(task).second) {
      validTasks.push_back(task);
    }
  }

  if (validTasks.empty()) {
    return result;
  }

  // Sorting is required by FindCombinations's ordering logic
  std::sort(validTasks.begin(), validTasks.end());

  std::vector<int> current;
  FindCombinations(validTasks, limit, /*start=*/0, current, result);
  return result;
}