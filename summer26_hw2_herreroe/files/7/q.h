#ifndef DYNAMIC_ARRAY_VIZ_H
#define DYNAMIC_ARRAY_VIZ_H

#include <string>
#include <vector>

// HW2 - Q7: Visualizing a Dynamic Array
//
// In Q5 you implemented push_back / pop_back / insert / erase on a raw
// dynamic array. In this question you build the *data* that drives an animated
// cpptui visualization of those very same operations (see viz.cc).
//
// The idea: instead of mutating an array in place and losing the history, you
// replay a list of operations and record one snapshot ("frame") after each
// step. The visualization then plays the frames back like a flip-book so a
// student can watch the array grow, shift, and shrink.
//
// You only have to implement the pure logic in q.cc. The cpptui rendering in
// viz.cc is provided for you and depends only on the functions below.

// A Frame is one snapshot of the array: its contents at a moment in time plus a
// short, human-readable label explaining the operation that produced it.
struct Frame {
  std::vector<int> values;  // the array contents in this snapshot
  std::string label;        // e.g. "push_back(7)" or "erase(index=2)"
};

// A Command describes one operation to apply to the dynamic array.
// op is one of: "push_back", "pop_back", "insert", "erase".
//   "push_back" -> appends `value`            (ignores `index`)
//   "pop_back"  -> removes the last element   (ignores `value`, `index`)
//   "insert"    -> inserts `value` at `index` (valid index range: 0 .. size)
//   "erase"     -> erases element at `index`  (valid index range: 0 .. size-1)
struct Command {
  std::string op;
  int value = 0;
  int index = 0;
};

// Replays `commands` on an initially-empty dynamic array and returns one Frame
// per step.
//
//   * The FIRST frame is always the empty starting state with label "start".
//   * Each following frame is the array state AFTER applying one command.
//
// Label format (must match exactly so the grader can check it):
//   start          -> "start"
//   push_back(v)   -> "push_back(<v>)"
//   pop_back ok    -> "pop_back()"
//   pop_back empty -> "pop_back() [empty]"
//   insert ok      -> "insert(index=<i>, value=<v>)"
//   insert bad i   -> "insert(index=<i>, value=<v>) [out of range]"
//   erase ok       -> "erase(index=<i>)"
//   erase bad i    -> "erase(index=<i>) [out of range]"
//
// An out-of-range or empty operation must leave the array UNCHANGED but still
// emit a frame whose label carries the suffix above.
std::vector<Frame> BuildFrames(const std::vector<Command>& commands);

#endif  // DYNAMIC_ARRAY_VIZ_H
