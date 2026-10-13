#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------

TEST(CanBecomeTest, HandlesExampleTrue) {
  EXPECT_TRUE(CanBecome("abcde", "cdeab"));
}

TEST(CanBecomeTest, HandlesExampleFalse) {
  EXPECT_FALSE(CanBecome("abcde", "abced"));
}

TEST(CanBecomeTest, HandlesEmptyStrings) {
  EXPECT_TRUE(CanBecome("", ""));
}

TEST(CanBecomeTest, HandlesDifferentLengths) {
  EXPECT_FALSE(CanBecome("abc", "ab"));
}

TEST(CanBecomeTest, HandlesSameString) {
  EXPECT_TRUE(CanBecome("aaaa", "aaaa"));
}

TEST(CanBecomeTest, HandlesSingleCharacter) {
  EXPECT_TRUE(CanBecome("a", "a"));
}

TEST(CanBecomeTest, HandlesRepeatedCharactersTrue) {
  EXPECT_TRUE(CanBecome("aab", "aba"));
}

TEST(CanBecomeTest, HandlesRepeatedCharactersFalse) {
  EXPECT_FALSE(CanBecome("aab", "abb"));
}

TEST(CanBecomeTest, HandlesRepeatedPatternFalse) {
  EXPECT_FALSE(CanBecome("abab", "aabb"));
}

TEST(CanBecomeTest, HandlesSameLengthDifferentLetters) {
  EXPECT_FALSE(CanBecome("abc", "abd"));
}

TEST(CanBecomeTest, HandlesOneShiftRotation) {
  EXPECT_TRUE(CanBecome("abcde", "eabcd"));
}

