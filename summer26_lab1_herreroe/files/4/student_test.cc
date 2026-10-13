#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "q.h"

TEST(HashMapVizStudentTest, StartsWithEmptyFrame) {
  const auto frames = BuildHashMapFrames({}, 4);

  ASSERT_EQ(frames.size(), 1);
  EXPECT_EQ(frames[0].label, "start");
  EXPECT_EQ(frames[0].size, 0);
  EXPECT_EQ(frames[0].buckets.size(), 4);
}

TEST(HashMapVizStudentTest, InsertAddsFrameAndEntry) {
  const auto frames = BuildHashMapFrames({{"insert", "alpha", 1, 0}}, 4);

  ASSERT_EQ(frames.size(), 2);
  EXPECT_EQ(frames[1].label, "insert(\"alpha\", 1)");
  EXPECT_EQ(frames[1].size, 1);

  int found = 0;
  for (const auto& bucket : frames[1].buckets) {
    for (const auto& entry : bucket) {
      if (entry.key == "alpha" && entry.value == 1) {
        ++found;
      }
    }
  }
  EXPECT_EQ(found, 1);
}

TEST(HashMapVizStudentTest, OverwriteDoesNotGrowSize) {
  const std::vector<HashCommand> commands = {
      {"insert", "alpha", 1, 0},
      {"insert", "alpha", 7, 0},
  };

  const auto frames = BuildHashMapFrames(commands, 4);

  ASSERT_EQ(frames.size(), 3);
  EXPECT_EQ(frames[2].label, "insert(\"alpha\", 7) [overwrite]");
  EXPECT_EQ(frames[2].size, 1);
}

TEST(HashMapVizStudentTest, RehashPreservesEntries) {
  const std::vector<HashCommand> commands = {
      {"insert", "alpha", 1, 0},
      {"insert", "beta", 2, 0},
      {"rehash", "", 0, 8},
  };

  const auto frames = BuildHashMapFrames(commands, 2);

  ASSERT_EQ(frames.size(), 4);
  EXPECT_EQ(frames[3].label, "rehash(8)");
  EXPECT_EQ(frames[3].size, 2);
  EXPECT_EQ(frames[3].buckets.size(), 8);
}

TEST(HashMapVizStudentTest, InvalidRehashEmitsFrameWithoutChangingBuckets) {
  const std::vector<HashCommand> commands = {
      {"insert", "alpha", 1, 0},
      {"rehash", "", 0, 0},
  };

  const auto frames = BuildHashMapFrames(commands, 4);

  ASSERT_EQ(frames.size(), 3);
  EXPECT_EQ(frames[2].label, "rehash(0) [invalid]");
  EXPECT_EQ(frames[2].size, 1);
  EXPECT_EQ(frames[2].buckets.size(), 4);
}
