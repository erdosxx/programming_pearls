#ifndef ALGORITHM_ANALYSIS_RANGE_LOOKUP_BST_H
#define ALGORITHM_ANALYSIS_RANGE_LOOKUP_BST_H
// 15.12 The range lookup problem

#include <memory>
#include <vector>

#include "BST_prototype.h"

using std::make_unique;
using std::unique_ptr;
using std::vector;

struct Interval;
void RangeLookupInBSTHelper(const unique_ptr<BSTNode<int>>&, const Interval&,
                            vector<int>&);

// @include
struct Interval {
    int left, right;
};

vector<int> RangeLookupInBST(const unique_ptr<BSTNode<int>>& tree,
                             const Interval& interval) {
    vector<int> result;
    RangeLookupInBSTHelper(tree, interval, result);
    return result;
}

void RangeLookupInBSTHelper(const unique_ptr<BSTNode<int>>& tree,
                            const Interval& interval, vector<int>& result) {
    if (tree == nullptr) {
        return;
    }
    if (interval.left <= tree->data && tree->data <= interval.right) {
        // tree->data lies in the interval.
        RangeLookupInBSTHelper(tree->left, interval, result);
        result.emplace_back(tree->data);
        RangeLookupInBSTHelper(tree->right, interval, result);
    } else if (interval.left > tree->data) {
        RangeLookupInBSTHelper(tree->right, interval, result);
    } else {  // interval.right > tree->data
        RangeLookupInBSTHelper(tree->left, interval, result);
    }
}
// @exclude

#endif //ALGORITHM_ANALYSIS_RANGE_LOOKUP_BST_H
