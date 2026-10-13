#include <vector>
// q.h (Question 5)
// Permutations with duplicates — backtracking exercise.
//
// Public API
// Compute all unique permutations of the input array `nums` (which may
// contain duplicates). The result should contain each distinct permutation
// exactly once. Order of permutations is not important.
//
// Example:
//   Input: `nums = {1,1,2}`
//   Possible output: `{{1,1,2}, {1,2,1}, {2,1,1}}`
std::vector<std::vector<int>> permute_with_duplicates(std::vector<int> nums);

// Helpers to implement (backtracking)
// Implement a helper that runs a depth-first search (DFS) on the exhaustive
// search tree with backtracking. The helper should avoid generating duplicate
// permutations when input contains repeated values (Hint: sort
// the input and skip branches that would produce duplicates).
void permute_with_duplicates_recursive(const std::vector<int>& nums,
                                      std::vector<bool>& used,
                                      std::vector<int>& current,
                                      std::vector<std::vector<int>>& result);
