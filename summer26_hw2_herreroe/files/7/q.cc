#include "q.h"

#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>
// TODO:
// 1. Implement the the functions in q.h.
// 2. Write some unit tests for them in student_test.cc

std::vector<Frame> BuildFrames(const std::vector<Command>& commands) {
    std::vector<Frame> frames;
    std::vector<int> array;

    frames.push_back({array, "start"});

    for (const Command& cmd : commands) {
        if (cmd.op == "push_back") {
            array.push_back(cmd.value);
            frames.push_back({array, "push_back(" + std::to_string(cmd.value) + ")"});

        } else if (cmd.op == "pop_back") {
            if (array.empty()) {
                frames.push_back({array, "pop_back() [empty]"});
            } else {
                array.pop_back();
                frames.push_back({array, "pop_back()"});
            }

        } else if (cmd.op == "insert") {
            if (cmd.index < 0 || cmd.index > (int)array.size()) {
                frames.push_back({array, "insert(index=" + std::to_string(cmd.index) +
                                         ", value=" + std::to_string(cmd.value) + ") [out of range]"});
            } else {
                array.insert(array.begin() + cmd.index, cmd.value);
                frames.push_back({array, "insert(index=" + std::to_string(cmd.index) +
                                         ", value=" + std::to_string(cmd.value) + ")"});
            }

        } else if (cmd.op == "erase") {
            if (cmd.index < 0 || cmd.index >= (int)array.size()) {
                frames.push_back({array, "erase(index=" + std::to_string(cmd.index) + ") [out of range]"});
            } else {
                array.erase(array.begin() + cmd.index);
                frames.push_back({array, "erase(index=" + std::to_string(cmd.index) + ")"});
            }
        }
    }

    return frames;
}
