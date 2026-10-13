#include <vector>

// Given a collection of coin denominations and a total amount, return the
// minimum number of coins needed to make that amount. You may use an unlimited
// number of each coin.
//
// Return -1 when the amount cannot be made with the supplied coins.
// Return 0 when amount is 0.
// You may assume that every coin denomination is a positive integer.
//
// Example:
//   coins = {1, 2, 5}, amount = 11
//   result = 3, because 11 = 5 + 5 + 1

// Implement the solution using plain recursion without memoization.
int coinChangeRecursive(const std::vector<int>& coins, int amount);

// Implement the solution using recursion with memoization.
int coinChangeMemoization(const std::vector<int>& coins, int amount);

// Implement the solution using bottom-up tabulation. This implementation must
// not be recursive.
int coinChangeTabulation(const std::vector<int>& coins, int amount);
