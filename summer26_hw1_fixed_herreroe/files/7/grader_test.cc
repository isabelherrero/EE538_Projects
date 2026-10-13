#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------s
TEST(CanBecomeTest, TestCase1) { EXPECT_TRUE(CanBecome("abcde", "cdeab")); }

TEST(CanBecomeTest, TestCase2) { EXPECT_FALSE(CanBecome("abcde", "abced")); }

TEST(CanBecomeTest, TestCase3) { EXPECT_TRUE(CanBecome("abcde", "abcde")); }

TEST(CanBecomeTest, TestCase4) { EXPECT_TRUE(CanBecome("a", "a")); }

TEST(CanBecomeTest, TestCase5) { EXPECT_FALSE(CanBecome("abcde", "abcdea")); }
TEST(CanBecomeTest, TestCase6) { EXPECT_FALSE(CanBecome("a", "")); }
TEST(CanBecomeTest, TestCase7) { EXPECT_FALSE(CanBecome("", "a")); }
TEST(CanBecomeTest, TestCase8) { EXPECT_TRUE(CanBecome("", "")); }