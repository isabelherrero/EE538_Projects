#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------

TEST(SinglyLinkedListTest, DefaultConstructorIsEmpty) {
  SinglyLinkedList list;
  EXPECT_TRUE(list.empty());
  EXPECT_EQ(list.size(), 0);
  EXPECT_EQ(list.head(), nullptr);
  EXPECT_EQ(list.back(), -1);
}

TEST(SinglyLinkedListTest, VectorConstructorBuildsCorrectList) {
  std::vector<int> v = {1, 4, 5, 6, 10};
  SinglyLinkedList list(v);
  EXPECT_EQ(list.size(), 5);
  ASSERT_NE(list.head(), nullptr);
  EXPECT_EQ(list.head()->val, 1);
  EXPECT_EQ(list.convert_to_vector(), v);
}

TEST(SinglyLinkedListTest, VectorConstructorWithEmptyVector) {
  std::vector<int> v;
  SinglyLinkedList list(v);
  EXPECT_TRUE(list.empty());
  EXPECT_EQ(list.head(), nullptr);
}

TEST(SinglyLinkedListTest, VectorConstructorWithSingleElement) {
  std::vector<int> v = {42};
  SinglyLinkedList list(v);
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list.head()->val, 42);
  EXPECT_EQ(list.back(), 42);
}

TEST(SinglyLinkedListTest, CopyConstructorProducesEqualButDistinctList) {
  std::vector<int> v = {1, 2, 3};
  SinglyLinkedList original(v);
  SinglyLinkedList copy(original);

  EXPECT_EQ(copy.convert_to_vector(), v);
  EXPECT_NE(copy.head(), original.head());

  copy.push_back(4);
  EXPECT_EQ(copy.size(), 4);
  EXPECT_EQ(original.size(), 3);
}

TEST(SinglyLinkedListTest, CopyConstructorOfEmptyList) {
  SinglyLinkedList original;
  SinglyLinkedList copy(original);
  EXPECT_TRUE(copy.empty());
}

TEST(SinglyLinkedListTest, PushBackOnEmptyList) {
  SinglyLinkedList list;
  list.push_back(42);
  EXPECT_EQ(list.size(), 1);
  ASSERT_NE(list.head(), nullptr);
  EXPECT_EQ(list.head()->val, 42);
  EXPECT_EQ(list.back(), 42);
}

TEST(SinglyLinkedListTest, PushBackMultipleMaintainsOrder) {
  SinglyLinkedList list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  EXPECT_EQ(list.convert_to_vector(), (std::vector<int>{1, 2, 3}));
  EXPECT_EQ(list.back(), 3);
}

TEST(SinglyLinkedListTest, PopBackOnEmptyListReturnsFalse) {
  SinglyLinkedList list;
  EXPECT_FALSE(list.pop_back());
}

TEST(SinglyLinkedListTest, PopBackOnSingleElementList) {
  SinglyLinkedList list;
  list.push_back(5);
  EXPECT_TRUE(list.pop_back());
  EXPECT_TRUE(list.empty());
  EXPECT_EQ(list.head(), nullptr);
}

TEST(SinglyLinkedListTest, PopBackOnMultiElementList) {
  std::vector<int> v = {1, 2, 3, 4};
  SinglyLinkedList list(v);
  EXPECT_TRUE(list.pop_back());
  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(list.convert_to_vector(), (std::vector<int>{1, 2, 3}));
  EXPECT_EQ(list.back(), 3);
}

TEST(SinglyLinkedListTest, PopBackRepeatedlyUntilEmpty) {
  std::vector<int> v = {1, 2};
  SinglyLinkedList list(v);
  EXPECT_TRUE(list.pop_back());
  EXPECT_TRUE(list.pop_back());
  EXPECT_TRUE(list.empty());
  EXPECT_FALSE(list.pop_back());
}

