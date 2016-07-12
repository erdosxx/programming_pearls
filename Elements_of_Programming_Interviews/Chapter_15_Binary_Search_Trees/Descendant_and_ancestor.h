#ifndef ALGORITHM_ANALYSIS_DESCENDANT_AND_ANCESTOR_H
#define ALGORITHM_ANALYSIS_DESCENDANT_AND_ANCESTOR_H

#include <memory>

#include "BST_prototype.h"

using std::make_unique;
using std::unique_ptr;

bool SearchTarget(const unique_ptr<BSTNode<int>>&,
                  const unique_ptr<BSTNode<int>>&);

// @include
bool PairIncludesAncestorAndDescendantOfM(
        const unique_ptr<BSTNode<int>>& possible_anc_or_desc_0,
        const unique_ptr<BSTNode<int>>& possible_anc_or_desc_1,
        const unique_ptr<BSTNode<int>>& middle) {
    auto* search_0 = possible_anc_or_desc_0.get();
    auto* search_1 = possible_anc_or_desc_1.get();

    // Perform interleaved searching from possible_anc_or_desc_0 and
    // possible_anc_or_desc_1 for middle.
    while (search_0 != possible_anc_or_desc_1.get() &&
           search_0 != middle.get() &&
           search_1 != possible_anc_or_desc_0.get() &&
           search_1 != middle.get() &&
            (search_0 || search_1)) {
        if (search_0) {
            search_0 = search_0->data > middle->data ? search_0->left.get()
                                                     : search_0->right.get();
        }
        if (search_1) {
            search_1 = search_1->data > middle->data ? search_1->left.get()
                                                     : search_1->right.get();
        }
    }

    // If both searches were unsuccessful, or we got from
    // possible_anc_or_desc_0 to possible_anc_or_desc_1 without seeing middle,
    // or from possible_anc_or_desc_1 to possible_anc_or_desc_0 without seeing
    // middle, middle cannot lie between possible_anc_or_desc_0 and
    // possible_anc_or_desc_1.
    if ((search_0 != middle.get() && search_1 != middle.get()) ||
        search_0 == possible_anc_or_desc_1.get() ||
        search_1 == possible_anc_or_desc_0.get()) {
        return false;
    }

    // If we get here, we already know one of possible_anc_or_desc_0 or
    // possible_anc_or_desc_1 has a path to middle. Check if middle has a path
    // to possible_anc_or_desc_1 or to possible_anc_or_desc_0.
    return search_0 == middle.get()
           ? SearchTarget(middle, possible_anc_or_desc_1)
           : SearchTarget(middle, possible_anc_or_desc_0);
}

bool SearchTarget(const unique_ptr<BSTNode<int>>& from,
                  const unique_ptr<BSTNode<int>>& target) {
    auto* iter = from.get();
    while (iter && iter != target.get()) {
        iter = iter->data > target->data ? iter->left.get() : iter->right.get();
    }
    return iter == target.get();
}
// @exclude

#endif //ALGORITHM_ANALYSIS_DESCENDANT_AND_ANCESTOR_H
