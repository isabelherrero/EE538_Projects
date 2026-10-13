#include "q.h"

#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>
// TODO:
// 1. Implement the the functions in q.h.
// 2. Write some unit tests for them in student_test.cc

void FindAllPasswords_aux(BlackBox& blackbox, int max_length,
                           std::string& current_password,
                           std::unordered_set<std::string>& results) {
  if (!current_password.empty()) {
    if (blackbox.TryPassword(current_password) &&
        !blackbox.IsInDictionary(current_password)) {
      results.insert(current_password);
    }
  }

  if (static_cast<int>(current_password.size()) >= max_length) {
    return;
  }

  for (char c = 'a'; c <= 'z'; ++c) {
    current_password.push_back(c);
    FindAllPasswords_aux(blackbox, max_length, current_password, results);
    current_password.pop_back();
  }
}

std::unordered_set<std::string> FindAllPasswords(BlackBox& blackbox,
                                                   int max_length) {
  std::unordered_set<std::string> results;

  if (max_length <= 0) {
    return results;
  }

  std::string current_password;
  FindAllPasswords_aux(blackbox, max_length, current_password, results);
  return results;
}