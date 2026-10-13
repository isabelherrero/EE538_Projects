#include "q.h"

#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>
// TODO:
// 1. Implement the the functions in q.h.
// 2. Write some unit tests for them in student_test.cc

namespace {

TreeNode* buildSubtree(const std::vector<int>& values, int i) {
  if (i < 0 || i >= static_cast<int>(values.size()) || values[i] == -1) {
    return nullptr;
  }
  TreeNode* node = new TreeNode(values[i]);
  node->left = buildSubtree(values, 2 * i + 1);
  node->right = buildSubtree(values, 2 * i + 2);
  return node;
}

void inorderHelper(TreeNode* node, std::vector<int>& out) {
  if (node == nullptr) {
    return;
  }
  inorderHelper(node->left, out);
  out.push_back(node->val);
  inorderHelper(node->right, out);
}

void preorderHelper(TreeNode* node, std::vector<int>& out) {
  if (node == nullptr) {
    return;
  }
  out.push_back(node->val);
  preorderHelper(node->left, out);
  preorderHelper(node->right, out);
}

void postorderHelper(TreeNode* node, std::vector<int>& out) {
  if (node == nullptr) {
    return;
  }
  postorderHelper(node->left, out);
  postorderHelper(node->right, out);
  out.push_back(node->val);
}

}

TreeNode* createTree(const std::vector<int>& values) {
  return buildSubtree(values, 0);
}

void deleteTree(TreeNode* root) {
  if (root == nullptr) {
    return;
  }
  deleteTree(root->left);
  deleteTree(root->right);
  delete root;
}

std::vector<int> inorderTraversal(TreeNode* root) {
  std::vector<int> result;
  inorderHelper(root, result);
  return result;
}

std::vector<int> preorderTraversal(TreeNode* root) {
  std::vector<int> result;
  preorderHelper(root, result);
  return result;
}

std::vector<int> postorderTraversal(TreeNode* root) {
  std::vector<int> result;
  postorderHelper(root, result);
  return result;
}
