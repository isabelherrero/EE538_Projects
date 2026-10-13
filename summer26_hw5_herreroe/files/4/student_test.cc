#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------

TEST(FindAllPasswordsTest, Example1_SomeExcludedSomeKept) {
  std::unordered_set<std::string> dictionary = {"ab", "cd"};
  std::unordered_set<std::string> valid_passwords = {"abb", "cdd", "aa", "j"};
  BlackBox blackbox(valid_passwords, dictionary);

  std::unordered_set<std::string> expected = {"aa", "j"};
  EXPECT_EQ(FindAllPasswords(blackbox, 3), expected);
}

TEST(FindAllPasswordsTest, Example2_AllExcluded) {
  std::unordered_set<std::string> dictionary = {"a", "b"};
  std::unordered_set<std::string> valid_passwords = {"aa", "bad", "sad", "bbb"};
  BlackBox blackbox(valid_passwords, dictionary);

  std::unordered_set<std::string> expected = {};
  EXPECT_EQ(FindAllPasswords(blackbox, 3), expected);
}

TEST(FindAllPasswordsTest, MaxLengthZeroReturnsEmpty) {
  std::unordered_set<std::string> dictionary = {};
  std::unordered_set<std::string> valid_passwords = {"a", "b", "c"};
  BlackBox blackbox(valid_passwords, dictionary);

  EXPECT_TRUE(FindAllPasswords(blackbox, 0).empty());
}

TEST(FindAllPasswordsTest, NegativeMaxLengthReturnsEmpty) {
  std::unordered_set<std::string> dictionary = {};
  std::unordered_set<std::string> valid_passwords = {"a", "b", "c"};
  BlackBox blackbox(valid_passwords, dictionary);

  EXPECT_TRUE(FindAllPasswords(blackbox, -1).empty());
}

TEST(FindAllPasswordsTest, MaxLengthOneSingleCharacterPassword) {
  std::unordered_set<std::string> dictionary = {"z"};
  std::unordered_set<std::string> valid_passwords = {"j"};
  BlackBox blackbox(valid_passwords, dictionary);

  std::unordered_set<std::string> expected = {"j"};
  EXPECT_EQ(FindAllPasswords(blackbox, 1), expected);
}

TEST(FindAllPasswordsTest, EmptyDictionaryKeepsAllValidPasswords) {
  std::unordered_set<std::string> dictionary = {};
  std::unordered_set<std::string> valid_passwords = {"a", "bb", "ccc"};
  BlackBox blackbox(valid_passwords, dictionary);

  std::unordered_set<std::string> expected = {"a", "bb", "ccc"};
  EXPECT_EQ(FindAllPasswords(blackbox, 3), expected);
}

TEST(FindAllPasswordsTest, EmptyValidPasswordsReturnsEmpty) {
  std::unordered_set<std::string> dictionary = {"x"};
  std::unordered_set<std::string> valid_passwords = {};
  BlackBox blackbox(valid_passwords, dictionary);

  EXPECT_TRUE(FindAllPasswords(blackbox, 3).empty());
}

TEST(FindAllPasswordsTest, ValidPasswordLongerThanMaxLengthIsNeverFound) {
  std::unordered_set<std::string> dictionary = {};
  std::unordered_set<std::string> valid_passwords = {"abcd", "ab"};
  BlackBox blackbox(valid_passwords, dictionary);

  std::unordered_set<std::string> expected = {"ab"};
  EXPECT_EQ(FindAllPasswords(blackbox, 3), expected);
}

TEST(FindAllPasswordsTest, NonLowercasePasswordsAreNeverFound) {
  std::unordered_set<std::string> dictionary = {};
  std::unordered_set<std::string> valid_passwords = {"Ab", "a1", "a ", "ab"};
  BlackBox blackbox(valid_passwords, dictionary);

  std::unordered_set<std::string> expected = {"ab"};
  EXPECT_EQ(FindAllPasswords(blackbox, 2), expected);
}

TEST(FindAllPasswordsTest, DictionaryWordMatchesAnySubstringPosition) {
  std::unordered_set<std::string> dictionary = {"xy"};
  std::unordered_set<std::string> valid_passwords = {"xyz", "axy", "wxyz", "wz"};
  BlackBox blackbox(valid_passwords, dictionary);

  std::unordered_set<std::string> expected = {"wz"};
  EXPECT_EQ(FindAllPasswords(blackbox, 4), expected);
}

TEST(FindAllPasswordsTest, PasswordEqualsDictionaryWordExactly) {
  std::unordered_set<std::string> dictionary = {"cat"};
  std::unordered_set<std::string> valid_passwords = {"cat", "dog"};
  BlackBox blackbox(valid_passwords, dictionary);

  std::unordered_set<std::string> expected = {"dog"};
  EXPECT_EQ(FindAllPasswords(blackbox, 3), expected);
}

TEST(FindAllPasswordsTest, MultipleDictionaryWordsBlockDifferentPasswords) {
  std::unordered_set<std::string> dictionary = {"no", "bad"};
  std::unordered_set<std::string> valid_passwords = {"nope", "badge", "okay"};
  BlackBox blackbox(valid_passwords, dictionary);

  std::unordered_set<std::string> expected = {"okay"};
  EXPECT_EQ(FindAllPasswords(blackbox, 5), expected);
}