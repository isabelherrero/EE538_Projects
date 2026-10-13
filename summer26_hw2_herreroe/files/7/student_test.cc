#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------

void CheckFrame(const std::vector<Frame>& frames, int i,
                std::vector<int> expected_values, std::string expected_label) {
    ASSERT_LT(i, (int)frames.size());
    EXPECT_EQ(frames[i].values, expected_values);
    EXPECT_EQ(frames[i].label, expected_label);
}

TEST(BuildFrames, EmptyCommandsGivesStartFrame) {
    std::vector<Frame> frames = BuildFrames({});
    ASSERT_EQ(frames.size(), 1);
    CheckFrame(frames, 0, {}, "start");
}

TEST(BuildFrames, AlwaysStartsWithEmptyArray) {
    std::vector<Frame> frames = BuildFrames({{"push_back", 1, 0}});
    CheckFrame(frames, 0, {}, "start");
}

TEST(BuildFrames, PushBackSingle) {
    std::vector<Frame> frames = BuildFrames({{"push_back", 5, 0}});
    ASSERT_EQ(frames.size(), 2);
    CheckFrame(frames, 1, {5}, "push_back(5)");
}

TEST(BuildFrames, PushBackMultiple) {
    std::vector<Frame> frames = BuildFrames({
        {"push_back", 1, 0},
        {"push_back", 2, 0},
        {"push_back", 3, 0}
    });
    ASSERT_EQ(frames.size(), 4);
    CheckFrame(frames, 1, {1},       "push_back(1)");
    CheckFrame(frames, 2, {1, 2},    "push_back(2)");
    CheckFrame(frames, 3, {1, 2, 3}, "push_back(3)");
}

TEST(BuildFrames, PushBackZero) {
    std::vector<Frame> frames = BuildFrames({{"push_back", 0, 0}});
    CheckFrame(frames, 1, {0}, "push_back(0)");
}

TEST(BuildFrames, PopBackNormal) {
    std::vector<Frame> frames = BuildFrames({
        {"push_back", 10, 0},
        {"pop_back", 0, 0}
    });
    CheckFrame(frames, 2, {}, "pop_back()");
}

TEST(BuildFrames, PopBackOnEmpty) {
    std::vector<Frame> frames = BuildFrames({{"pop_back", 0, 0}});
    ASSERT_EQ(frames.size(), 2);
    CheckFrame(frames, 1, {}, "pop_back() [empty]");
}

TEST(BuildFrames, PopBackLeavesArrayUnchanged) {
    std::vector<Frame> frames = BuildFrames({{"pop_back", 0, 0}});
    EXPECT_TRUE(frames[1].values.empty());
}

TEST(BuildFrames, MultiplePopBacksUntilEmpty) {
    std::vector<Frame> frames = BuildFrames({
        {"push_back", 1, 0},
        {"push_back", 2, 0},
        {"pop_back", 0, 0},
        {"pop_back", 0, 0},
        {"pop_back", 0, 0}   // empty
    });
    CheckFrame(frames, 3, {1},  "pop_back()");
    CheckFrame(frames, 4, {},   "pop_back()");
    CheckFrame(frames, 5, {},   "pop_back() [empty]");
}

TEST(BuildFrames, InsertAtBeginning) {
    std::vector<Frame> frames = BuildFrames({
        {"push_back", 2, 0},
        {"insert", 1, 0}
    });
    CheckFrame(frames, 2, {1, 2}, "insert(index=0, value=1)");
}

TEST(BuildFrames, InsertAtEnd) {
    std::vector<Frame> frames = BuildFrames({
        {"push_back", 1, 0},
        {"insert", 2, 1}
    });
    CheckFrame(frames, 2, {1, 2}, "insert(index=1, value=2)");
}

TEST(BuildFrames, InsertAtMiddle) {
    std::vector<Frame> frames = BuildFrames({
        {"push_back", 1, 0},
        {"push_back", 3, 0},
        {"insert", 2, 1}
    });
    CheckFrame(frames, 3, {1, 2, 3}, "insert(index=1, value=2)");
}

TEST(BuildFrames, InsertOutOfRangeNegative) {
    std::vector<Frame> frames = BuildFrames({
        {"push_back", 1, 0},
        {"insert", 99, -1}
    });
    // array must be unchanged
    CheckFrame(frames, 2, {1}, "insert(index=-1, value=99) [out of range]");
}

TEST(BuildFrames, InsertOutOfRangeTooLarge) {
    std::vector<Frame> frames = BuildFrames({
        {"push_back", 1, 0},
        {"insert", 99, 50}
    });
    CheckFrame(frames, 2, {1}, "insert(index=50, value=99) [out of range]");
}

TEST(BuildFrames, InsertIntoEmptyArray) {
    std::vector<Frame> frames = BuildFrames({{"insert", 7, 0}});
    CheckFrame(frames, 1, {7}, "insert(index=0, value=7)");
}

TEST(BuildFrames, EraseFirst) {
    std::vector<Frame> frames = BuildFrames({
        {"push_back", 1, 0},
        {"push_back", 2, 0},
        {"erase", 0, 0}
    });
    CheckFrame(frames, 3, {2}, "erase(index=0)");
}

TEST(BuildFrames, EraseLast) {
    std::vector<Frame> frames = BuildFrames({
        {"push_back", 1, 0},
        {"push_back", 2, 0},
        {"erase", 0, 1}
    });
    CheckFrame(frames, 3, {1}, "erase(index=1)");
}

TEST(BuildFrames, EraseMiddle) {
    std::vector<Frame> frames = BuildFrames({
        {"push_back", 1, 0},
        {"push_back", 2, 0},
        {"push_back", 3, 0},
        {"erase", 0, 1}
    });
    CheckFrame(frames, 4, {1, 3}, "erase(index=1)");
}

TEST(BuildFrames, EraseOutOfRangeNegative) {
    std::vector<Frame> frames = BuildFrames({
        {"push_back", 1, 0},
        {"erase", 0, -1}
    });
    CheckFrame(frames, 2, {1}, "erase(index=-1) [out of range]");
}

TEST(BuildFrames, EraseOutOfRangeTooLarge) {
    std::vector<Frame> frames = BuildFrames({
        {"push_back", 1, 0},
        {"erase", 0, 9}
    });
    CheckFrame(frames, 2, {1}, "erase(index=9) [out of range]");
}

TEST(BuildFrames, EraseOnEmptyArray) {
    std::vector<Frame> frames = BuildFrames({{"erase", 0, 0}});
    CheckFrame(frames, 1, {}, "erase(index=0) [out of range]");
}

TEST(BuildFrames, MixedOperations) {
    std::vector<Frame> frames = BuildFrames({
        {"push_back", 1, 0},
        {"push_back", 2, 0},
        {"insert", 0, 0},
        {"erase", 0, 1},
        {"pop_back", 0, 0}
    });
    CheckFrame(frames, 1, {1},       "push_back(1)");
    CheckFrame(frames, 2, {1, 2},    "push_back(2)");
    CheckFrame(frames, 3, {0, 1, 2}, "insert(index=0, value=0)");
    CheckFrame(frames, 4, {0, 2},    "erase(index=1)");
    CheckFrame(frames, 5, {0},       "pop_back()");
}

TEST(BuildFrames, FrameCountMatchesCommandsPlusOne) {
    std::vector<Command> cmds = {
        {"push_back", 1, 0},
        {"push_back", 2, 0},
        {"pop_back", 0, 0}
    };
    std::vector<Frame> frames = BuildFrames(cmds);
    EXPECT_EQ(frames.size(), cmds.size() + 1);
}