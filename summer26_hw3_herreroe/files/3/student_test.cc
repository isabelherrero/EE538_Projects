#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------

TEST(QueueBasicTest, NewQueueIsEmpty) {
  Queue q;
  EXPECT_TRUE(q.IsEmpty());
}

TEST(QueueBasicTest, FrontOnEmptyQueueReturnsMinusOne) {
  Queue q;
  EXPECT_EQ(q.Front(), -1);
}

TEST(QueueBasicTest, DequeueOnEmptyQueueReturnsFalse) {
  Queue q;
  EXPECT_FALSE(q.Dequeue());
}

TEST(QueueBasicTest, EnqueueMakesQueueNonEmpty) {
  Queue q;
  EXPECT_TRUE(q.Enqueue(1));
  EXPECT_FALSE(q.IsEmpty());
}

TEST(QueueBasicTest, FrontReturnsFirstEnqueuedValue) {
  Queue q;
  q.Enqueue(1);
  q.Enqueue(2);
  q.Enqueue(3);
  EXPECT_EQ(q.Front(), 1);
}

TEST(QueueBasicTest, FifoOrderPreserved) {
  Queue q;
  q.Enqueue(1);
  q.Enqueue(2);
  q.Enqueue(3);
  std::vector<int> expected = {1, 2, 3};
  EXPECT_EQ(q.GetData(), expected);
}

TEST(QueueBasicTest, DequeueRemovesFromFrontInOrder) {
  Queue q;
  q.Enqueue(1);
  q.Enqueue(2);
  q.Enqueue(3);
  EXPECT_EQ(q.Front(), 1);
  EXPECT_TRUE(q.Dequeue());
  EXPECT_EQ(q.Front(), 2);
  EXPECT_TRUE(q.Dequeue());
  EXPECT_EQ(q.Front(), 3);
  EXPECT_TRUE(q.Dequeue());
  EXPECT_TRUE(q.IsEmpty());
}

TEST(QueueBasicTest, DequeueDownToEmptyThenDequeueAgainFails) {
  Queue q;
  q.Enqueue(42);
  EXPECT_TRUE(q.Dequeue());
  EXPECT_TRUE(q.IsEmpty());
  EXPECT_FALSE(q.Dequeue());
  EXPECT_EQ(q.Front(), -1);
}

TEST(QueueBasicTest, EnqueueAfterEmptyingWorksAgain) {
  Queue q;
  q.Enqueue(1);
  q.Dequeue();
  EXPECT_TRUE(q.IsEmpty());
  q.Enqueue(99);
  EXPECT_FALSE(q.IsEmpty());
  EXPECT_EQ(q.Front(), 99);
}

TEST(QueueBasicTest, SingleElementQueueDequeueLeavesEmpty) {
  Queue q;
  q.Enqueue(7);
  EXPECT_EQ(q.Front(), 7);
  EXPECT_TRUE(q.Dequeue());
  EXPECT_TRUE(q.IsEmpty());
}

TEST(QueueCopyConstructorTest, CopyOfEmptyQueueIsEmpty) {
  Queue q1;
  Queue q2(q1);
  EXPECT_TRUE(q2.IsEmpty());
}

TEST(QueueCopyConstructorTest, CopyHasSameElements) {
  Queue q1;
  q1.Enqueue(1);
  q1.Enqueue(2);
  q1.Enqueue(3);
  Queue q2(q1);
  EXPECT_EQ(q2.GetData(), q1.GetData());
}

TEST(QueueCopyConstructorTest, CopyIsIndependentDeepCopy) {
  Queue q1;
  q1.Enqueue(1);
  q1.Enqueue(2);
  Queue q2(q1);
  q2.Enqueue(3);
  q1.Dequeue();
  std::vector<int> expected_q1 = {2};
  std::vector<int> expected_q2 = {1, 2, 3};
  EXPECT_EQ(q1.GetData(), expected_q1);
  EXPECT_EQ(q2.GetData(), expected_q2);
}

TEST(QueueAssignmentTest, AssignCopiesElements) {
  Queue q1;
  q1.Enqueue(1);
  q1.Enqueue(2);
  Queue q2;
  q2.Enqueue(99);
  q2 = q1;
  EXPECT_EQ(q2.GetData(), q1.GetData());
}

