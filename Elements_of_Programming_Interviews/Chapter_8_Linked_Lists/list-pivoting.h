#ifndef ALGORITHM_ANALYSIS_LIST_PIVOTING_H
#define ALGORITHM_ANALYSIS_LIST_PIVOTING_H

#include <memory>

#include "Linked_list_prototype.h"
#include "Merge_sorted_lists.h"  // uses AppendNode().

using std::make_shared;
using std::shared_ptr;

// @include
shared_ptr<ListNode<int>> ListPivoting(const shared_ptr<ListNode<int>>& L,
                                       int x) {
    shared_ptr<ListNode<int>> less_head(new ListNode<int>);
    shared_ptr<ListNode<int>> equal_head(new ListNode<int>);
    shared_ptr<ListNode<int>> greater_head(new ListNode<int>);

    auto less_iter = less_head;
    auto equal_iter = equal_head;
    auto greater_iter = greater_head;

    // Populates the three lists.
    shared_ptr<ListNode<int>> iter = L;

    while (iter) {
        AppendNode(&iter, iter->data < x ? &less_iter : iter->data == x
                                                        ? &equal_iter
                                                        : &greater_iter);
    }

    // Combines the three lists.
    greater_iter->next = nullptr;
    equal_iter->next = greater_head->next;
    less_iter->next = equal_head->next;
    return less_head->next;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_LIST_PIVOTING_H
