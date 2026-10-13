#include <iostream>
#include <list>
#include <map>
#include <set>
#include <vector>

// Given a string return a map of how many times each character was used in the
// string.
//
// Example: Input: "This is a test".
// Output: {{'T', 1}, {'h', 1}, {'i', 2}, {'s', 3},
//          {' ', 3}, {'a', 1}, {'t', 2}, {'e', 1}}
std::map<char, int> CountCharacters(std::string& input);
