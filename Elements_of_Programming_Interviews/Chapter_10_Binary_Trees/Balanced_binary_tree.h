#ifndef ALGORITHM_ANALYSIS_BALANCED_BINARY_TREE_H
#define ALGORITHM_ANALYSIS_BALANCED_BINARY_TREE_H

#include <algorithm>
#include <memory>
#include <utility>

#include "Binary_tree_prototype.h"

using std::make_unique;
using std::max;
using std::unique_ptr;

struct BalancedStatusWithHeight;

BalancedStatusWithHeight CheckBalanced(
    const unique_ptr<BinaryTreeNode<int>>&);

// @include
struct BalancedStatusWithHeight {
  bool balanced;
  int height;
};

bool IsBalanced(const unique_ptr<BinaryTreeNode<int>>& tree) {
  return CheckBalanced(tree).balanced;
}

// First value of the return value indicates if tree is balanced, and if
// balanced the second value of the return value is the height of tree.
BalancedStatusWithHeight CheckBalanced(
    const unique_ptr<BinaryTreeNode<int>>& tree) {
  if (tree == nullptr) {
    return {true, -1};  // Base case.
  }

  auto left_result = CheckBalanced(tree->left);
  if (!left_result.balanced) {
    return {false, 0};  // Left subtree is not balanced.
  }
  auto right_result = CheckBalanced(tree->right);
  if (!right_result.balanced) {
    return {false, 0};  // Right subtree is not balanced.
  }

  bool is_balanced = abs(left_result.height - right_result.height) <= 1;
  int height = max(left_result.height, right_result.height) + 1;
  return {is_balanced, height};
}
// @exclude

#endif //ALGORITHM_ANALYSIS_BALANCED_BINARY_TREE_H
