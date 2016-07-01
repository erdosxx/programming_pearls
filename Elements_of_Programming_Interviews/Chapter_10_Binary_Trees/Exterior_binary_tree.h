#ifndef ALGORITHM_ANALYSIS_EXTERIOR_BINARY_TREE_H
#define ALGORITHM_ANALYSIS_EXTERIOR_BINARY_TREE_H

#include <list>
#include <memory>

#include "Binary_tree_prototype.h"

using std::list;
using std::make_unique;
using std::unique_ptr;
using btree::BinaryTreeNode;

list<const unique_ptr<BinaryTreeNode<int>>*> LeftBoundaryAndLeaves(
        const unique_ptr<BinaryTreeNode<int>>&, bool);

list<const unique_ptr<BinaryTreeNode<int>>*> RightBoundaryAndLeaves(
        const unique_ptr<BinaryTreeNode<int>>&, bool);

bool IsLeaf(const unique_ptr<BinaryTreeNode<int>>&);

// @include
list<const unique_ptr<BinaryTreeNode<int>>*> ExteriorBinaryTree(
        const unique_ptr<BinaryTreeNode<int>>& tree) {
    list<const unique_ptr<BinaryTreeNode<int>>*> exterior;

    if (tree != nullptr) {
        exterior.emplace_back(&tree);
        exterior.splice(exterior.end(), LeftBoundaryAndLeaves(tree->left, true));
        exterior.splice(exterior.end(), RightBoundaryAndLeaves(tree->right, true));
    }
    return exterior;
}

// Computes the nodes from the root to the leftmost leaf followed by all the
// leaves in subtree.
list<const unique_ptr<BinaryTreeNode<int>>*> LeftBoundaryAndLeaves(
        const unique_ptr<BinaryTreeNode<int>>& subtree, bool is_boundary) {
    list<const unique_ptr<BinaryTreeNode<int>>*> result;

    // The search is same as preorder traversal. But add additional boundary condition.
    if (subtree != nullptr) {
        if (is_boundary || IsLeaf(subtree)) {
            result.emplace_back(&subtree);
        }
        // when we go to left subtree, it could be boundary.
        result.splice(result.end(),
                      LeftBoundaryAndLeaves(subtree->left, is_boundary));
        // when we go to right subtree, to be boundary, left subtree must be null.
        //        B
        //      C
        //        D     <--- D is boundary and it's left sibling is null.
        result.splice(result.end(), LeftBoundaryAndLeaves(
                subtree->right,
                is_boundary && subtree->left == nullptr));
    }
    return result;
}

// Computes the leaves in left-to-right order followed by the rightmost leaf
// to the root path in subtree.
list<const unique_ptr<BinaryTreeNode<int>>*> RightBoundaryAndLeaves(
        const unique_ptr<BinaryTreeNode<int>>& subtree, bool is_boundary) {
    list<const unique_ptr<BinaryTreeNode<int>>*> result;

    // The search is same as postorder traversal. But add additional boundary condition.
    if (subtree != nullptr) {
        result.splice(
                result.end(),
                RightBoundaryAndLeaves(subtree->left,
                                       is_boundary && subtree->right == nullptr));
        result.splice(result.end(),
                      RightBoundaryAndLeaves(subtree->right, is_boundary));
        if (is_boundary || IsLeaf(subtree)) {
            result.emplace_back(&subtree);
        }
    }
    return result;
}

bool IsLeaf(const unique_ptr<BinaryTreeNode<int>>& node) {
    return node->left == nullptr && node->right == nullptr;
}
// @exclude

list<int> CreateOutputList(
        const list<const unique_ptr<BinaryTreeNode<int>>*>& L) {
    list<int> output;

    for (const auto* l : L) {
        output.push_back((*l)->data);
    }
    return output;
}

#endif //ALGORITHM_ANALYSIS_EXTERIOR_BINARY_TREE_H
