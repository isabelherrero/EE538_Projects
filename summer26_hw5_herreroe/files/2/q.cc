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

int MaxEndingAtRecursive(const std::vector<int> &nums, int i) {
  if (i == 0) {
    return nums[0];
  }
  int prev = MaxEndingAtRecursive(nums, i - 1);
  return nums[i] + std::max(0, prev);
}

int MaxEndingAtMemo(const std::vector<int> &nums, int i,
                     std::vector<int> *memo) {
  if (i == 0) {
    return nums[0];
  }
  if ((*memo)[i] != INT_MIN) {
    return (*memo)[i];
  }
  int prev = MaxEndingAtMemo(nums, i - 1, memo);
  (*memo)[i] = nums[i] + std::max(0, prev);
  return (*memo)[i];
}

}

int maxSubarraySumRecursive(const std::vector<int> &nums) {
  if (nums.empty()) {
    return 0;
  }

  int best = INT_MIN;
  for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
    best = std::max(best, MaxEndingAtRecursive(nums, i));
  }
  return best;
}

int maxSubarraySumMemoization(const std::vector<int> &nums) {
  if (nums.empty()) {
    return 0;
  }

  std::vector<int> memo(nums.size(), INT_MIN);
  int best = INT_MIN;
  for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
    best = std::max(best, MaxEndingAtMemo(nums, i, &memo));
  }
  return best;
}

int maxSubarraySumTabulation(const std::vector<int> &nums) {
  if (nums.empty()) {
    return 0;
  }

  std::vector<int> dp(nums.size());
  dp[0] = nums[0];
  int best = dp[0];

  for (int i = 1; i < static_cast<int>(nums.size()); ++i) {
    dp[i] = nums[i] + std::max(0, dp[i - 1]);
    best = std::max(best, dp[i]);
  }
  return best;
}