TEST(SinglyLinkedListTest, GetIthPointerValidIndices) {
  std::vector<int> v = {10, 20, 30};
  SinglyLinkedList list(v);
  ASSERT_NE(list.GetIthPointer(0), nullptr);
  EXPECT_EQ(list.GetIthPointer(0)->val, 10);
  EXPECT_EQ(list.GetIthPointer(2)->val, 30);
}

TEST(SinglyLinkedListTest, GetIthPointerInvalidIndices) {
  std::vector<int> v = {10, 20, 30};
  SinglyLinkedList list(v);
  EXPECT_EQ(list.GetIthPointer(-1), nullptr);
  EXPECT_EQ(list.GetIthPointer(3), nullptr);
  EXPECT_EQ(list.GetIthPointer(100), nullptr);
}

TEST(SinglyLinkedListTest, GetIthPointerOnEmptyList) {
  SinglyLinkedList list;
  EXPECT_EQ(list.GetIthPointer(0), nullptr);
}

TEST(SinglyLinkedListTest, GetBackPointerEmptyAndNonEmpty) {
  SinglyLinkedList list;
  EXPECT_EQ(list.GetBackPointer(), nullptr);
  list.push_back(7);
  EXPECT_EQ(list.GetBackPointer()->val, 7);
  list.push_back(8);
  EXPECT_EQ(list.GetBackPointer()->val, 8);
}

TEST(SinglyLinkedListTest, OperatorBracketValidIndices) {
  std::vector<int> v = {10, 20, 30};
  SinglyLinkedList list(v);
  EXPECT_EQ(list[0], 10);
  EXPECT_EQ(list[2], 30);
}

TEST(SinglyLinkedListTest, OperatorBracketAllowsMutation) {
  std::vector<int> v = {10, 20, 30};
  SinglyLinkedList list(v);
  list[1] = 99;
  EXPECT_EQ(list.convert_to_vector(), (std::vector<int>{10, 99, 30}));
}

TEST(SinglyLinkedListTest, OperatorBracketInvalidIndicesReturnMinusOne) {
  std::vector<int> v = {10, 20, 30};
  SinglyLinkedList list(v);
  EXPECT_EQ(list[-1], -1);
  EXPECT_EQ(list[100], -1);
}

TEST(SinglyLinkedListTest, ConvertToVectorMatchesInput) {
  std::vector<int> v = {1, 4, 5, 6, 10};
  SinglyLinkedList list(v);
  EXPECT_EQ(list.convert_to_vector(), v);
}

TEST(SinglyLinkedListTest, ConvertToVectorOnEmptyListIsEmpty) {
  SinglyLinkedList list;
  EXPECT_TRUE(list.convert_to_vector().empty());
}

TEST(SinglyLinkedListTest, EraseByIndexMiddleElement) {
  std::vector<int> v = {1, 5, 10, 20};
  SinglyLinkedList list(v);
  ListNode *result = list.erase(2);
  EXPECT_EQ(list.convert_to_vector(), (std::vector<int>{1, 5, 20}));
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->val, 5);
  EXPECT_EQ(list.size(), 3);
}

TEST(SinglyLinkedListTest, EraseByIndexHeadElement) {
  std::vector<int> v = {1, 5, 10, 20};
  SinglyLinkedList list(v);
  ListNode *result = list.erase(0);
  EXPECT_EQ(list.convert_to_vector(), (std::vector<int>{5, 10, 20}));
  EXPECT_EQ(result, nullptr);
  EXPECT_EQ(list.head()->val, 5);
}

TEST(SinglyLinkedListTest, EraseByIndexTailElement) {
  std::vector<int> v = {1, 5, 10, 20};
  SinglyLinkedList list(v);
  ListNode *result = list.erase(3);
  EXPECT_EQ(list.convert_to_vector(), (std::vector<int>{1, 5, 10}));
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->val, 10);
  EXPECT_EQ(list.back(), 10);
}

