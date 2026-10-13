#include "q.h"

#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <climits>
// TODO:
// 1. Implement the the functions in q.h.
// 2. Write some unit tests for them in student_test.cc

namespace {

int CoinChangeMemoHelper(const std::vector<int>& coins, int amount,
                          std::vector<int>* memo) {
  if (amount == 0) {
    return 0;
  }
  if (amount < 0) {
    return -1;
  }
  if ((*memo)[amount] != -2) {
    return (*memo)[amount];
  }

  int best = INT_MAX;
  for (int coin : coins) {
    if (coin <= 0) {
      continue;
    }
    int sub = CoinChangeMemoHelper(coins, amount - coin, memo);
    if (sub >= 0 && sub + 1 < best) {
      best = sub + 1;
    }
  }

  (*memo)[amount] = (best == INT_MAX) ? -1 : best;
  return (*memo)[amount];
}

} 

int coinChangeRecursive(const std::vector<int>& coins, int amount) {
  if (amount == 0) {
    return 0;
  }
  if (amount < 0) {
    return -1;
  }

  int best = INT_MAX;
  for (int coin : coins) {
    if (coin <= 0) {
      continue;
    }
    int sub = coinChangeRecursive(coins, amount - coin);
    if (sub >= 0 && sub + 1 < best) {
      best = sub + 1;
    }
  }

  return (best == INT_MAX) ? -1 : best;
}

int coinChangeMemoization(const std::vector<int>& coins, int amount) {
  if (amount < 0) {
    return -1;
  }

  std::vector<int> memo(amount + 1, -2);
  return CoinChangeMemoHelper(coins, amount, &memo);
}

int coinChangeTabulation(const std::vector<int>& coins, int amount) {
  if (amount < 0) {
    return -1;
  }
  if (amount == 0) {
    return 0;
  }

  const int kUnreachable = amount + 1;
  std::vector<int> dp(amount + 1, kUnreachable);
  dp[0] = 0;

  for (int a = 1; a <= amount; ++a) {
    for (int coin : coins) {
      if (coin <= 0 || coin > a) {
        continue;
      }
      if (dp[a - coin] != kUnreachable) {
        dp[a] = std::min(dp[a], dp[a - coin] + 1);
      }
    }
  }

  return (dp[amount] == kUnreachable) ? -1 : dp[amount];
}