#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------

TEST(SwapByPointerTest, BasicSwap) {
    float x = 10.0f, y = 15.0f;
    SwapByPointer(&x, &y);
    EXPECT_FLOAT_EQ(x, 15.0f);
    EXPECT_FLOAT_EQ(y, 10.0f);
}

TEST(SwapByPointerTest, NegativeValues) {
    float x = -3.5f, y = -7.2f;
    SwapByPointer(&x, &y);
    EXPECT_FLOAT_EQ(x, -7.2f);
    EXPECT_FLOAT_EQ(y, -3.5f);
}

TEST(SwapByPointerTest, OneNegativeOnePositive) {
    float x = -5.0f, y = 5.0f;
    SwapByPointer(&x, &y);
    EXPECT_FLOAT_EQ(x, 5.0f);
    EXPECT_FLOAT_EQ(y, -5.0f);
}

TEST(SwapByPointerTest, ZeroValues) {
    float x = 0.0f, y = 0.0f;
    SwapByPointer(&x, &y);
    EXPECT_FLOAT_EQ(x, 0.0f);
    EXPECT_FLOAT_EQ(y, 0.0f);
}

TEST(SwapByPointerTest, OneZero) {
    float x = 0.0f, y = 42.0f;
    SwapByPointer(&x, &y);
    EXPECT_FLOAT_EQ(x, 42.0f);
    EXPECT_FLOAT_EQ(y, 0.0f);
}

TEST(SwapByPointerTest, SameValue) {
    float x = 7.7f, y = 7.7f;
    SwapByPointer(&x, &y);
    EXPECT_FLOAT_EQ(x, 7.7f);
    EXPECT_FLOAT_EQ(y, 7.7f);
}

TEST(SwapByPointerTest, LargeValues) {
    float x = 1e30f, y = -1e30f;
    SwapByPointer(&x, &y);
    EXPECT_FLOAT_EQ(x, -1e30f);
    EXPECT_FLOAT_EQ(y, 1e30f);
}

TEST(SwapByPointerTest, SmallDecimalValues) {
    float x = 0.0001f, y = 0.0002f;
    SwapByPointer(&x, &y);
    EXPECT_FLOAT_EQ(x, 0.0002f);
    EXPECT_FLOAT_EQ(y, 0.0001f);
}

TEST(SwapByReferenceTest, BasicSwap) {
    float x = 10.0f, y = 15.0f;
    SwapByReference(x, y);
    EXPECT_FLOAT_EQ(x, 15.0f);
    EXPECT_FLOAT_EQ(y, 10.0f);
}

TEST(SwapByReferenceTest, NegativeValues) {
    float x = -3.5f, y = -7.2f;
    SwapByReference(x, y);
    EXPECT_FLOAT_EQ(x, -7.2f);
    EXPECT_FLOAT_EQ(y, -3.5f);
}

TEST(SwapByReferenceTest, OneNegativeOnePositive) {
    float x = -5.0f, y = 5.0f;
    SwapByReference(x, y);
    EXPECT_FLOAT_EQ(x, 5.0f);
    EXPECT_FLOAT_EQ(y, -5.0f);
}

TEST(SwapByReferenceTest, ZeroValues) {
    float x = 0.0f, y = 0.0f;
    SwapByReference(x, y);
    EXPECT_FLOAT_EQ(x, 0.0f);
    EXPECT_FLOAT_EQ(y, 0.0f);
}

TEST(SwapByReferenceTest, OneZero) {
    float x = 0.0f, y = 42.0f;
    SwapByReference(x, y);
    EXPECT_FLOAT_EQ(x, 42.0f);
    EXPECT_FLOAT_EQ(y, 0.0f);
}

TEST(SwapByReferenceTest, SameValue) {
    float x = 7.7f, y = 7.7f;
    SwapByReference(x, y);
    EXPECT_FLOAT_EQ(x, 7.7f);
    EXPECT_FLOAT_EQ(y, 7.7f);
}

TEST(SwapByReferenceTest, LargeValues) {
    float x = 1e30f, y = -1e30f;
    SwapByReference(x, y);
    EXPECT_FLOAT_EQ(x, -1e30f);
    EXPECT_FLOAT_EQ(y, 1e30f);
}

TEST(SwapByReferenceTest, SmallDecimalValues) {
    float x = 0.0001f, y = 0.0002f;
    SwapByReference(x, y);
    EXPECT_FLOAT_EQ(x, 0.0002f);
    EXPECT_FLOAT_EQ(y, 0.0001f);
}

TEST(SwapByPointerTest, NullPointers) {
    SwapByPointer(nullptr, nullptr);
}

TEST(SwapByPointerTest, OneNullPointer) {
    float x = 5.0f;
    SwapByPointer(&x, nullptr);
    EXPECT_FLOAT_EQ(x, 5.0f);
}