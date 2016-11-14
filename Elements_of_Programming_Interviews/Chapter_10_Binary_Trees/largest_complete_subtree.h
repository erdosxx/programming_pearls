#ifndef ALGORITHM_ANALYSIS_LARGEST_COMPLETE_SUBTREE_H
#define ALGORITHM_ANALYSIS_LARGEST_COMPLETE_SUBTREE_H
// 10.1.1 Variant Test if a binary tree is height-balanced

#include <algorithm>
#include <memory>
#include "Binary_tree_prototype.h"

using std::max;
using std::unique_ptr;
using btree::BinaryTreeNode;
//using btree_node = btree::BinaryTreeNode<int>;

enum {DONT_CARE= 0};

struct subtree_stat {
    int size;
    int height;
    bool complete;
};

subtree_stat is_subtree_complete(const unique_ptr<BinaryTreeNode<int>>& tree, int* max_size_ptr) {
   if (tree == nullptr) {
      return {0, -1, true};
   }

   subtree_stat left_result = is_subtree_complete(tree->left, max_size_ptr);
   if (!left_result.complete) {
      return {DONT_CARE, DONT_CARE, false};
   }

   subtree_stat right_result = is_subtree_complete(tree->right, max_size_ptr);
   if (!right_result.complete) {
      return {DONT_CARE, DONT_CARE, false};
   }

   if (left_result.height != right_result.height) {
      return {DONT_CARE, DONT_CARE, false};
   } else { // left_height == right_height
      int new_complete_size = left_result.size + right_result.size + 1;
      *max_size_ptr = max(new_complete_size, *max_size_ptr);
      return {new_complete_size, left_result.height + 1, true};
   }
}

int size_largest_complete_subtree (const unique_ptr<BinaryTreeNode<int>>& tree) {
   int max_size =0;

   is_subtree_complete(tree, &max_size);

   return max_size;
}


#endif //ALGORITHM_ANALYSIS_LARGEST_COMPLETE_SUBTREE_H
