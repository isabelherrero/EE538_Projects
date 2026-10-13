#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------

TEST(SizedMapBasicTest, NewMapIsEmpty) {
  SizedMap sm(5);
  EXPECT_EQ(sm.Size(), 0);
}

TEST(SizedMapBasicTest, GetOnMissingKeyReturnsInvalidKey) {
  SizedMap sm(5);
  EXPECT_EQ(sm.Get(1), "INVALID_KEY");
}

TEST(SizedMapBasicTest, PutThenGetReturnsValue) {
  SizedMap sm(5);
  sm.Put(1, "one");
  EXPECT_EQ(sm.Get(1), "one");
}

TEST(SizedMapBasicTest, GetOnKeyNeverInsertedReturnsInvalidKey) {
  SizedMap sm(5);
  sm.Put(1, "one");
  EXPECT_EQ(sm.Get(2), "INVALID_KEY");
}

TEST(SizedMapBasicTest, SizeIncreasesWithDistinctPuts) {
  SizedMap sm(5);
  sm.Put(1, "one");
  sm.Put(2, "two");
  EXPECT_EQ(sm.Size(), 2);
}

TEST(SizedMapBasicTest, PutSameKeyTwiceUpdatesValueWithoutGrowingSize) {
  SizedMap sm(5);
  sm.Put(1, "one");
  sm.Put(1, "uno");
  EXPECT_EQ(sm.Size(), 1);
  EXPECT_EQ(sm.Get(1), "uno");
}

TEST(SizedMapEvictionTest, MatchesSpecExample) {
  SizedMap sm(2);
  sm.Put(1, "one");
  sm.Put(2, "two");
  sm.Put(3, "three");
  EXPECT_EQ(sm.Size(), 2);
  EXPECT_EQ(sm.Get(1), "INVALID_KEY");
  EXPECT_EQ(sm.Get(2), "two");
  EXPECT_EQ(sm.Get(3), "three");
}

TEST(SizedMapEvictionTest, SizeNeverExceedsCapacity) {
  SizedMap sm(3);
  for (int i = 0; i < 10; i++) {
    sm.Put(i, "value");
    EXPECT_LE(sm.Size(), 3);
  }
  EXPECT_EQ(sm.Size(), 3);
}

TEST(SizedMapEvictionTest, EvictionIsStrictlyFifoAcrossManyInserts) {
  SizedMap sm(3);
  sm.Put(1, "one");
  sm.Put(2, "two");
  sm.Put(3, "three");
  sm.Put(4, "four");
  sm.Put(5, "five");
  EXPECT_EQ(sm.Get(1), "INVALID_KEY");
  EXPECT_EQ(sm.Get(2), "INVALID_KEY");
  EXPECT_EQ(sm.Get(3), "three");
  EXPECT_EQ(sm.Get(4), "four");
  EXPECT_EQ(sm.Get(5), "five");
}

TEST(SizedMapEvictionTest, CapacityOneEvictsImmediatelyOnNewKey) {
  SizedMap sm(1);
  sm.Put(1, "one");
  sm.Put(2, "two");
  EXPECT_EQ(sm.Size(), 1);
  EXPECT_EQ(sm.Get(1), "INVALID_KEY");
  EXPECT_EQ(sm.Get(2), "two");
}

TEST(SizedMapEvictionTest, UpdatingExistingKeyDoesNotResetFifoPosition) {
  SizedMap sm(2);
  sm.Put(1, "one");
  sm.Put(2, "two");
  sm.Put(1, "one-updated");
  sm.Put(3, "three");
  EXPECT_EQ(sm.Get(1), "INVALID_KEY");
  EXPECT_EQ(sm.Get(2), "two");
  EXPECT_EQ(sm.Get(3), "three");
}

TEST(SizedMapEvictionTest, MapUsableAfterEviction) {
  SizedMap sm(2);
  sm.Put(1, "one");
  sm.Put(2, "two");
  sm.Put(3, "three");
  sm.Put(2, "two-updated");
  EXPECT_EQ(sm.Size(), 2);
  EXPECT_EQ(sm.Get(2), "two-updated");
  EXPECT_EQ(sm.Get(3), "three");
}

