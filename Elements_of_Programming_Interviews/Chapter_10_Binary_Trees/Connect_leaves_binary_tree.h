#ifndef ALGORITHM_ANALYSIS_CONNECT_LEAVES_BINARY_TREE_H
#define ALGORITHM_ANALYSIS_CONNECT_LEAVES_BINARY_TREE_H
//10.14 Form a linked list from the leaves of a binary tree

#include <list>
#include <memory>

#include "Binary_tree_prototype.h"

using std::list;
using std::make_unique;
using std::unique_ptr;
using btree::BinaryTreeNode;

// @include
list<const unique_ptr<BinaryTreeNode<int>>*> CreateListOfLeaves(
        const unique_ptr<BinaryTreeNode<int>>& tree) {
    list<const unique_ptr<BinaryTreeNode<int>>*> leaves;
    if (tree != nullptr) {
        if (tree->left == nullptr && tree->right == nullptr) {
            leaves.emplace_back(&tree);
        } else {
            // First do the left subtree, and then do the right subtree.
            leaves.splice(leaves.end(), CreateListOfLeaves(tree->left));
            leaves.splice(leaves.end(), CreateListOfLeaves(tree->right));
        }
    }
    return leaves;
}
// @exclude


#endif //ALGORITHM_ANALYSIS_CONNECT_LEAVES_BINARY_TREE_H
