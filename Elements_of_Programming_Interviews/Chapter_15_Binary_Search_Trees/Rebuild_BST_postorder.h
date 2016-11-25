#ifndef ALGORITHM_ANALYSIS_REBUILD_BST_POSTORDER_H
#define ALGORITHM_ANALYSIS_REBUILD_BST_POSTORDER_H

#include <limits>
#include <memory>
#include <string>
#include <vector>

#include "BST_prototype.h"

using std::make_unique;
using std::numeric_limits;
using std::unique_ptr;
using std::vector;

// Build a BST based on postorder[start : end - 1], return its root.
unique_ptr<BSTNode<int>> RebuildBSTFromPostorderHelper(
        const vector<int>& postorder, int start, int end) {
    if (start < end) {
        int right_subtree_begin_idx = start;
        while (right_subtree_begin_idx < end && postorder[right_subtree_begin_idx] < postorder[end - 1]) {
            ++right_subtree_begin_idx;
        }

        return make_unique<BSTNode<int>>(
                BSTNode<int>{postorder[end - 1],
                             RebuildBSTFromPostorderHelper(postorder, start, right_subtree_begin_idx),
                             RebuildBSTFromPostorderHelper(postorder, right_subtree_begin_idx, end - 1)});
    }

    return nullptr;
}

// Given a postorder traversal of a BST, return its root.
unique_ptr<BSTNode<int>> RebuildBSTFromPostorder(const vector<int>& postorder) {
    return RebuildBSTFromPostorderHelper(postorder, 0, postorder.size());
}

#endif //ALGORITHM_ANALYSIS_REBUILD_BST_POSTORDER_H
