#ifndef ALGORITHM_ANALYSIS_REBUILD_BST_PREORDER_H
#define ALGORITHM_ANALYSIS_REBUILD_BST_PREORDER_H
// 15.5 Reconstruct a BST from traversal data

#include <memory>
#include <string>
#include <vector>

#include "BST_prototype.h"

using std::make_unique;
using std::unique_ptr;
using std::vector;

// Builds a BST from preorder_sequence[start : end - 1].
unique_ptr<BSTNode<int>> RebuildBSTFromPreorderHelper(
        const vector<int>& preorder_sequence, int start, int end) {
    if (start >= end) {
        return nullptr;
    }

    int right_subtree_start_idx = start + 1;
    while (right_subtree_start_idx < end &&
           preorder_sequence[right_subtree_start_idx] < preorder_sequence[start]) {
        ++right_subtree_start_idx;
    }

    return make_unique<BSTNode<int>>(
            BSTNode<int>{preorder_sequence[start],
                         RebuildBSTFromPreorderHelper(preorder_sequence, start + 1,
                                                      right_subtree_start_idx),
                         RebuildBSTFromPreorderHelper(preorder_sequence,
                                                      right_subtree_start_idx, end)});
}

unique_ptr<BSTNode<int>> RebuildBSTFromPreorder(
        const vector<int>& preorder_sequence) {
    return RebuildBSTFromPreorderHelper(preorder_sequence, 0,
                                        preorder_sequence.size());
}

#endif //ALGORITHM_ANALYSIS_REBUILD_BST_PREORDER_H