TEST(SinglyLinkedListTest, EraseByIndexSingleElementList) {
  std::vector<int> v = {42};
  SinglyLinkedList list(v);
  ListNode *result = list.erase(0);
  EXPECT_EQ(result, nullptr);
  EXPECT_TRUE(list.empty());
}

TEST(SinglyLinkedListTest, EraseByIndexOutOfRangeDoesNotChangeList) {
  std::vector<int> v = {1, 2, 3};
  SinglyLinkedList list(v);
  EXPECT_EQ(list.erase(-1), nullptr);
  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(list.erase(100), nullptr);
  EXPECT_EQ(list.size(), 3);
}

TEST(SinglyLinkedListTest, EraseByIndexOnEmptyList) {
  SinglyLinkedList list;
  EXPECT_EQ(list.erase(0), nullptr);
}

TEST(SinglyLinkedListTest, GetPreviousOfHeadIsNullptr) {
  std::vector<int> v = {1, 2, 3, 4};
  SinglyLinkedList list(v);
  EXPECT_EQ(list.GetPrevious(list.GetIthPointer(0)), nullptr);
}

TEST(SinglyLinkedListTest, GetPreviousOfMiddleAndTailElements) {
  std::vector<int> v = {1, 2, 3, 4};
  SinglyLinkedList list(v);
  ListNode *n0 = list.GetIthPointer(0);
  ListNode *n1 = list.GetIthPointer(1);
  ListNode *n2 = list.GetIthPointer(2);
  EXPECT_EQ(list.GetPrevious(n1), n0);
  EXPECT_EQ(list.GetPrevious(n2), n1);
}

TEST(SinglyLinkedListTest, GetPreviousOfNullptrIsNullptr) {
  std::vector<int> v = {1, 2, 3};
  SinglyLinkedList list(v);
  EXPECT_EQ(list.GetPrevious(nullptr), nullptr);
}

TEST(SinglyLinkedListTest, GetPreviousOfForeignNodeIsNullptr) {
  std::vector<int> v = {1, 2, 3};
  SinglyLinkedList list(v);
  SinglyLinkedList other(std::vector<int>{99, 100});
  EXPECT_EQ(list.GetPrevious(other.head()), nullptr);
}

TEST(SinglyLinkedListTest, ErasePointerMiddleElement) {
  std::vector<int> v = {1, 5, 10, 20};
  SinglyLinkedList list(v);
  ListNode *target = list.GetIthPointer(2);
  ListNode *result = list.erase(target);
  EXPECT_EQ(list.convert_to_vector(), (std::vector<int>{1, 5, 20}));
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->val, 5);
}

TEST(SinglyLinkedListTest, ErasePointerHeadElement) {
  std::vector<int> v = {1, 5, 10, 20};
  SinglyLinkedList list(v);
  ListNode *target = list.head();
  ListNode *result = list.erase(target);
  EXPECT_EQ(list.convert_to_vector(), (std::vector<int>{5, 10, 20}));
  EXPECT_EQ(result, nullptr);
}

TEST(SinglyLinkedListTest, ErasePointerTailElement) {
  std::vector<int> v = {1, 5, 10, 20};
  SinglyLinkedList list(v);
  ListNode *target = list.GetBackPointer();
  ListNode *result = list.erase(target);
  EXPECT_EQ(list.convert_to_vector(), (std::vector<int>{1, 5, 10}));
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->val, 10);
}

TEST(SinglyLinkedListTest, ErasePointerNullptrReturnsNullptr) {
  std::vector<int> v = {1, 2, 3};
  SinglyLinkedList list(v);
  EXPECT_EQ(list.erase(static_cast<ListNode *>(nullptr)), nullptr);
  EXPECT_EQ(list.size(), 3);
}

TEST(SinglyLinkedListTest, ErasePointerSingleElementList) {
  std::vector<int> v = {42};
  SinglyLinkedList list(v);
  ListNode *target = list.head();
  ListNode *result = list.erase(target);
  EXPECT_EQ(result, nullptr);
  EXPECT_TRUE(list.empty());
}

