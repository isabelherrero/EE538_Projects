#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------

namespace {

bool IsValidMaxHeap(const std::vector<Student>& data) {
  int n = static_cast<int>(data.size());
  for (int i = 0; i < n; i++) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && data[i].grade < data[left].grade) return false;
    if (right < n && data[i].grade < data[right].grade) return false;
  }
  return true;
}

}  

TEST(StudentMaxHeapTest, DefaultConstructorIsEmpty) {
  StudentMaxHeap heap;
  EXPECT_TRUE(heap.empty());
  EXPECT_EQ(heap.size(), 0);
}

TEST(StudentMaxHeapTest, TopOnEmptyHeapReturnsDefaultStudent) {
  StudentMaxHeap heap;
  Student top = heap.top();
  EXPECT_EQ(top.name, "NO_NAME");
  EXPECT_EQ(top.grade, INT_MIN);
}

TEST(StudentMaxHeapTest, PopOnEmptyHeapReturnsFalse) {
  StudentMaxHeap heap;
  EXPECT_FALSE(heap.pop());
}

TEST(StudentMaxHeapTest, PushSingleElement) {
  StudentMaxHeap heap;
  heap.push(Student("Alice", 90));
  EXPECT_FALSE(heap.empty());
  EXPECT_EQ(heap.size(), 1);
  EXPECT_EQ(heap.top().grade, 90);
  EXPECT_EQ(heap.top().name, "Alice");
}

TEST(StudentMaxHeapTest, PushMultipleKeepsMaxAtTop) {
  StudentMaxHeap heap;
  heap.push(Student("Alice", 70));
  heap.push(Student("Bob", 95));
  heap.push(Student("Carla", 60));
  heap.push(Student("Dave", 88));

  EXPECT_EQ(heap.size(), 4);
  EXPECT_EQ(heap.top().grade, 95);
  EXPECT_EQ(heap.top().name, "Bob");
  EXPECT_TRUE(IsValidMaxHeap(heap.GetData()));
}

TEST(StudentMaxHeapTest, PushInAscendingOrderStillMaintainsHeap) {
  StudentMaxHeap heap;
  for (int grade = 1; grade <= 10; grade++) {
    heap.push(Student("S" + std::to_string(grade), grade));
  }
  EXPECT_EQ(heap.top().grade, 10);
  EXPECT_TRUE(IsValidMaxHeap(heap.GetData()));
}

TEST(StudentMaxHeapTest, PushInDescendingOrderStillMaintainsHeap) {
  StudentMaxHeap heap;
  for (int grade = 10; grade >= 1; grade--) {
    heap.push(Student("S" + std::to_string(grade), grade));
  }
  EXPECT_EQ(heap.top().grade, 10);
  EXPECT_TRUE(IsValidMaxHeap(heap.GetData()));
}

TEST(StudentMaxHeapTest, PopRemovesMaxAndRestoresHeapProperty) {
  StudentMaxHeap heap;
  heap.push(Student("Alice", 70));
  heap.push(Student("Bob", 95));
  heap.push(Student("Carla", 60));
  heap.push(Student("Dave", 88));

  EXPECT_EQ(heap.top().grade, 95);
  EXPECT_TRUE(heap.pop());
  EXPECT_EQ(heap.size(), 3);
  EXPECT_EQ(heap.top().grade, 88);
  EXPECT_TRUE(IsValidMaxHeap(heap.GetData()));
}

TEST(StudentMaxHeapTest, PopUntilEmptyYieldsDescendingOrder) {
  StudentMaxHeap heap;
  std::vector<int> grades = {50, 20, 90, 10, 40, 90, 30};
  for (int g : grades) {
    heap.push(Student("S", g));
  }

  std::vector<int> popped;
  while (!heap.empty()) {
    popped.push_back(heap.top().grade);
    EXPECT_TRUE(heap.pop());
  }
  EXPECT_FALSE(heap.pop());

  ASSERT_EQ(popped.size(), grades.size());
  for (size_t i = 1; i < popped.size(); i++) {
    EXPECT_GE(popped[i - 1], popped[i]);
  }
}

TEST(StudentMaxHeapTest, ParameterizedConstructorBuildsValidHeap) {
  std::vector<Student> input = {Student("A", 5),  Student("B", 3),
                                 Student("C", 8),  Student("D", 1),
                                 Student("E", 9),  Student("F", 2)};
  StudentMaxHeap heap(input);
  EXPECT_EQ(heap.size(), 6);
  EXPECT_EQ(heap.top().grade, 9);
  EXPECT_TRUE(IsValidMaxHeap(heap.GetData()));
}

