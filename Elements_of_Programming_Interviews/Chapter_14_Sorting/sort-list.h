#ifndef ALGORITHM_ANALYSIS_SORT_LIST_H
#define ALGORITHM_ANALYSIS_SORT_LIST_H

#include <memory>
#include <string>

#include "Linked_list_prototype.h"
#include "Merge_sorted_lists.h"

using std::make_shared;

// @include
shared_ptr<ListNode<int>> StableSortList(const shared_ptr<ListNode<int>>& L) {
    // Base cases: L is empty or a single node, nothing to do.
    if (L == nullptr || L->next == nullptr) {
        return L;
    }

    // Find the midpoint of L using a slow and a fast pointer.
    shared_ptr<ListNode<int>> pre_slow = nullptr;
    auto slow = L;
    auto fast = L;

    while (fast && fast->next) {
        pre_slow = slow;
        fast = fast->next->next;
        slow = slow->next;
    }

    pre_slow->next = nullptr;  // Splits the list into two equal-sized lists.

    return MergeTwoSortedLists(StableSortList(L), StableSortList(slow));
}
// @exclude


#endif //ALGORITHM_ANALYSIS_SORT_LIST_H
