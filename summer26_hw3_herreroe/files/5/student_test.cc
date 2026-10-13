#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------

TEST(MyVectorConstructorTest, DefaultConstructorIsEmpty) {
  MyVector v;
  EXPECT_EQ(v.size(), 0);
}

TEST(MyVectorConstructorTest, SizedConstructorSetsSize) {
  MyVector v(5);
  EXPECT_EQ(v.size(), 5);
}

TEST(MyVectorConstructorTest, SizedConstructorWithZeroIsEmpty) {
  MyVector v(0);
  EXPECT_EQ(v.size(), 0);
}

TEST(MyVectorConstructorTest, SizedConstructorWithNegativeSizeIsEmpty) {
  MyVector v(-3);
  EXPECT_EQ(v.size(), 0);
}

TEST(MyVectorCopyConstructorTest, CopyHasSameContents) {
  MyVector v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  MyVector copy(v);
  EXPECT_EQ(copy.size(), 3);
  EXPECT_EQ(copy.ConvertToStdVector(), v.ConvertToStdVector());
}

TEST(MyVectorCopyConstructorTest, CopyIsIndependentOfOriginal) {
  MyVector v;
  v.push_back(1);
  v.push_back(2);
  MyVector copy(v);
  copy.push_back(3);
  v.pop_back();
  EXPECT_EQ(v.ConvertToStdVector(), std::vector<int>({1}));
  EXPECT_EQ(copy.ConvertToStdVector(), std::vector<int>({1, 2, 3}));
}

TEST(MyVectorCopyConstructorTest, CopyOfEmptyVectorIsEmpty) {
  MyVector v;
  MyVector copy(v);
  EXPECT_EQ(copy.size(), 0);
}

TEST(MyVectorCopyConstructorTest, CopyDoesNotGetSourceErrorState) {
  MyVector v;
  v.pop_back();
  EXPECT_EQ(v.get_error(), ErrorCode::kPopFromEmptyVector);
  MyVector copy(v);
  EXPECT_EQ(copy.get_error(), ErrorCode::kNoError);
}

TEST(MyVectorPushPopBackTest, PushBackIncreasesSizeAndAppendsInOrder) {
  MyVector v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v.ConvertToStdVector(), std::vector<int>({1, 2, 3}));
}

TEST(MyVectorPushPopBackTest, PopBackReturnsLastValueAndShrinks) {
  MyVector v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  EXPECT_EQ(v.pop_back(), 3);
  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(v.ConvertToStdVector(), std::vector<int>({1, 2}));
  EXPECT_EQ(v.get_error(), ErrorCode::kNoError);
}

TEST(MyVectorPushPopBackTest, PopBackOnEmptyVectorSetsError) {
  MyVector v;
  int result = v.pop_back();
  EXPECT_EQ(result, -1);
  EXPECT_EQ(v.get_error(), ErrorCode::kPopFromEmptyVector);
  EXPECT_EQ(v.size(), 0);
}

TEST(MyVectorPushPopBackTest, PopBackDownToEmptyThenAgainFails) {
  MyVector v;
  v.push_back(42);
  EXPECT_EQ(v.pop_back(), 42);
  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.pop_back(), -1);
  EXPECT_EQ(v.get_error(), ErrorCode::kPopFromEmptyVector);
}

TEST(MyVectorPushPopBackTest, PushBackWorksAgainAfterFullyDraining) {
  MyVector v;
  v.push_back(1);
  v.pop_back();
  EXPECT_EQ(v.size(), 0);
  v.push_back(99);
  EXPECT_EQ(v.size(), 1);
  EXPECT_EQ(v.ConvertToStdVector(), std::vector<int>({99}));
}

TEST(MyVectorPushPopFrontTest, PushFrontInsertsAtBeginning) {
  MyVector v;
  v.push_back(1);
  v.push_back(2);
  v.push_front(0);
  EXPECT_EQ(v.ConvertToStdVector(), std::vector<int>({0, 1, 2}));
}

TEST(MyVectorPushPopFrontTest, PopFrontReturnsFirstValueAndShifts) {
  MyVector v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  EXPECT_EQ(v.pop_front(), 1);
  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(v.ConvertToStdVector(), std::vector<int>({2, 3}));
  EXPECT_EQ(v.get_error(), ErrorCode::kNoError);
}

TEST(MyVectorPushPopFrontTest, PopFrontOnEmptyVectorSetsError) {
  MyVector v;
  int result = v.pop_front();
  EXPECT_EQ(result, -1);
  EXPECT_EQ(v.get_error(), ErrorCode::kPopFromEmptyVector);
  EXPECT_EQ(v.size(), 0);
}

TEST(MyVectorPushPopFrontTest, PopFrontDownToEmptyThenAgainFails) {
  MyVector v;
  v.push_front(42);
  EXPECT_EQ(v.pop_front(), 42);
  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.pop_front(), -1);
  EXPECT_EQ(v.get_error(), ErrorCode::kPopFromEmptyVector);
}

TEST(MyVectorPushPopFrontTest, PushFrontWorksAgainAfterFullyDraining) {
  MyVector v;
  v.push_front(1);
  v.pop_front();
  EXPECT_EQ(v.size(), 0);
  v.push_front(7);
  EXPECT_EQ(v.ConvertToStdVector(), std::vector<int>({7}));
}

TEST(MyVectorInsertTest, InsertAtNegativeOneInsertsAtFront) {
  MyVector v;
  v.push_back(1);
  v.push_back(2);
  v.insert(0, -1);
  EXPECT_EQ(v.ConvertToStdVector(), std::vector<int>({0, 1, 2}));
  EXPECT_EQ(v.get_error(), ErrorCode::kNoError);
}