TEST(SizedMapCopyConstructorTest, CopyHasSameContents) {
  SizedMap sm(5);
  sm.Put(1, "one");
  sm.Put(2, "two");
  SizedMap copy(sm);
  EXPECT_EQ(copy.Size(), 2);
  EXPECT_EQ(copy.Get(1), "one");
  EXPECT_EQ(copy.Get(2), "two");
}

TEST(SizedMapCopyConstructorTest, CopyIsIndependentOfOriginal) {
  SizedMap sm(5);
  sm.Put(1, "one");
  SizedMap copy(sm);
  copy.Put(2, "two");
  sm.Put(3, "three");
  EXPECT_EQ(sm.Size(), 2);
  EXPECT_EQ(sm.Get(2), "INVALID_KEY");
  EXPECT_EQ(sm.Get(3), "three");
  EXPECT_EQ(copy.Size(), 2);
  EXPECT_EQ(copy.Get(2), "two");
  EXPECT_EQ(copy.Get(3), "INVALID_KEY");
}

TEST(SizedMapCopyConstructorTest, CopyPreservesFifoOrderForEviction) {
  SizedMap sm(2);
  sm.Put(1, "one");
  sm.Put(2, "two");
  SizedMap copy(sm);
  copy.Put(3, "three");
  EXPECT_EQ(copy.Get(1), "INVALID_KEY");
  EXPECT_EQ(copy.Get(2), "two");
  EXPECT_EQ(copy.Get(3), "three");
  EXPECT_EQ(sm.Size(), 2);
  EXPECT_EQ(sm.Get(1), "one");
}

TEST(SizedMapCopyConstructorTest, CopyOfEmptyMapIsEmpty) {
  SizedMap sm(5);
  SizedMap copy(sm);
  EXPECT_EQ(copy.Size(), 0);
}

TEST(SizedMapOperatorPlusTest, MatchesSpecExample) {
  SizedMap sm1(2);
  sm1.Put(1, "one");
  SizedMap sm2(3);
  sm2.Put(2, "two");
  sm2.Put(3, "three");
  SizedMap sm3 = sm1 + sm2;
  EXPECT_EQ(sm3.Size(), 3);
  EXPECT_EQ(sm3.Get(1), "one");
  EXPECT_EQ(sm3.Get(2), "two");
  EXPECT_EQ(sm3.Get(3), "three");
}

TEST(SizedMapOperatorPlusTest, CombinedCapacityIsSumOfBoth) {
  SizedMap sm1(2);
  sm1.Put(1, "one");
  sm1.Put(2, "two");
  SizedMap sm2(2);
  sm2.Put(4, "four");
  sm2.Put(5, "five");
  SizedMap sm3 = sm1 + sm2;
  EXPECT_EQ(sm3.Size(), 4);
  sm3.Put(6, "six");
  EXPECT_EQ(sm3.Size(), 4);
  EXPECT_EQ(sm3.Get(1), "INVALID_KEY");
  EXPECT_EQ(sm3.Get(2), "two");
  EXPECT_EQ(sm3.Get(4), "four");
  EXPECT_EQ(sm3.Get(5), "five");
  EXPECT_EQ(sm3.Get(6), "six");
}

TEST(SizedMapOperatorPlusTest, FifoOrderIsFirstMapThenSecondMap) {
  SizedMap sm1(2);
  sm1.Put(1, "one");
  sm1.Put(2, "two");
  SizedMap sm2(2);
  sm2.Put(4, "four");
  sm2.Put(5, "five");
  SizedMap sm3 = sm1 + sm2;
  sm3.Put(6, "six");  // evicts 1
  EXPECT_EQ(sm3.Get(1), "INVALID_KEY");
  sm3.Put(7, "seven");  // evicts 2
  EXPECT_EQ(sm3.Get(2), "INVALID_KEY");
  EXPECT_EQ(sm3.Get(4), "four");
  EXPECT_EQ(sm3.Get(5), "five");
}

TEST(SizedMapOperatorPlusTest, OverlappingKeyUsesSecondMapValueButFirstMapPosition) {
  SizedMap sm1(2);
  sm1.Put(1, "one");
  sm1.Put(2, "two");
  SizedMap sm2(2);
  sm2.Put(2, "TWO-FROM-SM2");
  sm2.Put(3, "three");
  SizedMap sm3 = sm1 + sm2;
  EXPECT_EQ(sm3.Get(2), "TWO-FROM-SM2");
  EXPECT_EQ(sm3.Size(), 3);
  sm3.Put(50, "a");
  EXPECT_EQ(sm3.Size(), 4);
  EXPECT_EQ(sm3.Get(1), "one");
  sm3.Put(51, "b");
  EXPECT_EQ(sm3.Get(1), "INVALID_KEY");
  sm3.Put(52, "c");
  EXPECT_EQ(sm3.Get(2), "INVALID_KEY");
  EXPECT_EQ(sm3.Get(3), "three");
}

