#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Writing student test is optional!
//-----------------------------------------------------------------------------

// Test basic operations with positive numbers
TEST(CalculateTest, BasicOperations) {
    int a = 10, b = 9;
    EXPECT_EQ(Calculate(a, b, Operation::kAdd), 19); // 10 + 9 = 19
    EXPECT_EQ(Calculate(a, b, Operation::kSubtract), 1); // 10 - 9 = 1
    EXPECT_EQ(Calculate(a, b, Operation::kMultiplication), 90); // 10 * 9 = 90
    EXPECT_NEAR(Calculate(a, b, Operation::kDivision), 1.1f, 0.1f); // 10 / 9 ≈ 1.1111
    EXPECT_EQ(Calculate(a, b, Operation::kBitwise_AND), 0x8); // 1010 & 1001 = 1000 (8 in decimal)
    EXPECT_EQ(Calculate(a, b, Operation::kBitwise_OR), 0xB); // 1010 | 1001 = 1011 (11 in decimal)
    EXPECT_EQ(Calculate(a, b, Operation::kBitwise_XOR), 0x3); // 1010 ^ 1001 = 0011 (3 in decimal)
    EXPECT_EQ(Calculate(a, b, Operation::kShift_left), 0x1400); // 10 << 9 = 5120
    EXPECT_EQ(Calculate(a, b, Operation::kShift_right), 0x0); // 10 >> 9 = 0
}

// Test operations with negative numbers
TEST(CalculateTest, NegativeNumbers) {
    int a = -6, b = 2;
    EXPECT_EQ(Calculate(a, b, Operation::kAdd), -4); // -6 + 2 = -4
    EXPECT_EQ(Calculate(a, b, Operation::kSubtract), -8); // -6 - 2 = -8
    EXPECT_EQ(Calculate(a, b, Operation::kMultiplication), -12); // -6 * 2 = -12
    EXPECT_NEAR(Calculate(a, b, Operation::kDivision), -3.0f, 0.1f); // -6 / 2 = -3.0
}

// Test operations with zero
TEST(CalculateTest, ZeroOperand) {
    int a = 0, b = 5;
    EXPECT_EQ(Calculate(a, b, Operation::kAdd), 5); // 0 + 5 = 5
    EXPECT_EQ(Calculate(a, b, Operation::kSubtract), -5); // 0 - 5 = -5
    EXPECT_EQ(Calculate(a, b, Operation::kMultiplication), 0); // 0 * 5 = 0
    EXPECT_NEAR(Calculate(a, b, Operation::kDivision), 0.0f, 0.1f); // 0 / 5 = 0.0
    EXPECT_EQ(Calculate(a, b, Operation::kBitwise_AND), 0); // 0000 & 00101 = 00000 (0 in decimal)
    EXPECT_EQ(Calculate(a, b, Operation::kBitwise_OR), 5); // 0000 | 00101 = 00101 (5 in decimal)
    EXPECT_EQ(Calculate(a, b, Operation::kBitwise_XOR), 5); // 0000 ^ 00101 = 00101 (5 in decimal)
}

// Test more cases
TEST(CalculateTest, MoreCases) {
    // XOR with same values should return 0
    EXPECT_EQ(Calculate(5, 5, Operation::kBitwise_XOR), 0);    // 0101 ^ 0101 = 0000 (0 in decimal)
    // Shift by 0, should return the same number
    EXPECT_EQ(Calculate(10, 0, Operation::kShift_left), 10);   // 10 << 0 = 10
    EXPECT_EQ(Calculate(10, 0, Operation::kShift_right), 10);  // 10 >> 0 = 10
    // Subtraction where a == b, should return 0
    EXPECT_EQ(Calculate(5, 5, Operation::kSubtract), 0);       // 5 - 5 = 0
}