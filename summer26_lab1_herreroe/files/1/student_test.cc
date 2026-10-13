#include <stdexcept>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

TEST(VectorHashMapStudentTest, StartsEmpty) {
  VectorHashMap map(4);

  EXPECT_TRUE(map.Empty());
  EXPECT_EQ(map.Size(), 0);
  EXPECT_DOUBLE_EQ(map.LoadFactor(), 0.0);
  EXPECT_FALSE(map.Contains("missing"));
}

TEST(VectorHashMapStudentTest, InsertsAndGetsValues) {
  VectorHashMap map(4);

  EXPECT_TRUE(map.Insert("usc", 1880));
  EXPECT_FALSE(map.Empty());
  EXPECT_EQ(map.Size(), 1);
  EXPECT_TRUE(map.Contains("usc"));
  EXPECT_EQ(map.Get("usc"), 1880);
}

TEST(VectorHashMapStudentTest, OverwritesExistingKeyWithoutGrowing) {
  VectorHashMap map(4);

  EXPECT_TRUE(map.Insert("course", 538));
  EXPECT_FALSE(map.Insert("course", 599));

  EXPECT_EQ(map.Size(), 1);
  EXPECT_EQ(map.Get("course"), 599);
}

TEST(VectorHashMapStudentTest, MissingGetThrows) {
  VectorHashMap map(4);

  EXPECT_THROW(map.Get("missing"), std::out_of_range);
}

TEST(VectorHashMapStudentTest, ErasesExistingAndMissingKeys) {
  VectorHashMap map(4);
  map.Insert("a", 1);
  map.Insert("b", 2);

  EXPECT_TRUE(map.Erase("a"));
  EXPECT_FALSE(map.Contains("a"));
  EXPECT_EQ(map.Size(), 1);
  EXPECT_FALSE(map.Erase("a"));
  EXPECT_EQ(map.Get("b"), 2);
}

TEST(VectorHashMapStudentTest, RehashPreservesEntries) {
  VectorHashMap map(2);
  map.Insert("alpha", 1);
  map.Insert("beta", 2);
  map.Insert("gamma", 3);

  map.Rehash(16);

  EXPECT_EQ(map.Size(), 3);
  EXPECT_EQ(map.Get("alpha"), 1);
  EXPECT_EQ(map.Get("beta"), 2);
  EXPECT_EQ(map.Get("gamma"), 3);
  EXPECT_DOUBLE_EQ(map.LoadFactor(), 3.0 / 16.0);
}

TEST(VectorHashMapStudentTest, ZeroBucketInputsUseOneBucket) {
  VectorHashMap map(0);
  EXPECT_TRUE(map.Insert("safe", 10));
  EXPECT_EQ(map.Get("safe"), 10);
  EXPECT_DOUBLE_EQ(map.LoadFactor(), 1.0);

  map.Rehash(0);
  EXPECT_EQ(map.Get("safe"), 10);
  EXPECT_DOUBLE_EQ(map.LoadFactor(), 1.0);
}
