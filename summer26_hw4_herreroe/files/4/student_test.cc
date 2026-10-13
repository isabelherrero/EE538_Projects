#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------

TEST(CreateTreeTest, EmptyVectorProducesNullRoot) {
  std::vector<int> v = {};
  TreeNode *root = createTree(v);
  EXPECT_EQ(root, nullptr);
  deleteTree(root);
}

TEST(CreateTreeTest, RootIsMinusOneProducesNullTree) {
  std::vector<int> v = {-1};
  TreeNode *root = createTree(v);
  EXPECT_EQ(root, nullptr);
  deleteTree(root);
}

TEST(CreateTreeTest, RootIsMinusOneWithTrailingValuesStillNull) {
  std::vector<int> v = {-1, 2, 3};
  TreeNode *root = createTree(v);
  EXPECT_EQ(root, nullptr);
  deleteTree(root);
}

TEST(CreateTreeTest, SingleNodeTree) {
  std::vector<int> v = {5};
  TreeNode *root = createTree(v);
  ASSERT_NE(root, nullptr);
  EXPECT_EQ(root->val, 5);
  EXPECT_EQ(root->left, nullptr);
  EXPECT_EQ(root->right, nullptr);
  deleteTree(root);
}

TEST(CreateTreeTest, SpecExampleSimpleTree) {
  std::vector<int> v = {1, 2, 3, -1, 4};
  TreeNode *root = createTree(v);
  ASSERT_NE(root, nullptr);
  EXPECT_EQ(root->val, 1);

  ASSERT_NE(root->left, nullptr);
  EXPECT_EQ(root->left->val, 2);
  EXPECT_EQ(root->left->left, nullptr);
  ASSERT_NE(root->left->right, nullptr);
  EXPECT_EQ(root->left->right->val, 4);

  ASSERT_NE(root->right, nullptr);
  EXPECT_EQ(root->right->val, 3);
  EXPECT_EQ(root->right->left, nullptr);
  EXPECT_EQ(root->right->right, nullptr);

  deleteTree(root);
}

TEST(CreateTreeTest, SpecExampleCompleteTree) {
  std::vector<int> v = {1, 2, 3, 4, 5, 6, 7};
  TreeNode *root = createTree(v);
  ASSERT_NE(root, nullptr);
  EXPECT_EQ(root->val, 1);
  EXPECT_EQ(root->left->val, 2);
  EXPECT_EQ(root->right->val, 3);
  EXPECT_EQ(root->left->left->val, 4);
  EXPECT_EQ(root->left->right->val, 5);
  EXPECT_EQ(root->right->left->val, 6);
  EXPECT_EQ(root->right->right->val, 7);
  deleteTree(root);
}

TEST(CreateTreeTest, LeftOnlyChildAtRoot) {
  std::vector<int> v = {1, 2, -1};
  TreeNode *root = createTree(v);
  ASSERT_NE(root, nullptr);
  ASSERT_NE(root->left, nullptr);
  EXPECT_EQ(root->left->val, 2);
  EXPECT_EQ(root->right, nullptr);
  deleteTree(root);
}

TEST(CreateTreeTest, RightOnlyChildAtRoot) {
  std::vector<int> v = {1, -1, 3};
  TreeNode *root = createTree(v);
  ASSERT_NE(root, nullptr);
  EXPECT_EQ(root->left, nullptr);
  ASSERT_NE(root->right, nullptr);
  EXPECT_EQ(root->right->val, 3);
  deleteTree(root);
}

TEST(CreateTreeTest, ChildIndicesBeyondVectorEndAreNull) {
  std::vector<int> v = {1, 2};
  TreeNode *root = createTree(v);
  ASSERT_NE(root, nullptr);
  ASSERT_NE(root->left, nullptr);
  EXPECT_EQ(root->left->val, 2);
  EXPECT_EQ(root->right, nullptr);
  EXPECT_EQ(root->left->left, nullptr);
  EXPECT_EQ(root->left->right, nullptr);
  deleteTree(root);
}

TEST(CreateTreeTest, LeftSkewedTree) {
  std::vector<int> v = {1, 2, -1, 3, -1, -1, -1, 4};
  TreeNode *root = createTree(v);
  ASSERT_NE(root, nullptr);
  EXPECT_EQ(root->val, 1);
  EXPECT_EQ(root->right, nullptr);
  ASSERT_NE(root->left, nullptr);
  EXPECT_EQ(root->left->val, 2);
  ASSERT_NE(root->left->left, nullptr);
  EXPECT_EQ(root->left->left->val, 3);
  EXPECT_EQ(root->left->left->right, nullptr);
  ASSERT_NE(root->left->left->left, nullptr);
  EXPECT_EQ(root->left->left->left->val, 4);
  deleteTree(root);
}

