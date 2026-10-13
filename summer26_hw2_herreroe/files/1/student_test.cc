#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------

TEST(CountCharactersTest, EmptyString) {
    std::string input = "";
    std::map<char, int> expected = {};

    EXPECT_EQ(CountCharacters(input), expected);
}

TEST(CountCharactersTest, SingleCharacter) {
    std::string input = "a";
    std::map<char, int> expected = {
        {'a', 1}
    };

    EXPECT_EQ(CountCharacters(input), expected);
}

TEST(CountCharactersTest, AllSameCharacter) {
    std::string input = "aaaaa";
    std::map<char, int> expected = {
        {'a', 5}
    };

    EXPECT_EQ(CountCharacters(input), expected);
}

TEST(CountCharactersTest, MultipleDifferentCharacters) {
    std::string input = "abc";
    std::map<char, int> expected = {
        {'a', 1},
        {'b', 1},
        {'c', 1}
    };

    EXPECT_EQ(CountCharacters(input), expected);
}

TEST(CountCharactersTest, RepeatedCharacters) {
    std::string input = "banana";
    std::map<char, int> expected = {
        {'b', 1},
        {'a', 3},
        {'n', 2}
    };

    EXPECT_EQ(CountCharacters(input), expected);
}

TEST(CountCharactersTest, SpacesAreCounted) {
    std::string input = "a a";
    std::map<char, int> expected = {
        {'a', 2},
        {' ', 1}
    };

    EXPECT_EQ(CountCharacters(input), expected);
}

TEST(CountCharactersTest, PunctuationIsCounted) {
    std::string input = "hi!";
    std::map<char, int> expected = {
        {'h', 1},
        {'i', 1},
        {'!', 1}
    };

    EXPECT_EQ(CountCharacters(input), expected);
}

TEST(CountCharactersTest, CaseSensitive) {
    std::string input = "Aa";
    std::map<char, int> expected = {
        {'A', 1},
        {'a', 1}
    };

    EXPECT_EQ(CountCharacters(input), expected);
}

TEST(CountCharactersTest, ExampleFromPrompt) {
    std::string input = "This is a test";
    std::map<char, int> expected = {
        {'T', 1},
        {'h', 1},
        {'i', 2},
        {'s', 3},
        {' ', 3},
        {'a', 1},
        {'t', 2},
        {'e', 1}
    };

    EXPECT_EQ(CountCharacters(input), expected);
}