TEST(SinglyLinkedListTest, ErasePointerForeignNodeDoesNotAffectList) {
  std::vector<int> v = {1, 2, 3};
  SinglyLinkedList list(v);
  SinglyLinkedList other(std::vector<int>{99});
  ListNode *result = list.erase(other.head());
  EXPECT_EQ(result, nullptr);
  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(list.convert_to_vector(), (std::vector<int>{1, 2, 3}));
}

TEST(SinglyLinkedListTest, ErasePointerOnEmptyList) {
  SinglyLinkedList list;
  ListNode dangling(5);
  EXPECT_EQ(list.erase(&dangling), nullptr);
}

TEST(SinglyLinkedListTest, RemoveDuplicatesSpecExample) {
  std::vector<int> v = {1, 5, 1, 20, 4, 5, 32};
  SinglyLinkedList list(v);
  list.remove_duplicates();
  EXPECT_EQ(list.convert_to_vector(), (std::vector<int>{1, 5, 20, 4, 32}));
  EXPECT_EQ(list.size(), 5);
}

TEST(SinglyLinkedListTest, RemoveDuplicatesWithNoDuplicates) {
  std::vector<int> v = {1, 2, 3, 4};
  SinglyLinkedList list(v);
  list.remove_duplicates();
  EXPECT_EQ(list.convert_to_vector(), v);
}

TEST(SinglyLinkedListTest, RemoveDuplicatesAllIdentical) {
  std::vector<int> v = {7, 7, 7, 7};
  SinglyLinkedList list(v);
  list.remove_duplicates();
  EXPECT_EQ(list.convert_to_vector(), (std::vector<int>{7}));
  EXPECT_EQ(list.size(), 1);
}

TEST(SinglyLinkedListTest, RemoveDuplicatesAtTailUpdatesBack) {
  std::vector<int> v = {1, 2, 3, 1};
  SinglyLinkedList list(v);
  list.remove_duplicates();
  EXPECT_EQ(list.convert_to_vector(), (std::vector<int>{1, 2, 3}));
  EXPECT_EQ(list.back(), 3);
}

TEST(SinglyLinkedListTest, RemoveDuplicatesOnEmptyList) {
  SinglyLinkedList list;
  list.remove_duplicates();
  EXPECT_TRUE(list.empty());
}

TEST(SinglyLinkedListTest, RemoveDuplicatesOnSingleElementList) {
  std::vector<int> v = {5};
  SinglyLinkedList list(v);
  list.remove_duplicates();
  EXPECT_EQ(list.convert_to_vector(), v);
}

TEST(SinglyLinkedListTest, ReverseSpecExample) {
  std::vector<int> v = {1, 5, 1, 20};
  SinglyLinkedList list(v);
  list.reverse();
  EXPECT_EQ(list.convert_to_vector(), (std::vector<int>{20, 1, 5, 1}));
  EXPECT_EQ(list.head()->val, 20);
  EXPECT_EQ(list.back(), 1);
}

TEST(SinglyLinkedListTest, ReverseEmptyList) {
  SinglyLinkedList list;
  list.reverse();
  EXPECT_TRUE(list.empty());
  EXPECT_EQ(list.head(), nullptr);
}

TEST(SinglyLinkedListTest, ReverseSingleElementList) {
  std::vector<int> v = {9};
  SinglyLinkedList list(v);
  list.reverse();
  EXPECT_EQ(list.convert_to_vector(), v);
}

TEST(SinglyLinkedListTest, ReverseTwiceRestoresOriginalOrder) {
  std::vector<int> v = {1, 2, 3, 4, 5};
  SinglyLinkedList list(v);
  list.reverse();
  list.reverse();
  EXPECT_EQ(list.convert_to_vector(), v);
  EXPECT_EQ(list.size(), 5);
}