TEST(SizedMapOperatorPlusTest, FirstMapEmpty) {
  SizedMap sm1(2);
  SizedMap sm2(2);
  sm2.Put(1, "one");
  SizedMap sm3 = sm1 + sm2;
  EXPECT_EQ(sm3.Size(), 1);
  EXPECT_EQ(sm3.Get(1), "one");
}

TEST(SizedMapOperatorPlusTest, SecondMapEmpty) {
  SizedMap sm1(2);
  sm1.Put(1, "one");
  SizedMap sm2(2);
  SizedMap sm3 = sm1 + sm2;
  EXPECT_EQ(sm3.Size(), 1);
  EXPECT_EQ(sm3.Get(1), "one");
}

TEST(SizedMapOperatorPlusTest, BothMapsEmpty) {
  SizedMap sm1(2);
  SizedMap sm2(3);
  SizedMap sm3 = sm1 + sm2;
  EXPECT_EQ(sm3.Size(), 0);
}

TEST(SizedMapOperatorPlusTest, OperandsUnchangedAfterAddition) {
  SizedMap sm1(2);
  sm1.Put(1, "one");
  SizedMap sm2(2);
  sm2.Put(2, "two");
  SizedMap sm3 = sm1 + sm2;
  (void)sm3;
  EXPECT_EQ(sm1.Size(), 1);
  EXPECT_EQ(sm1.Get(1), "one");
  EXPECT_EQ(sm2.Size(), 1);
  EXPECT_EQ(sm2.Get(2), "two");
}

TEST(SizedMapOperatorPlusTest, ResultIsIndependentOfOperands) {
  SizedMap sm1(2);
  sm1.Put(1, "one");
  SizedMap sm2(2);
  sm2.Put(2, "two");
  SizedMap sm3 = sm1 + sm2;
  sm3.Put(3, "three");
  EXPECT_EQ(sm1.Size(), 1);
  EXPECT_EQ(sm2.Size(), 1);
}

TEST(SizedMapReverseTest, ReverseOnEmptyMapDoesNotCrash) {
  SizedMap sm(3);
  sm.Reverse();
  EXPECT_EQ(sm.Size(), 0);
}

TEST(SizedMapReverseTest, ReverseOnSingleElementIsNoOp) {
  SizedMap sm(2);
  sm.Put(1, "one");
  sm.Reverse();
  sm.Put(2, "two");
  sm.Put(3, "three");
  EXPECT_EQ(sm.Get(1), "INVALID_KEY");
  EXPECT_EQ(sm.Get(2), "two");
  EXPECT_EQ(sm.Get(3), "three");
}

TEST(SizedMapReverseTest, ReverseFlipsEvictionOrder) {
  SizedMap sm(2);
  sm.Put(1, "one");
  sm.Put(2, "two");
  sm.Reverse();
  sm.Put(3, "three");
  EXPECT_EQ(sm.Get(2), "INVALID_KEY");
  EXPECT_EQ(sm.Get(1), "one");
  EXPECT_EQ(sm.Get(3), "three");
}

TEST(SizedMapReverseTest, DoubleReverseRestoresOriginalOrder) {
  SizedMap sm(2);
  sm.Put(1, "one");
  sm.Put(2, "two");
  sm.Reverse();
  sm.Reverse();
  sm.Put(3, "three");
  EXPECT_EQ(sm.Get(1), "INVALID_KEY");
  EXPECT_EQ(sm.Get(2), "two");
}

TEST(SizedMapReverseTest, ValuesUnaffectedByReverse) {
  SizedMap sm(3);
  sm.Put(1, "one");
  sm.Put(2, "two");
  sm.Reverse();
  EXPECT_EQ(sm.Get(1), "one");
  EXPECT_EQ(sm.Get(2), "two");
  EXPECT_EQ(sm.Size(), 2);
}