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
        int x = start;
        while (x < end && postorder[x] < postorder[end - 1]) {
            ++x;
        }

        return make_unique<BSTNode<int>>(
                BSTNode<int>{postorder[end - 1],
                             RebuildBSTFromPostorderHelper(postorder, start, x),
                             RebuildBSTFromPostorderHelper(postorder, x, end - 1)});
    }

    return nullptr;
}

// Given a postorder traversal of a BST, return its root.
unique_ptr<BSTNode<int>> RebuildBSTFromPostorder(const vector<int>& postorder) {
    return RebuildBSTFromPostorderHelper(postorder, 0, postorder.size());
}

#endif //ALGORITHM_ANALYSIS_REBUILD_BST_POSTORDER_H
