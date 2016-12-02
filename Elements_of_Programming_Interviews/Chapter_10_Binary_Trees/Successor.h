#ifndef ALGORITHM_ANALYSIS_SUCCESSOR_H
#define ALGORITHM_ANALYSIS_SUCCESSOR_H
// 10.10 Compute the successor

#include <memory>

#include "Binary_tree_with_parent_prototype.h"

using std::make_unique;
using std::unique_ptr;

namespace successor {
    using btree_with_parent::BinaryTreeNode;

// @include
    BinaryTreeNode<int> *FindSuccessor(
            const unique_ptr<BinaryTreeNode<int>> &node) {
        auto *iter = node.get();
        if (iter->right != nullptr) {
            // Successor is the leftmost element in node's right subtree.
            iter = iter->right.get();
            while (iter->left) {
                iter = iter->left.get();
            }
            return iter;
        }

        // Find the closest ancestor whose left subtree contains node.
        while (iter->parent != nullptr && iter->parent->right.get() == iter) {
            iter = iter->parent;
        }
        // A return timestamp of nullptr means node does not have successor, i.e., it is
        // the rightmost node in the tree.
        return iter->parent;
    }
// @exclude
}

#endif //ALGORITHM_ANALYSIS_SUCCESSOR_H
