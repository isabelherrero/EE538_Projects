#include <iostream>
#include <string>
#include <climits>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------

using CoinChangeFn = int (*)(const std::vector<int>&, int);

class CoinChangeTest : public ::testing::TestWithParam<CoinChangeFn> {};

TEST_P(CoinChangeTest, ExampleFromSpec) {
  std::vector<int> coins = {1, 2, 5};
  EXPECT_EQ(GetParam()(coins, 11), 3);
}

TEST_P(CoinChangeTest, AmountZero) {
  std::vector<int> coins = {1, 2, 5};
  EXPECT_EQ(GetParam()(coins, 0), 0);
}

TEST_P(CoinChangeTest, AmountZeroEmptyCoins) {
  std::vector<int> coins = {};
  EXPECT_EQ(GetParam()(coins, 0), 0);
}

TEST_P(CoinChangeTest, EmptyCoinsPositiveAmount) {
  std::vector<int> coins = {};
  EXPECT_EQ(GetParam()(coins, 5), -1);
}

TEST_P(CoinChangeTest, NegativeAmount) {
  std::vector<int> coins = {1, 2, 5};
  EXPECT_EQ(GetParam()(coins, -5), -1);
}

TEST_P(CoinChangeTest, AmountUnreachable) {
  std::vector<int> coins = {3, 7};
  EXPECT_EQ(GetParam()(coins, 5), -1);
}

TEST_P(CoinChangeTest, SingleCoinDivides) {
  std::vector<int> coins = {5};
  EXPECT_EQ(GetParam()(coins, 15), 3);
}

TEST_P(CoinChangeTest, SingleCoinDoesNotDivide) {
  std::vector<int> coins = {5};
  EXPECT_EQ(GetParam()(coins, 7), -1);
}

TEST_P(CoinChangeTest, CoinExactlyEqualsAmount) {
  std::vector<int> coins = {7};
  EXPECT_EQ(GetParam()(coins, 7), 1);
}

TEST_P(CoinChangeTest, OnlyCoinLargerThanAmount) {
  std::vector<int> coins = {10};
  EXPECT_EQ(GetParam()(coins, 5), -1);
}

TEST_P(CoinChangeTest, DenominationOneAlwaysWorks) {
  std::vector<int> coins = {1};
  EXPECT_EQ(GetParam()(coins, 5), 5);
}

TEST_P(CoinChangeTest, DuplicateDenominations) {
  std::vector<int> coins = {1, 1, 2};
  EXPECT_EQ(GetParam()(coins, 3), 2);  // 1 + 2
}

TEST_P(CoinChangeTest, GreedyWouldFailButDPFindsOptimum) {
  std::vector<int> coins = {1, 3, 4};
  EXPECT_EQ(GetParam()(coins, 6), 2);
}

INSTANTIATE_TEST_SUITE_P(AllImplementations, CoinChangeTest,
                          ::testing::Values(&coinChangeRecursive,
                                             &coinChangeMemoization,
                                             &coinChangeTabulation));

TEST(CoinChangeLargerAmountTest, USCoinsCanonicalSystem) {
  std::vector<int> coins = {1, 5, 10, 25};
  EXPECT_EQ(coinChangeMemoization(coins, 63), 6);
  EXPECT_EQ(coinChangeTabulation(coins, 63), 6);
}

TEST(CoinChangeLargerAmountTest, MemoizationAndTabulationAgree) {
  std::vector<int> coins = {1, 3, 4, 9, 11};
  for (int amount = 0; amount <= 200; ++amount) {
    EXPECT_EQ(coinChangeMemoization(coins, amount),
              coinChangeTabulation(coins, amount))
        << "Mismatch at amount = " << amount;
  }
}

TEST(CoinChangeLargerAmountTest, LargeUnreachableAmount) {
  std::vector<int> coins = {2, 4, 6};
  EXPECT_EQ(coinChangeMemoization(coins, 101), -1);
  EXPECT_EQ(coinChangeTabulation(coins, 101), -1);
}