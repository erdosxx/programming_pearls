#ifndef ALGORITHM_ANALYSIS_RECONSTRUCT_POSTORDER_WITH_NULL_H
#define ALGORITHM_ANALYSIS_RECONSTRUCT_POSTORDER_WITH_NULL_H
// 10.13.1 Variant Reconstruct a binary tree from a preorder traversal with markers

#include <memory>
#include <random>
#include <vector>

#include "Binary_tree_prototype.h"

using std::make_unique;
using std::unique_ptr;
using std::vector;
using btree::BinaryTreeNode;

// Reconstructs the subtree that is rooted at subtreeIdx.
unique_ptr<BinaryTreeNode<int>> ReconstructPostorderHelper(
        const vector<int*>& postorder, int* subtree_idx_pointer) {
    int& subtree_idx = *subtree_idx_pointer;
    int* subtree_key = postorder[subtree_idx--];

    if (subtree_key == nullptr) {
        return nullptr;
    }
    // Note that ReconstructPostderHelper updates subtree_idx. So the order of
    // following two calls are critical.
    auto right_subtree =
            ReconstructPostorderHelper(postorder, subtree_idx_pointer);
    auto left_subtree =
            ReconstructPostorderHelper(postorder, subtree_idx_pointer);
    return make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{
            *subtree_key, move(left_subtree), move(right_subtree)});
}

unique_ptr<BinaryTreeNode<int>> ReconstructPostorder(
        const vector<int*>& postorder) {
    int subtree_idx = postorder.size()-1;
    return ReconstructPostorderHelper(postorder, &subtree_idx);
}

template <typename T>
void GenPostorderWithNull(const unique_ptr<BinaryTreeNode<T>>& n,
                         vector<T*>* p) {
    if (!n) {
        p->emplace_back(nullptr);
        return;
    }

    GenPostorderWithNull(n->left, p);
    GenPostorderWithNull(n->right, p);
    p->emplace_back(&(n->data));
}

#endif //ALGORITHM_ANALYSIS_RECONSTRUCT_POSTORDER_WITH_NULL_H