TEST(StudentMaxHeapTest, ParameterizedConstructorEmptyVector) {
  std::vector<Student> input;
  StudentMaxHeap heap(input);
  EXPECT_TRUE(heap.empty());
  EXPECT_EQ(heap.size(), 0);
}

TEST(StudentMaxHeapTest, ParameterizedConstructorSingleElement) {
  std::vector<Student> input = {Student("Solo", 42)};
  StudentMaxHeap heap(input);
  EXPECT_EQ(heap.size(), 1);
  EXPECT_EQ(heap.top().grade, 42);
}

TEST(StudentMaxHeapTest, ParameterizedConstructorWithDuplicateGrades) {
  std::vector<Student> input = {Student("A", 5), Student("B", 5),
                                 Student("C", 5)};
  StudentMaxHeap heap(input);
  EXPECT_EQ(heap.size(), 3);
  EXPECT_EQ(heap.top().grade, 5);
  EXPECT_TRUE(IsValidMaxHeap(heap.GetData()));
}

TEST(StudentMaxHeapTest, GetParentIndexOnRootIsIntMax) {
  std::vector<Student> input = {Student("A", 1), Student("B", 2)};
  StudentMaxHeap heap(input);
  EXPECT_EQ(heap.GetParentIndex(0), INT_MAX);
}

TEST(StudentMaxHeapTest, GetParentIndexOutOfRangeIsIntMax) {
  std::vector<Student> input = {Student("A", 1), Student("B", 2)};
  StudentMaxHeap heap(input);
  EXPECT_EQ(heap.GetParentIndex(-1), INT_MAX);
  EXPECT_EQ(heap.GetParentIndex(100), INT_MAX);
}

TEST(StudentMaxHeapTest, GetParentIndexValid) {
  std::vector<Student> input = {Student("A", 1), Student("B", 2),
                                 Student("C", 3)};
  StudentMaxHeap heap(input);
  EXPECT_EQ(heap.GetParentIndex(1), 0);
  EXPECT_EQ(heap.GetParentIndex(2), 0);
}

TEST(StudentMaxHeapTest, GetLeftRightIndexOnLeafIsIntMax) {
  std::vector<Student> input = {Student("A", 3), Student("B", 2),
                                 Student("C", 1)};
  StudentMaxHeap heap(input);
  EXPECT_EQ(heap.GetLeftIndex(1), INT_MAX);
  EXPECT_EQ(heap.GetRightIndex(1), INT_MAX);
  EXPECT_EQ(heap.GetLeftIndex(2), INT_MAX);
  EXPECT_EQ(heap.GetRightIndex(2), INT_MAX);
}

TEST(StudentMaxHeapTest, GetLeftRightIndexOutOfRangeIsIntMax) {
  std::vector<Student> input = {Student("A", 1)};
  StudentMaxHeap heap(input);
  EXPECT_EQ(heap.GetLeftIndex(-1), INT_MAX);
  EXPECT_EQ(heap.GetRightIndex(50), INT_MAX);
}

TEST(StudentMaxHeapTest, GetLargestChildIndexNoChildren) {
  std::vector<Student> input = {Student("A", 1)};
  StudentMaxHeap heap(input);
  EXPECT_EQ(heap.GetLargestChildIndex(0), INT_MAX);
}

TEST(StudentMaxHeapTest, GetLargestChildIndexOnlyLeftChild) {
  std::vector<Student> input = {Student("A", 10), Student("B", 5)};
  StudentMaxHeap heap(input);
  EXPECT_EQ(heap.GetLargestChildIndex(0), 1);
}

TEST(StudentMaxHeapTest, GetLargestChildIndexPicksLargerOfTwo) {
  std::vector<Student> input = {Student("Root", 10), Student("Left", 3),
                                 Student("Right", 7)};
  StudentMaxHeap heap(input);
  EXPECT_EQ(heap.GetLargestChildIndex(0), 2);
}

TEST(StudentMaxHeapTest, GetParentGetLeftGetRightReturnDefaultWhenInvalid) {
  std::vector<Student> input = {Student("A", 1)};
  StudentMaxHeap heap(input);

  Student parent = heap.GetParent(0);
  EXPECT_EQ(parent.name, "NO_NAME");
  EXPECT_EQ(parent.grade, INT_MIN);

  Student left = heap.GetLeft(0);
  EXPECT_EQ(left.name, "NO_NAME");
  EXPECT_EQ(left.grade, INT_MIN);

  Student right = heap.GetRight(0);
  EXPECT_EQ(right.name, "NO_NAME");
  EXPECT_EQ(right.grade, INT_MIN);
}

