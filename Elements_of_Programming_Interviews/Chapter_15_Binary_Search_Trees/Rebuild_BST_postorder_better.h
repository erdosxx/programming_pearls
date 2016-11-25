#ifndef ALGORITHM_ANALYSIS_REBUILD_BST_POSTORDER_BETTER_H
#define ALGORITHM_ANALYSIS_REBUILD_BST_POSTORDER_BETTER_H

#include <limits>
#include <memory>
#include <vector>

#include "BST_prototype.h"

using std::make_unique;
using std::numeric_limits;
using std::unique_ptr;
using std::vector;

namespace improved {

    // Builds a BST from postorder_sequence on keys in (lower_bound :
    // upper_bound).
    unique_ptr<BSTNode<int>> RebuildBSTFromPostorderHelper(
            const vector<int> &postorder_sequence, int lower_bound, int upper_bound,
            int *root_idx) {
        if (*root_idx < 0) {
            return nullptr;
        }

        int root = postorder_sequence[*root_idx];
        if (root < lower_bound || root > upper_bound) {
            return nullptr;
        }
        --*root_idx;
        auto right_subtree = RebuildBSTFromPostorderHelper(postorder_sequence, root,
                                                           upper_bound, root_idx);
        auto left_subtree = RebuildBSTFromPostorderHelper(
                postorder_sequence, lower_bound, root, root_idx);
        return make_unique<BSTNode<int>>(
                BSTNode<int>{root, move(left_subtree), move(right_subtree)});
    }

    unique_ptr<BSTNode<int>> RebuildBSTFromPostorder(
            const vector<int> &postorder_sequence) {
        int root_idx = postorder_sequence.size() - 1;
        return RebuildBSTFromPostorderHelper(postorder_sequence,
                                             numeric_limits<int>::min(),
                                             numeric_limits<int>::max(), &root_idx);
    }
}

#endif //ALGORITHM_ANALYSIS_REBUILD_BST_POSTORDER_BETTER_H
