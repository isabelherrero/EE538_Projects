#include <iostream>
#include <map>
#include <string>
#include <vector>

// TODO: Implement the following functions in q.cc
//-----------------------------------------------------------------------------
// Returns the index of the fist space character in a string.
// Returns -1 if there are no spaces.
int IndexOfFirstSpace(std::string &input);
//-----------------------------------------------------------------------------
// Given the full_name, it returns the first_name and last_name.
// Note: you should use IndexOfFirstSpace function and cannot use any other
// std:: functions.
// If there is no space, set the last_name to an empty string.
// If the string is empty, both first and last name should be empty strings.
void SeparateFirstAndLastNames(std::string &full_name, std::string &first_name,
                               std::string &last_name);
//-----------------------------------------------------------------------------
// implement a helper function splitString that takes in a string and returns a
// vector of strings split by spaces.
std::vector<std::string> SplitString(const std::string &str);

//-----------------------------------------------------------------------------
// Suppose you have a string with multiple words separated by spaces. Implement
// a function CalculateFrequency that takes in this string and returns a map
// where the key is the word and the value is its frequency in the string.
// In your implementation you can use:
// - SplitString function in your implementation.
// - std::string's find function.
// - std::vector.
// - Do not use any other class from STL such as `istringstream` that are not
// discussed in our lectures.
// Example
// input: "apple banana orange apple apple banana"
// Output:
// apple: 3
// banana: 2
// orange: 1
std::map<std::string, int> CalculateFrequency(const std::string &input);
