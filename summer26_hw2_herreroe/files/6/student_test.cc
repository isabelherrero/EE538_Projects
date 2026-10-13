#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------

TEST(SetDifference, BasicDifference) {
    std::set<int> s1 = {1, 2, 3, 4};
    std::set<int> s2 = {3, 4, 5, 6};
    EXPECT_EQ(setDifference(s1, s2), (std::set<int>{1, 2}));
}

TEST(SetDifference, NoCommonElements) {
    std::set<int> s1 = {1, 2, 3};
    std::set<int> s2 = {4, 5, 6};
    EXPECT_EQ(setDifference(s1, s2), (std::set<int>{1, 2, 3}));
}

TEST(SetDifference, AllCommonElements) {
    std::set<int> s1 = {1, 2, 3};
    std::set<int> s2 = {1, 2, 3};
    EXPECT_EQ(setDifference(s1, s2), (std::set<int>{}));
}

TEST(SetDifference, EmptySet1) {
    std::set<int> s1 = {};
    std::set<int> s2 = {1, 2, 3};
    EXPECT_EQ(setDifference(s1, s2), (std::set<int>{}));
}

TEST(SetDifference, EmptySet2) {
    std::set<int> s1 = {1, 2, 3};
    std::set<int> s2 = {};
    EXPECT_EQ(setDifference(s1, s2), (std::set<int>{1, 2, 3}));
}

TEST(SetDifference, BothEmpty) {
    std::set<int> s1 = {};
    std::set<int> s2 = {};
    EXPECT_EQ(setDifference(s1, s2), (std::set<int>{}));
}

TEST(SetDifference, SingleElementMatch) {
    std::set<int> s1 = {5};
    std::set<int> s2 = {5};
    EXPECT_EQ(setDifference(s1, s2), (std::set<int>{}));
}

TEST(SetDifference, SingleElementNoMatch) {
    std::set<int> s1 = {5};
    std::set<int> s2 = {9};
    EXPECT_EQ(setDifference(s1, s2), (std::set<int>{5}));
}

TEST(SetDifference, S2LargerThanS1) {
    std::set<int> s1 = {1, 2};
    std::set<int> s2 = {1, 2, 3, 4, 5};
    EXPECT_EQ(setDifference(s1, s2), (std::set<int>{}));
}

TEST(SetDifference, NegativeNumbers) {
    std::set<int> s1 = {-3, -2, -1, 0};
    std::set<int> s2 = {-2, 0};
    EXPECT_EQ(setDifference(s1, s2), (std::set<int>{-3, -1}));
}

TEST(AreDisjoint, TrulyDisjoint) {
    std::set<int> s1 = {1, 2, 3};
    std::set<int> s2 = {4, 5, 6};
    EXPECT_TRUE(areDisjoint(s1, s2));
}

TEST(AreDisjoint, NotDisjoint) {
    std::set<int> s1 = {1, 2, 3};
    std::set<int> s2 = {3, 4, 5};
    EXPECT_FALSE(areDisjoint(s1, s2));
}

TEST(AreDisjoint, FullOverlap) {
    std::set<int> s1 = {1, 2, 3};
    std::set<int> s2 = {1, 2, 3};
    EXPECT_FALSE(areDisjoint(s1, s2));
}

TEST(AreDisjoint, BothEmpty) {
    std::set<int> s1 = {};
    std::set<int> s2 = {};
    EXPECT_TRUE(areDisjoint(s1, s2));  // vacuously true
}

TEST(AreDisjoint, OneEmpty) {
    std::set<int> s1 = {};
    std::set<int> s2 = {1, 2, 3};
    EXPECT_TRUE(areDisjoint(s1, s2));  // empty set is disjoint with everything
}

TEST(AreDisjoint, OtherEmpty) {
    std::set<int> s1 = {1, 2, 3};
    std::set<int> s2 = {};
    EXPECT_TRUE(areDisjoint(s1, s2));
}

TEST(AreDisjoint, SingleElementMatch) {
    std::set<int> s1 = {7};
    std::set<int> s2 = {7};
    EXPECT_FALSE(areDisjoint(s1, s2));
}

TEST(AreDisjoint, SingleElementNoMatch) {
    std::set<int> s1 = {7};
    std::set<int> s2 = {8};
    EXPECT_TRUE(areDisjoint(s1, s2));
}

TEST(AreDisjoint, OnlyLastElementOverlaps) {
    std::set<int> s1 = {1, 2, 3, 10};
    std::set<int> s2 = {10, 20, 30};
    EXPECT_FALSE(areDisjoint(s1, s2));
}

TEST(AreDisjoint, NegativeNumbers) {
    std::set<int> s1 = {-3, -2, -1};
    std::set<int> s2 = {-1, 0, 1};
    EXPECT_FALSE(areDisjoint(s1, s2));
}