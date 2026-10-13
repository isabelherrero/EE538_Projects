#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------

TEST(IsPrimeTest, NegativeNumbers) {
  EXPECT_FALSE(IsPrime(-5));
}

TEST(IsPrimeTest, ZeroAndOne) {
  EXPECT_FALSE(IsPrime(0));
  EXPECT_FALSE(IsPrime(1));
}

TEST(IsPrimeTest, SmallPrimes) {
  EXPECT_TRUE(IsPrime(2));
  EXPECT_TRUE(IsPrime(3));
  EXPECT_TRUE(IsPrime(5));
  EXPECT_TRUE(IsPrime(7));
}

TEST(IsPrimeTest, CompositeNumbers) {
  EXPECT_FALSE(IsPrime(4));
  EXPECT_FALSE(IsPrime(6));
  EXPECT_FALSE(IsPrime(9));
  EXPECT_FALSE(IsPrime(15));
}

TEST(IsPrimeTest, LargerPrime) {
  EXPECT_TRUE(IsPrime(97));
}

TEST(IsPrimeTest, SquareComposite) {
  EXPECT_FALSE(IsPrime(49));
}

TEST(IsPrimeTest, EvenComposite) {
  EXPECT_FALSE(IsPrime(100));
}

TEST(IsPrimeTest, AnotherPrime) {
  EXPECT_TRUE(IsPrime(101));
}