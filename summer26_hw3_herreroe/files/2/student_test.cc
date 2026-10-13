#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------

TEST(CheckValidExpressionTest, EmptyStringIsValid) {
  CPPLib lib;
  EXPECT_TRUE(lib.CheckValidExpression(""));
}

TEST(CheckValidExpressionTest, SingleTypeMatched) {
  CPPLib lib;
  EXPECT_TRUE(lib.CheckValidExpression("(a+b)"));
}

TEST(CheckValidExpressionTest, MultipleTypesMatchedInSequence) {
  CPPLib lib;
  EXPECT_TRUE(lib.CheckValidExpression("(a+b)[c*d]{5g+h}"));
}

TEST(CheckValidExpressionTest, NestedBracketsMatched) {
  CPPLib lib;
  EXPECT_TRUE(lib.CheckValidExpression("{2k+[5j]}"));
}

TEST(CheckValidExpressionTest, RepeatedOperatorsIgnored) {
  CPPLib lib;
  EXPECT_TRUE(lib.CheckValidExpression("{2k++[5--*j]}"));
}

TEST(CheckValidExpressionTest, MismatchedClosingType) {
  CPPLib lib;
  EXPECT_FALSE(lib.CheckValidExpression("(a+b]"));
}

TEST(CheckValidExpressionTest, WrongOrderOfClosing) {
  CPPLib lib;
  EXPECT_FALSE(lib.CheckValidExpression("(7h+[5c)+7]"));
}

TEST(CheckValidExpressionTest, UnclosedBracket) {
  CPPLib lib;
  EXPECT_FALSE(lib.CheckValidExpression("(a+b"));
}

TEST(CheckValidExpressionTest, ClosingWithoutOpening) {
  CPPLib lib;
  EXPECT_FALSE(lib.CheckValidExpression("a+b)"));
}

TEST(CheckValidExpressionTest, NoBracketsAtAll) {
  CPPLib lib;
  EXPECT_TRUE(lib.CheckValidExpression("a+b*c-d"));
}

TEST(CheckValidExpressionTest, SingleUnmatchedOpenBracket) {
  CPPLib lib;
  EXPECT_FALSE(lib.CheckValidExpression("("));
}

TEST(CheckValidExpressionTest, SingleUnmatchedCloseBracket) {
  CPPLib lib;
  EXPECT_FALSE(lib.CheckValidExpression(")"));
}

TEST(CheckValidExpressionTest, AllThreeTypesNestedTogether) {
  CPPLib lib;
  EXPECT_TRUE(lib.CheckValidExpression("({[]})"));
}

TEST(IsPalindromeTest, EmptyStringIsPalindrome) {
  CPPLib lib;
  EXPECT_TRUE(lib.IsPalindrome(""));
}

TEST(IsPalindromeTest, SingleCharacterIsPalindrome) {
  CPPLib lib;
  EXPECT_TRUE(lib.IsPalindrome("a"));
}

TEST(IsPalindromeTest, OddLengthPalindrome) {
  CPPLib lib;
  EXPECT_TRUE(lib.IsPalindrome("aba"));
}

TEST(IsPalindromeTest, EvenLengthPalindrome) {
  CPPLib lib;
  EXPECT_TRUE(lib.IsPalindrome("abba"));
}

TEST(IsPalindromeTest, NotAPalindrome) {
  CPPLib lib;
  EXPECT_FALSE(lib.IsPalindrome("abc"));
}

TEST(IsPalindromeTest, NotAPalindromeEvenLength) {
  CPPLib lib;
  EXPECT_FALSE(lib.IsPalindrome("abcd"));
}

TEST(IsPalindromeTest, CaseSensitiveMismatchIsIntentional) {
  CPPLib lib;
  EXPECT_FALSE(lib.IsPalindrome("Aa"));
}

TEST(IsPalindromeTest, TwoIdenticalCharactersIsPalindrome) {
  CPPLib lib;
  EXPECT_TRUE(lib.IsPalindrome("aa"));
}

TEST(OddCharTest, SingleCharacter) {
  CPPLib lib;
  EXPECT_EQ(lib.OddChar("a"), static_cast<int>('a'));
}

TEST(OddCharTest, OneOddAmongEvens) {
  CPPLib lib;
  EXPECT_EQ(lib.OddChar("aab"), static_cast<int>('b'));
}

TEST(OddCharTest, OddCharInMiddle) {
  CPPLib lib;
  EXPECT_EQ(lib.OddChar("xyxzz"), static_cast<int>('y'));
}

TEST(OddCharTest, CharacterAppearingThreeTimesIsStillOdd) {
  CPPLib lib;
  EXPECT_EQ(lib.OddChar("aabab"), static_cast<int>('a'));
}

TEST(OddCharTest, EmptyStringReturnsSentinel) {
  CPPLib lib;
  EXPECT_EQ(lib.OddChar(""), -1);
}