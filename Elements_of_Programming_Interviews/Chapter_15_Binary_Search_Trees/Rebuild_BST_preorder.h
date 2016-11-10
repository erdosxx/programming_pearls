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

unique_ptr<BSTNode<int>> RebuildBSTFromPreorderHelper(const vector<int>&, int,
                                                      int);

// @include
unique_ptr<BSTNode<int>> RebuildBSTFromPreorder(
        const vector<int>& preorder_sequence) {
    return RebuildBSTFromPreorderHelper(preorder_sequence, 0,
                                        preorder_sequence.size());
}

// Builds a BST from preorder_sequence[start : end - 1].
unique_ptr<BSTNode<int>> RebuildBSTFromPreorderHelper(
        const vector<int>& preorder_sequence, int start, int end) {
    if (start >= end) {
        return nullptr;
    }
    int transition_point = start + 1;
    while (transition_point < end &&
           preorder_sequence[transition_point] < preorder_sequence[start]) {
        ++transition_point;
    }
    return make_unique<BSTNode<int>>(
            BSTNode<int>{preorder_sequence[start],
                         RebuildBSTFromPreorderHelper(preorder_sequence, start + 1,
                                                      transition_point),
                         RebuildBSTFromPreorderHelper(preorder_sequence,
                                                      transition_point, end)});
}
// @exclude

#endif //ALGORITHM_ANALYSIS_REBUILD_BST_PREORDER_H
