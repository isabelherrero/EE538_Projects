#include "q.h"

#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#include <algorithm>
// TODO:
// 1. Implement the the functions in q.h.
// 2. Write some unit tests for them in student_test.cc

void UniqueVectorNotBySet(std::vector<int> &input) {
    for (int i = 0; i < input.size(); i++) {
        for (int j = i + 1; j < input.size(); j++) {
            if (input[i] == input[j]) {
                input.erase(input.begin() + j);
                j--;
            }
        }
    }
}

void UniqueVectorBySet(std::vector<int> &input) {
    std::set<int> seen;
    std::vector<int> result;
    for (int x : input) {
        if (seen.find(x) == seen.end()) {
            seen.insert(x);
            result.push_back(x);
        }
    }
    input = result;
}

std::vector<int> IntersectVectors(const std::vector<int> &input1,
                                  const std::vector<int> &input2) {
    std::set<int> seen(input2.begin(), input2.end());
    std::set<int> added;
    std::vector<int> result;
    for (int x : input1) {
        if (seen.count(x) && !added.count(x)) {
            result.push_back(x);
            added.insert(x);
        }
    }
    return result;
}

std::set<int> DiffVectors(const std::vector<int> &input1,
                          const std::vector<int> &input2) {
    std::vector<int> intersection = IntersectVectors(input1, input2);
    std::set<int> result;
    for (int x : input1) {
        if (std::find(intersection.begin(), intersection.end(), x) 
            == intersection.end()) {
            result.insert(x);
        }
    }
    return result;
}