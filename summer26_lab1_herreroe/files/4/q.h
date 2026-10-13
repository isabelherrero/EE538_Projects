#ifndef HASH_MAP_VIZ_H
#define HASH_MAP_VIZ_H

#include <cstddef>
#include <string>
#include <vector>

// Activity 8: Visualizing a vector-bucket hash map.
//
// Implement BuildHashMapFrames in q.cc. The visualization in viz.cc is already
// provided and only depends on the frame data produced here.

// One key/value pair stored inside one bucket in one visualization frame.
//
// This mirrors a single std::pair<std::string, int> from the main hash map
// exercise, but uses named fields so the visualizer code is easier to read.
struct HashMapEntry {
  std::string key;  // The stored key, such as "alpha".
  int value = 0;    // The integer value associated with `key`.
};

// One snapshot of the hash map after an operation.
//
// BuildHashMapFrames returns a vector of these snapshots. The visualizer plays
// them back one at a time, like a flip book.
struct HashMapFrame {
  // Current bucket contents.
  //
  // The outer vector is the bucket array. Each inner vector is one bucket.
  // Each HashMapEntry in an inner vector is one key/value pair in that bucket.
  std::vector<std::vector<HashMapEntry>> buckets;

  // Human-readable description of the operation that produced this frame.
  // The exact label text is part of the assignment contract and is tested.
  std::string label;

  // Number of stored key/value pairs across all buckets.
  // This should equal the sum of all inner bucket sizes.
  std::size_t size = 0;
};

// One command to replay while building visualization frames.
//
// Field usage by operation:
//   op == "insert":
//     * use `key`
//     * use `value`
//     * ignore `bucket_count`
//
//   op == "erase":
//     * use `key`
//     * ignore `value`
//     * ignore `bucket_count`
//
//   op == "rehash":
//     * use `bucket_count`
//     * ignore `key`
//     * ignore `value`
//
// Unknown `op` strings are ignored and should not produce a frame.
struct HashCommand {
  // Operation name: "insert", "erase", or "rehash".
  std::string op;

  // Key used by "insert" and "erase".
  std::string key;

  // Value used by "insert".
  int value = 0;

  // New bucket count used by "rehash".
  std::size_t bucket_count = 0;
};

// Replays commands on an initially-empty vector-bucket hash map.
//
// The first frame is always the empty starting state with label "start".
// If initial_bucket_count is 0, start with 1 bucket.
//
// Label format must match exactly:
//   start                 -> "start"
//   insert new            -> "insert(\"<key>\", <value>)"
//   insert overwrite      -> "insert(\"<key>\", <value>) [overwrite]"
//   erase existing        -> "erase(\"<key>\")"
//   erase missing         -> "erase(\"<key>\") [missing]"
//   rehash valid          -> "rehash(<bucket_count>)"
//   rehash zero           -> "rehash(0) [invalid]"
//
// Invalid rehash leaves the map unchanged but still emits a frame.
// Unknown command strings are ignored and do not emit frames.
//
// The returned vector should contain:
//   * one initial "start" frame
//   * one additional frame after every valid "insert", "erase", or "rehash"
//     command
//   * one additional frame for invalid rehash(0)
//   * no frame for unknown command strings
std::vector<HashMapFrame> BuildHashMapFrames(
    const std::vector<HashCommand>& commands,
    std::size_t initial_bucket_count = 4);

#endif  // HASH_MAP_VIZ_H
