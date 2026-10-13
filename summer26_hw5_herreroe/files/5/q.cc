#include "q.h"

#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
// TODO:
// 1. Implement the the functions in q.h.
// 2. Write some unit tests for them in student_test.cc

//test

void permute_with_duplicates_recursive(const std::vector<int>& nums,
                                        std::vector<bool>& used,
                                        std::vector<int>& current,
                                        std::vector<std::vector<int>>& result) {
  if (current.size() == nums.size()) {
    result.push_back(current);
    return;
  }

  std::unordered_set<int> tried_at_this_level;

  for (size_t i = 0; i < nums.size(); ++i) {
    if (used[i]) {
      continue;
    }
    if (tried_at_this_level.count(nums[i]) > 0) {
      continue;
    }
    
    tried_at_this_level.insert(nums[i]);

    used[i] = true;
    current.push_back(nums[i]);
    permute_with_duplicates_recursive(nums, used, current, result);
    current.pop_back();
    used[i] = false;
  }
}

std::vector<std::vector<int>> permute_with_duplicates(std::vector<int> nums) {
  std::sort(nums.begin(), nums.end());

  std::vector<std::vector<int>> result;
  std::vector<int> current;
  std::vector<bool> used(nums.size(), false);

  permute_with_duplicates_recursive(nums, used, current, result);
  return result;
}