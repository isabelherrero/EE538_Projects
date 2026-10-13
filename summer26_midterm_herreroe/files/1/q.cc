#include "q.h"

#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>
// TODO:
// 1. Implement the the functions in q.h.
// 2. Write some unit tests for them in student_test.cc

// Returns the index of the first space character in a string
int IndexOfFirstSpace(std::string &input) {
    // Loop through the string to find the first space character
    for (int i = 0; i < input.size(); i++) {
        // If a space is found, return its index
        if (input[i] == ' ')
            return i;
    }
    // If no space is found, return -1
    return -1;
}

// Splits full_name into first_name and last_name using IndexOfFirstSpace
void SeparateFirstAndLastNames(std::string &full_name, std::string &first_name, std::string &last_name) {
    // If empty, both names are empty
    if (full_name.empty()) {
        first_name = "";
        last_name = "";
        // Return early since there is nothing to split
        return;
    }

    // Find the index of the first space in the full name
    int index = IndexOfFirstSpace(full_name);

    // If no space, first name is the full name and last name is empty
    if (index == -1) {
        first_name = full_name;
        last_name = "";
        // Return early since there is no last name
        return;
    }

    // Split at the space index
    // The first name is everything before the first space
    first_name = full_name.substr(0, index);
    // The last name is the substring after the first space
    last_name = full_name.substr(index + 1);
}

// Splits a string into a vector of words seperated by spaces
std::vector<std::string> SplitString(const std::string &str) {
    // Create a vector to hold the words and a string to build each word
    std::vector<std::string> words;
    // Initialize an empty string to hold the current word
    std::string word = "";

    // Loop through the string to build words
    for (int i = 0; i < str.size(); i++) {
        // When there is a space, it saves the current word if it is not empty
        if (str[i] == ' ') {
            // Adds the word to the vector if it is not empty
            if (word != "") {
                words.push_back(word);
                word = "";
            }
        // If the current character is not a space, it adds it to the current word
        } else {
            word += str[i];
        }
    }
    // Push the last word if there is one
    if (word != "")
        words.push_back(word);
    // Return the vector of words
    return words;
}

// Returns a map of word frequencies from a space separated string
std::map<std::string, int> CalculateFrequency(const std::string &input) {
    // Create a map to hold the frequency of each word
    std::map<std::string, int> frequency;
    // Split the input string into words using the SplitString function
    std::vector<std::string> words = SplitString(input);

    // Loop through the vector of words and count the times they appear (frequency)
    for (int i = 0; i < words.size(); i++) {
        if (frequency.find(words[i]) == frequency.end()) {
            // If the word is not in the map, add it with a count of 1
            frequency[words[i]] = 1;
        } else {
            // If the word is already in the map, increment its count
            frequency[words[i]]++;
        }
    }

    // Return the map containing the frequency of each word
    return frequency;
}
