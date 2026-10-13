#ifndef TREE_TRAVERSAL_H
#define TREE_TRAVERSAL_H

#include <vector>

// Definition for a binary tree node.
// Already implemented. No need to change.
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Create a binary tree from a vector of integers.
// The vector represents the level order traversal of the binary tree.
// It interprets each element in the vector as a node in the binary tree. The
// index of the element determines the position of the node in the tree:
//
// The root node is at index 0.
// The left child of a node at index i is at index 2*i + 1.
// The right child of a node at index i is at index 2*i + 2.
//
// A value of -1 in the vector represents a null node (i.e., an absent node),
// which means that the function should not create a node for that position in
// the tree.
//
// Example:
// SimpleTree: The input vector is {1, 2, 3, -1, 4}, and the expected tree
// structure is:
//    1
//   / \
//  2   3
//   \
//    4
//
// Example: Complete Tree:
// The input vector is {1, 2, 3, 4, 5, 6, 7}, and the expected tree structure
// is:
//
//      1
//    /   \
//   2     3
//  / \   / \
// 4   5 6   7
TreeNode* createTree(const std::vector<int>& values);

// This function deletes the tree
void deleteTree(TreeNode* root);

//--------------------------------------------------------------------------
// Inorder traversal
// Performs an inorder traversal of the binary tree and returns a vector of
// nodes.
std::vector<int> inorderTraversal(TreeNode* root);
//--------------------------------------------------------------------------
// Preorder traversal
// Performs a preorder traversal of the binary tree and returns a vector of
// nodes.
std::vector<int> preorderTraversal(TreeNode* root);
//--------------------------------------------------------------------------
// Postorder traversal
// Performs a postorder traversal of the binary tree and returns a vector of
// nodes.
std::vector<int> postorderTraversal(TreeNode* root);

#endif  // TREE_TRAVERSAL_H
