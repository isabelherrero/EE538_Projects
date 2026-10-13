#include "q.h"

#include <string>
#include <vector>

// TODO:
// 1. Replay the commands using vector buckets.
// 2. Emit one frame for the starting state and one frame after every command.
// 3. Match the label strings documented in q.h exactly.

namespace {

using Buckets = std::vector<std::vector<HashMapEntry>>;

std::size_t NormalizeBucketCount(std::size_t bucket_count) {
  return bucket_count == 0 ? 1 : bucket_count;
}

std::size_t BucketIndexFor(const std::string& key, std::size_t bucket_count) {
  return std::hash<std::string>{}(key) % bucket_count;
}

HashMapFrame MakeFrame(const Buckets& buckets, std::size_t size,
                        std::string label) {
  HashMapFrame frame;
  frame.buckets = buckets;
  frame.label = std::move(label);
  frame.size = size;
  return frame;
}

std::string ApplyInsert(Buckets& buckets, std::size_t& size,
                         const std::string& key, int value) {
  auto& bucket = buckets[BucketIndexFor(key, buckets.size())];

  for (auto& entry : bucket) {
    if (entry.key == key) {
      entry.value = value;
      return "insert(\"" + key + "\", " + std::to_string(value) +
             ") [overwrite]";
    }
  }

  bucket.push_back({key, value});
  ++size;
  return "insert(\"" + key + "\", " + std::to_string(value) + ")";
}

std::string ApplyErase(Buckets& buckets, std::size_t& size,
                        const std::string& key) {
  auto& bucket = buckets[BucketIndexFor(key, buckets.size())];

  for (auto it = bucket.begin(); it != bucket.end(); ++it) {
    if (it->key == key) {
      bucket.erase(it);
      --size;
      return "erase(\"" + key + "\")";
    }
  }
  return "erase(\"" + key + "\") [missing]";
}

std::string ApplyRehash(Buckets& buckets, std::size_t new_bucket_count) {
  if (new_bucket_count == 0) {
    return "rehash(0) [invalid]";
  }

  Buckets new_buckets(new_bucket_count);
  for (const auto& bucket : buckets) {
    for (const auto& entry : bucket) {
      new_buckets[BucketIndexFor(entry.key, new_bucket_count)]
          .push_back(entry);
    }
  }
  buckets = std::move(new_buckets);
  return "rehash(" + std::to_string(new_bucket_count) + ")";
}

}

std::vector<HashMapFrame> BuildHashMapFrames(
    const std::vector<HashCommand>& commands,
    std::size_t initial_bucket_count) {
  Buckets buckets(NormalizeBucketCount(initial_bucket_count));
  std::size_t size = 0;

  std::vector<HashMapFrame> frames;
  frames.push_back(MakeFrame(buckets, size, "start"));

  for (const auto& command : commands) {
    std::string label;

    if (command.op == "insert") {
      label = ApplyInsert(buckets, size, command.key, command.value);
    } else if (command.op == "erase") {
      label = ApplyErase(buckets, size, command.key);
    } else if (command.op == "rehash") {
      label = ApplyRehash(buckets, command.bucket_count);
    } else {
      continue;
    }

    frames.push_back(MakeFrame(buckets, size, std::move(label)));
  }

  return frames;
}