TEST(StudentMaxHeapTest, GetParentGetLeftGetRightReturnCorrectValues) {
  std::vector<Student> input = {Student("Root", 10), Student("Left", 8),
                                 Student("Right", 9)};
  StudentMaxHeap heap(input);
  EXPECT_EQ(heap.GetParent(1).name, "Root");
  EXPECT_EQ(heap.GetLeft(0).name, "Left");
  EXPECT_EQ(heap.GetRight(0).name, "Right");
}

TEST(HeapSortTest, EmptyVector) {
  std::vector<Student> input;
  HeapSort(input);
  EXPECT_TRUE(input.empty());
}

TEST(HeapSortTest, SingleElement) {
  std::vector<Student> input = {Student("Solo", 42)};
  HeapSort(input);
  ASSERT_EQ(input.size(), 1);
  EXPECT_EQ(input[0].grade, 42);
}

TEST(HeapSortTest, AlreadySortedAscending) {
  std::vector<Student> input = {Student("A", 1), Student("B", 2),
                                 Student("C", 3), Student("D", 4)};
  HeapSort(input);
  ASSERT_EQ(input.size(), 4);
  EXPECT_EQ(input[0].grade, 1);
  EXPECT_EQ(input[1].grade, 2);
  EXPECT_EQ(input[2].grade, 3);
  EXPECT_EQ(input[3].grade, 4);
}

TEST(HeapSortTest, ReverseSorted) {
  std::vector<Student> input = {Student("D", 4), Student("C", 3),
                                 Student("B", 2), Student("A", 1)};
  HeapSort(input);
  ASSERT_EQ(input.size(), 4);
  EXPECT_EQ(input[0].grade, 1);
  EXPECT_EQ(input[1].grade, 2);
  EXPECT_EQ(input[2].grade, 3);
  EXPECT_EQ(input[3].grade, 4);
}

TEST(HeapSortTest, UnsortedGeneralCase) {
  std::vector<Student> input = {Student("A", 5),  Student("B", 1),
                                 Student("C", 9),  Student("D", 3),
                                 Student("E", 7),  Student("F", 2)};
  HeapSort(input);
  std::vector<int> expected = {1, 2, 3, 5, 7, 9};
  ASSERT_EQ(input.size(), expected.size());
  for (size_t i = 0; i < expected.size(); i++) {
    EXPECT_EQ(input[i].grade, expected[i]);
  }
}

TEST(HeapSortTest, WithDuplicateGrades) {
  std::vector<Student> input = {Student("A", 5), Student("B", 3),
                                 Student("C", 5), Student("D", 3),
                                 Student("E", 5)};
  HeapSort(input);
  std::vector<int> expected = {3, 3, 5, 5, 5};
  ASSERT_EQ(input.size(), expected.size());
  for (size_t i = 0; i < expected.size(); i++) {
    EXPECT_EQ(input[i].grade, expected[i]);
  }
}

TEST(HeapSortTest, AllIdenticalGrades) {
  std::vector<Student> input = {Student("A", 7), Student("B", 7),
                                 Student("C", 7)};
  HeapSort(input);
  ASSERT_EQ(input.size(), 3);
  for (const auto& s : input) {
    EXPECT_EQ(s.grade, 7);
  }
}

TEST(HeapSortTest, NegativeGrades) {
  std::vector<Student> input = {Student("A", -5), Student("B", 3),
                                 Student("C", -10), Student("D", 0)};
  HeapSort(input);
  std::vector<int> expected = {-10, -5, 0, 3};
  ASSERT_EQ(input.size(), expected.size());
  for (size_t i = 0; i < expected.size(); i++) {
    EXPECT_EQ(input[i].grade, expected[i]);
  }
}

TEST(HeapSortTest, LargerRandomLikeVector) {
  std::vector<Student> input = {Student("A", 34), Student("B", 7),
                                 Student("C", 23), Student("D", 32),
                                 Student("E", 5),  Student("F", 62),
                                 Student("G", 32), Student("H", 2),
                                 Student("I", 12), Student("J", 45)};
  HeapSort(input);
  for (size_t i = 1; i < input.size(); i++) {
    EXPECT_LE(input[i - 1].grade, input[i].grade);
  }
}