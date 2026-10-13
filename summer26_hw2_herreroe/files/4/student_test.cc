#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------

TEST(UniqueVectorNotBySet, BasicDuplicates) {
    std::vector<int> v = {1, 2, 2, 4};
    UniqueVectorNotBySet(v);
    EXPECT_EQ(v, (std::vector<int>{1, 2, 4}));
}

TEST(UniqueVectorNotBySet, NoDuplicates) {
    std::vector<int> v = {1, 2, 3};
    UniqueVectorNotBySet(v);
    EXPECT_EQ(v, (std::vector<int>{1, 2, 3}));
}

TEST(UniqueVectorNotBySet, AllDuplicates) {
    std::vector<int> v = {5, 5, 5, 5};
    UniqueVectorNotBySet(v);
    EXPECT_EQ(v, (std::vector<int>{5}));
}

TEST(UniqueVectorNotBySet, SingleElement) {
    std::vector<int> v = {42};
    UniqueVectorNotBySet(v);
    EXPECT_EQ(v, (std::vector<int>{42}));
}

TEST(UniqueVectorNotBySet, EmptyVector) {
    std::vector<int> v = {};
    UniqueVectorNotBySet(v);
    EXPECT_EQ(v, (std::vector<int>{}));
}

TEST(UniqueVectorNotBySet, MultipleDuplicates) {
    std::vector<int> v = {1, 1, 2, 2, 3, 3};
    UniqueVectorNotBySet(v);
    EXPECT_EQ(v, (std::vector<int>{1, 2, 3}));
}   

TEST(UniqueVectorBySet, BasicDuplicates) {
    std::vector<int> v = {1, 2, 2, 4};
    UniqueVectorBySet(v);
    EXPECT_EQ(v, (std::vector<int>{1, 2, 4}));
}

TEST(UniqueVectorBySet, NoDuplicates) {
    std::vector<int> v = {1, 2, 3};
    UniqueVectorBySet(v);
    EXPECT_EQ(v, (std::vector<int>{1, 2, 3}));
}

TEST(UniqueVectorBySet, AllDuplicates) {
    std::vector<int> v = {5, 5, 5, 5};
    UniqueVectorBySet(v);
    EXPECT_EQ(v, (std::vector<int>{5}));
}

TEST(UniqueVectorBySet, SingleElement) {
    std::vector<int> v = {42};
    UniqueVectorBySet(v);
    EXPECT_EQ(v, (std::vector<int>{42}));
}

TEST(UniqueVectorBySet, EmptyVector) {
    std::vector<int> v = {};
    UniqueVectorBySet(v);
    EXPECT_EQ(v, (std::vector<int>{}));
}

TEST(UniqueVectorBySet, MultipleDuplicates) {
    std::vector<int> v = {1, 1, 2, 2, 3, 3};
    UniqueVectorBySet(v);
    EXPECT_EQ(v, (std::vector<int>{1, 2, 3}));
}

TEST(IntersectVectors, BasicIntersection) {
    std::vector<int> v1 = {1, 2, 2, 3};
    std::vector<int> v2 = {3, 4, 4, 5};
    EXPECT_EQ(IntersectVectors(v1, v2), (std::vector<int>{3}));
}

TEST(IntersectVectors, NoIntersection) {
    std::vector<int> v1 = {1, 2};
    std::vector<int> v2 = {3, 4};
    EXPECT_EQ(IntersectVectors(v1, v2), (std::vector<int>{}));
}

TEST(IntersectVectors, FullIntersection) {
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {1, 2, 3};
    EXPECT_EQ(IntersectVectors(v1, v2), (std::vector<int>{1, 2, 3}));
}

TEST(IntersectVectors, DuplicatesInBoth) {
    std::vector<int> v1 = {1, 1, 2, 2};
    std::vector<int> v2 = {2, 2, 3, 3};
    EXPECT_EQ(IntersectVectors(v1, v2), (std::vector<int>{2}));
}

TEST(IntersectVectors, OneEmptyVector) {
    std::vector<int> v1 = {};
    std::vector<int> v2 = {1, 2, 3};
    EXPECT_EQ(IntersectVectors(v1, v2), (std::vector<int>{}));
}

TEST(IntersectVectors, BothEmpty) {
    std::vector<int> v1 = {};
    std::vector<int> v2 = {};
    EXPECT_EQ(IntersectVectors(v1, v2), (std::vector<int>{}));
}

TEST(DiffVectors, BasicDiff) {
    std::vector<int> v1 = {1, 2, 2, 3};
    std::vector<int> v2 = {3, 4, 4, 5};
    EXPECT_EQ(DiffVectors(v1, v2), (std::set<int>{1, 2}));
}

TEST(DiffVectors, NoDiff) {
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {1, 2, 3};
    EXPECT_EQ(DiffVectors(v1, v2), (std::set<int>{}));
}

TEST(DiffVectors, AllDiff) {
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {4, 5, 6};
    EXPECT_EQ(DiffVectors(v1, v2), (std::set<int>{1, 2, 3}));
}

TEST(DiffVectors, EmptyV1) {
    std::vector<int> v1 = {};
    std::vector<int> v2 = {1, 2, 3};
    EXPECT_EQ(DiffVectors(v1, v2), (std::set<int>{}));
}

TEST(DiffVectors, EmptyV2) {
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {};
    EXPECT_EQ(DiffVectors(v1, v2), (std::set<int>{1, 2, 3}));
}

TEST(DiffVectors, DuplicatesInV1) {
    std::vector<int> v1 = {1, 1, 2, 2, 3};
    std::vector<int> v2 = {3};
    EXPECT_EQ(DiffVectors(v1, v2), (std::set<int>{1, 2}));
}