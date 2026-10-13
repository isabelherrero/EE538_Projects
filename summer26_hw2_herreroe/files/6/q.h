#ifndef SET_OPERATIONS_H
#define SET_OPERATIONS_H

#include <set>

// Function declarations for set operations

// Function to compute the set difference (elements present in set1 but not in
// set2)
std::set<int> setDifference(const std::set<int> &set1,
                            const std::set<int> &set2);

// Function to check if two sets are disjoint (have no common elements)
bool areDisjoint(const std::set<int> &set1, const std::set<int> &set2);

#endif // SET_OPERATIONS_H
