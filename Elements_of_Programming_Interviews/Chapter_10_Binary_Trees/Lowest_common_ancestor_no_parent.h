#ifndef ALGORITHM_ANALYSIS_LOWEST_COMMON_ANCESTOR_NO_PARENT_H
#define ALGORITHM_ANALYSIS_LOWEST_COMMON_ANCESTOR_NO_PARENT_H
// 10.3 Compute the lowest common ancestor in a binary tree

#include <memory>

#include "Binary_tree_prototype.h"

using std::make_unique;
using std::unique_ptr;
using btree::BinaryTreeNode;
using btree_ptr= unique_ptr<BinaryTreeNode<int>>;

namespace lca_no_parenet {

    struct Status {
        int num_target_nodes;
        BinaryTreeNode<int> *ancestor;
    };

    Status LCAHelper(const btree_ptr &,
                     const btree_ptr &,
                     const btree_ptr &);


    BinaryTreeNode<int> *LCA(const btree_ptr &tree,
                             const btree_ptr &node0,
                             const btree_ptr &node1) {
        return LCAHelper(tree, node0, node1).ancestor;
    }

// Returns an object consisting of an int and a node. The int field is
// 0, 1, or 2 depending on how many of {node0, node1} are present in
// the tree. If both are present in the tree, when ancestor is
// assigned to a non-null value, it is the LCA.
    Status LCAHelper(const btree_ptr &tree,
                     const btree_ptr &node0,
                     const btree_ptr &node1) {
        if (tree == nullptr) {
            return {0, nullptr};
        }

        auto left_result = LCAHelper(tree->left, node0, node1);
        if (left_result.num_target_nodes == 2) {  // Found both nodes in the left subtree.
            return left_result;
        }

        auto right_result = LCAHelper(tree->right, node0, node1);
        if (right_result.num_target_nodes == 2) {  // Found both nodes in the right subtree.
            return right_result;
        }

        int num_target_nodes = left_result.num_target_nodes +
                               right_result.num_target_nodes + (tree == node0) +
                               (tree == node1);
        return {num_target_nodes, num_target_nodes == 2 ? tree.get() : nullptr};
    }
// @exclude
}

#endif //ALGORITHM_ANALYSIS_LOWEST_COMMON_ANCESTOR_NO_PARENT_H