TEST(CreateTreeTest, RightSkewedTree) {
  std::vector<int> v = {1, -1, 2, -1, -1, -1, 3};
  TreeNode *root = createTree(v);
  ASSERT_NE(root, nullptr);
  EXPECT_EQ(root->left, nullptr);
  ASSERT_NE(root->right, nullptr);
  EXPECT_EQ(root->right->val, 2);
  ASSERT_NE(root->right->right, nullptr);
  EXPECT_EQ(root->right->right->val, 3);
  deleteTree(root);
}

TEST(CreateTreeTest, ValuesIncludingZeroAndNegativesOtherThanSentinel) {
  std::vector<int> v = {0, -5, 7};
  TreeNode *root = createTree(v);
  ASSERT_NE(root, nullptr);
  EXPECT_EQ(root->val, 0);
  ASSERT_NE(root->left, nullptr);
  EXPECT_EQ(root->left->val, -5);
  ASSERT_NE(root->right, nullptr);
  EXPECT_EQ(root->right->val, 7);
  deleteTree(root);
}

TEST(DeleteTreeTest, DeleteNullptrIsSafeNoOp) {
  deleteTree(nullptr);  // Should not crash.
  SUCCEED();
}

TEST(DeleteTreeTest, DeleteFullTreeDoesNotCrash) {
  std::vector<int> v = {1, 2, 3, 4, 5, 6, 7};
  TreeNode *root = createTree(v);
  deleteTree(root);
  SUCCEED();
}

TEST(TraversalTest, NullRootTraversalsAreEmpty) {
  EXPECT_EQ(inorderTraversal(nullptr), std::vector<int>{});
  EXPECT_EQ(preorderTraversal(nullptr), std::vector<int>{});
  EXPECT_EQ(postorderTraversal(nullptr), std::vector<int>{});
}

TEST(TraversalTest, SingleNodeTraversals) {
  std::vector<int> v = {5};
  TreeNode *root = createTree(v);
  EXPECT_EQ(inorderTraversal(root), (std::vector<int>{5}));
  EXPECT_EQ(preorderTraversal(root), (std::vector<int>{5}));
  EXPECT_EQ(postorderTraversal(root), (std::vector<int>{5}));
  deleteTree(root);
}

TEST(TraversalTest, SpecExampleSimpleTreeTraversals) {
  std::vector<int> v = {1, 2, 3, -1, 4};
  TreeNode *root = createTree(v);
  EXPECT_EQ(preorderTraversal(root), (std::vector<int>{1, 2, 4, 3}));
  EXPECT_EQ(inorderTraversal(root), (std::vector<int>{2, 4, 1, 3}));
  EXPECT_EQ(postorderTraversal(root), (std::vector<int>{4, 2, 3, 1}));
  deleteTree(root);
}

TEST(TraversalTest, CompleteTreeTraversals) {
  std::vector<int> v = {1, 2, 3, 4, 5, 6, 7};
  TreeNode *root = createTree(v);
  EXPECT_EQ(preorderTraversal(root), (std::vector<int>{1, 2, 4, 5, 3, 6, 7}));
  EXPECT_EQ(inorderTraversal(root), (std::vector<int>{4, 2, 5, 1, 6, 3, 7}));
  EXPECT_EQ(postorderTraversal(root), (std::vector<int>{4, 5, 2, 6, 7, 3, 1}));
  deleteTree(root);
}

TEST(TraversalTest, LeftSkewedTreeTraversals) {
  std::vector<int> v = {1, 2, -1, 3, -1, -1, -1, 4};
  TreeNode *root = createTree(v);
  EXPECT_EQ(inorderTraversal(root), (std::vector<int>{4, 3, 2, 1}));
  EXPECT_EQ(preorderTraversal(root), (std::vector<int>{1, 2, 3, 4}));
  EXPECT_EQ(postorderTraversal(root), (std::vector<int>{4, 3, 2, 1}));
  deleteTree(root);
}

TEST(TraversalTest, RightSkewedTreeTraversals) {
  std::vector<int> v = {1, -1, 2, -1, -1, -1, 3};
  TreeNode *root = createTree(v);
  EXPECT_EQ(inorderTraversal(root), (std::vector<int>{1, 2, 3}));
  EXPECT_EQ(preorderTraversal(root), (std::vector<int>{1, 2, 3}));
  EXPECT_EQ(postorderTraversal(root), (std::vector<int>{3, 2, 1}));
  deleteTree(root);
}