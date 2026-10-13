#include <iostream>
#include <list>
#include <string>
#include <vector>

// TODO:
// 1. Implement the following functions in q.cc.
// 2. Write some unit tests for them in student_test.cc

//-----------------------------------------------------------------------------
// Given two strings s and goal, return true if and only if s can become goal
// after some number of shifts on s.

// A shift on s consists of moving the leftmost character of s to the rightmost
// position.

// For example, if s = "abcde", then it will be "bcdea" after one shift.

// Example 1:

// Input: s = "abcde", goal = "cdeab"
// Output: true
// Example 2:

// Input: s = "abcde", goal = "abced"
// Output: false
bool CanBecome(const std::string &s, const std::string &goal);