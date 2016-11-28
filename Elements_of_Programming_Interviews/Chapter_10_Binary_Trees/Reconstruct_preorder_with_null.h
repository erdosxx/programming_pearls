#ifndef ALGORITHM_ANALYSIS_RECONSTRUCT_PREORDER_WITH_NULL_H
#define ALGORITHM_ANALYSIS_RECONSTRUCT_PREORDER_WITH_NULL_H
// 10.13 Reconstruct a binary tree from a preorder traversal with markers

#include <memory>
#include <random>
#include <vector>

#include "Binary_tree_prototype.h"

using std::make_unique;
using std::unique_ptr;
using std::vector;
using btree::BinaryTreeNode;

// Reconstructs the subtree that is rooted at subtreeIdx.
unique_ptr<BinaryTreeNode<int>> ReconstructPreorderHelper(
        const vector<int*>& preorder, int* subtree_idx_pointer) {
    int& subtree_idx = *subtree_idx_pointer;
    int* subtree_key = preorder[subtree_idx++];

    if (subtree_key == nullptr) {
        return nullptr;
    }
    // Note that ReconstructPreorderHelper updates subtree_idx. So the order of
    // following two calls are critical.
    auto left_subtree =
            ReconstructPreorderHelper(preorder, subtree_idx_pointer);
    auto right_subtree =
            ReconstructPreorderHelper(preorder, subtree_idx_pointer);
    return make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{
            *subtree_key, move(left_subtree), move(right_subtree)});
}

unique_ptr<BinaryTreeNode<int>> ReconstructPreorder(
        const vector<int*>& preorder) {
    int subtree_idx = 0;
    return ReconstructPreorderHelper(preorder, &subtree_idx);
}

template <typename T>
void GenPreorderWithNull(const unique_ptr<BinaryTreeNode<T>>& n,
                         vector<T*>* p) {
    if (!n) {
        p->emplace_back(nullptr);
        return;
    }

    p->emplace_back(&(n->data));
    GenPreorderWithNull(n->left, p);
    GenPreorderWithNull(n->right, p);
}

#endif //ALGORITHM_ANALYSIS_RECONSTRUCT_PREORDER_WITH_NULL_H