TEST(QueueAssignmentTest, AssignIsIndependentDeepCopy) {
  Queue q1;
  q1.Enqueue(1);
  q1.Enqueue(2);
  Queue q2;
  q2 = q1;
  q2.Enqueue(3);
  std::vector<int> expected_q1 = {1, 2};
  std::vector<int> expected_q2 = {1, 2, 3};
  EXPECT_EQ(q1.GetData(), expected_q1);
  EXPECT_EQ(q2.GetData(), expected_q2);
}

TEST(QueueAssignmentTest, SelfAssignmentLeavesQueueUnchanged) {
  Queue q1;
  q1.Enqueue(1);
  q1.Enqueue(2);
  q1.Enqueue(3);
  q1 = q1;
  std::vector<int> expected = {1, 2, 3};
  EXPECT_EQ(q1.GetData(), expected);
}

TEST(QueueAssignmentTest, ChainedAssignment) {
  Queue q1, q2, q3;
  q3.Enqueue(5);
  q3.Enqueue(6);
  q1 = q2 = q3;
  std::vector<int> expected = {5, 6};
  EXPECT_EQ(q1.GetData(), expected);
  EXPECT_EQ(q2.GetData(), expected);
}

TEST(QueueAssignmentTest, AssignEmptyQueueClearsTarget) {
  Queue q1;
  q1.Enqueue(1);
  q1.Enqueue(2);
  Queue empty_queue;
  q1 = empty_queue;
  EXPECT_TRUE(q1.IsEmpty());
}

TEST(QueueOperatorPlusTest, MatchesSpecExample) {
  Queue q1;
  q1.Enqueue(1);
  q1.Enqueue(2);
  q1.Enqueue(3);
  Queue q2;
  q2.Enqueue(4);
  q2.Enqueue(5);
  Queue q3 = q1 + q2;
  std::vector<int> expected = {4, 5, 1, 2, 3};
  EXPECT_EQ(q3.GetData(), expected);
  EXPECT_EQ(q3.Front(), 4);
}

TEST(QueueOperatorPlusTest, LeftOperandEmpty) {
  Queue q1;
  Queue q2;
  q2.Enqueue(4);
  q2.Enqueue(5);
  Queue q3 = q1 + q2;
  std::vector<int> expected = {4, 5};
  EXPECT_EQ(q3.GetData(), expected);
}

TEST(QueueOperatorPlusTest, RightOperandEmpty) {
  Queue q1;
  q1.Enqueue(1);
  q1.Enqueue(2);
  Queue q2;
  Queue q3 = q1 + q2;
  std::vector<int> expected = {1, 2};
  EXPECT_EQ(q3.GetData(), expected);
}

TEST(QueueOperatorPlusTest, BothOperandsEmpty) {
  Queue q1;
  Queue q2;
  Queue q3 = q1 + q2;
  EXPECT_TRUE(q3.IsEmpty());
}

TEST(QueueOperatorPlusTest, OperandsUnchangedAfterAddition) {
  Queue q1;
  q1.Enqueue(1);
  q1.Enqueue(2);
  Queue q2;
  q2.Enqueue(3);
  Queue q3 = q1 + q2;
  (void)q3;
  std::vector<int> expected_q1 = {1, 2};
  std::vector<int> expected_q2 = {3};
  EXPECT_EQ(q1.GetData(), expected_q1);
  EXPECT_EQ(q2.GetData(), expected_q2);
}

TEST(QueueOperatorPlusTest, ResultIsIndependentOfOperands) {
  Queue q1;
  q1.Enqueue(1);
  Queue q2;
  q2.Enqueue(2);
  Queue q3 = q1 + q2;
  q3.Enqueue(100);
  std::vector<int> expected_q1 = {1};
  std::vector<int> expected_q2 = {2};
  EXPECT_EQ(q1.GetData(), expected_q1);
  EXPECT_EQ(q2.GetData(), expected_q2);
}

TEST(QueueOperatorPlusTest, SelfAddition) {
  Queue q1;
  q1.Enqueue(1);
  q1.Enqueue(2);
  Queue q3 = q1 + q1;
  std::vector<int> expected = {1, 2, 1, 2};
  EXPECT_EQ(q3.GetData(), expected);
}