TEST(MyVectorInsertTest, InsertIntoEmptyVectorAtNegativeOne) {
  MyVector v;
  v.insert(5, -1);
  EXPECT_EQ(v.size(), 1);
  EXPECT_EQ(v.ConvertToStdVector(), std::vector<int>({5}));
  EXPECT_EQ(v.get_error(), ErrorCode::kNoError);
}

TEST(MyVectorInsertTest, InsertAfterMiddleIndex) {
  MyVector v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(4);
  v.insert(3, 1);
  EXPECT_EQ(v.ConvertToStdVector(), std::vector<int>({1, 2, 3, 4}));
}

TEST(MyVectorInsertTest, InsertAfterLastValidIndexAppendsToEnd) {
  MyVector v;
  v.push_back(1);
  v.push_back(2);
  v.insert(3, 1);
  EXPECT_EQ(v.ConvertToStdVector(), std::vector<int>({1, 2, 3}));
}

TEST(MyVectorInsertTest, InsertWithIndexTooLowIsInvalid) {
  MyVector v;
  v.push_back(1);
  v.insert(99, -2);
  EXPECT_EQ(v.get_error(), ErrorCode::kIndexError);
  EXPECT_EQ(v.ConvertToStdVector(), std::vector<int>({1}));
}

TEST(MyVectorInsertTest, InsertWithIndexTooHighIsInvalid) {
  MyVector v;
  v.push_back(1);
  v.push_back(2);
  v.insert(99, 2);
  EXPECT_EQ(v.get_error(), ErrorCode::kIndexError);
  EXPECT_EQ(v.ConvertToStdVector(), std::vector<int>({1, 2}));
}

TEST(MyVectorInsertTest, InsertIntoEmptyVectorWithNonNegativeIndexIsInvalid) {
  MyVector v;
  v.insert(1, 0);
  EXPECT_EQ(v.get_error(), ErrorCode::kIndexError);
  EXPECT_EQ(v.size(), 0);
}

TEST(MyVectorAtTest, AtReturnsCorrectValueForValidIndex) {
  MyVector v;
  v.push_back(10);
  v.push_back(20);
  v.push_back(30);
  EXPECT_EQ(v.at(0), 10);
  EXPECT_EQ(v.at(2), 30);
  EXPECT_EQ(v.get_error(), ErrorCode::kNoError);
}

TEST(MyVectorAtTest, AtWithNegativeIndexSetsError) {
  MyVector v;
  v.push_back(1);
  int result = v.at(-1);
  EXPECT_EQ(result, -1);
  EXPECT_EQ(v.get_error(), ErrorCode::kIndexError);
}

TEST(MyVectorAtTest, AtWithIndexEqualToSizeSetsError) {
  MyVector v;
  v.push_back(1);
  v.push_back(2);
  int result = v.at(2);
  EXPECT_EQ(result, -1);
  EXPECT_EQ(v.get_error(), ErrorCode::kIndexError);
}

TEST(MyVectorAtTest, AtOnEmptyVectorSetsError) {
  MyVector v;
  int result = v.at(0);
  EXPECT_EQ(result, -1);
  EXPECT_EQ(v.get_error(), ErrorCode::kIndexError);
}

TEST(MyVectorFindTest, FindsItemAtFront) {
  MyVector v;
  v.push_back(5);
  v.push_back(6);
  v.push_back(7);
  EXPECT_EQ(v.find(5), 0);
  EXPECT_EQ(v.get_error(), ErrorCode::kNoError);
}

TEST(MyVectorFindTest, FindsItemInMiddle) {
  MyVector v;
  v.push_back(5);
  v.push_back(6);
  v.push_back(7);
  EXPECT_EQ(v.find(6), 1);
}

TEST(MyVectorFindTest, FindsItemAtBack) {
  MyVector v;
  v.push_back(5);
  v.push_back(6);
  v.push_back(7);
  EXPECT_EQ(v.find(7), 2);
}

TEST(MyVectorFindTest, FindReturnsFirstOccurrenceForDuplicates) {
  MyVector v;
  v.push_back(9);
  v.push_back(1);
  v.push_back(9);
  EXPECT_EQ(v.find(9), 0);
}

TEST(MyVectorFindTest, FindItemNotPresentSetsError) {
  MyVector v;
  v.push_back(1);
  v.push_back(2);
  int result = v.find(999);
  EXPECT_EQ(result, -1);
  EXPECT_EQ(v.get_error(), ErrorCode::kNotFound);
}

TEST(MyVectorFindTest, FindOnEmptyVectorSetsError) {
  MyVector v;
  int result = v.find(1);
  EXPECT_EQ(result, -1);
  EXPECT_EQ(v.get_error(), ErrorCode::kNotFound);
}

TEST(MyVectorErrorStateTest, SuccessfulOpClearsPreviousError) {
  MyVector v;
  v.pop_back();
  EXPECT_EQ(v.get_error(), ErrorCode::kPopFromEmptyVector);
  v.push_back(1);
  EXPECT_EQ(v.get_error(), ErrorCode::kNoError);
}

TEST(MyVectorErrorStateTest, ErrorStateTracksMostRecentOperationOnly) {
  MyVector v;
  v.push_back(1);
  v.push_back(2);
  v.at(50);
  EXPECT_EQ(v.get_error(), ErrorCode::kIndexError);
  v.find(1);
  EXPECT_EQ(v.get_error(), ErrorCode::kNoError);
  v.find(999);
  EXPECT_EQ(v.get_error(), ErrorCode::kNotFound);
  v.insert(3, 0);
  EXPECT_EQ(v.get_error(), ErrorCode::kNoError);
}