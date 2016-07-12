#ifndef ALGORITHM_ANALYSIS_REBUILD_BST_PREORDER_BETTER_H
#define ALGORITHM_ANALYSIS_REBUILD_BST_PREORDER_BETTER_H

#include <limits>
#include <memory>
#include <vector>

#include "BST_prototype.h"

using std::make_unique;
using std::numeric_limits;
using std::unique_ptr;
using std::vector;

namespace improved {

    unique_ptr<BSTNode<int>> RebuildBSTFromPreorderOnValueRange(
            const vector<int> &, int, int, int *);

// @include
    unique_ptr<BSTNode<int>> RebuildBSTFromPreorder(
            const vector<int> &preorder_sequence) {
        int root_idx = 0;
        return RebuildBSTFromPreorderOnValueRange(
                preorder_sequence, numeric_limits<int>::min(),
                numeric_limits<int>::max(), &root_idx);
    }

// Builds a BST on the subtree rooted at root_idx from preorder_sequence on
// keys in (lower_bound, upper_bound).
    unique_ptr<BSTNode<int>> RebuildBSTFromPreorderOnValueRange(
            const vector<int> &preorder_sequence, int lower_bound, int upper_bound,
            int *root_idx_pointer) {
        //int &root_idx = *root_idx_pointer;
        if (*root_idx_pointer == preorder_sequence.size()) {
            return nullptr;
        }

        int root = preorder_sequence[*root_idx_pointer];
        if (root < lower_bound || root > upper_bound) {
            return nullptr;
        }
        ++(*root_idx_pointer);
        // Note that RebuildBSTFromPreorderOnValueRange updates root_idx. So the
        // order of following two calls are critical.
        auto left_subtree = RebuildBSTFromPreorderOnValueRange(
                preorder_sequence, lower_bound, root, root_idx_pointer);
        auto right_subtree = RebuildBSTFromPreorderOnValueRange(
                preorder_sequence, root, upper_bound, root_idx_pointer);
        return make_unique<BSTNode<int>>(
                BSTNode<int>{root, move(left_subtree), move(right_subtree)});
    }
// @exclude
}

#endif //ALGORITHM_ANALYSIS_REBUILD_BST_PREORDER_BETTER_H
