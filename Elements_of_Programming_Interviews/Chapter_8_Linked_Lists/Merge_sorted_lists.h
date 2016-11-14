#ifndef ALGORITHM_ANALYSIS_MERGE_SORTED_LISTS_H
#define ALGORITHM_ANALYSIS_MERGE_SORTED_LISTS_H
// 8.1 Merge two sorted lists

#include <memory>

using std::shared_ptr;
using std::make_shared;

#include "Linked_list_prototype.h"

void AppendNode(shared_ptr<ListNode<int>>* node,
                shared_ptr<ListNode<int>>* tail) {
    (*tail)->next = *node;
    *tail = *node;  // Updates tail.
    *node = (*node)->next;  // shift to next node
}

// @include
shared_ptr<ListNode<int>> MergeTwoSortedLists(shared_ptr<ListNode<int>> L1,
                                              shared_ptr<ListNode<int>> L2) {
    // Creates a placeholder for the result.
    //shared_ptr<ListNode<int>> dummy_head(new ListNode<int>);
    shared_ptr<ListNode<int>> dummy_head = make_shared<ListNode<int>>(ListNode<int>{});

    // auto tail = dummy_head;
    shared_ptr<ListNode<int>> tail = dummy_head;

    while (L1 && L2) {
        AppendNode(L1->data <= L2->data ? &L1 : &L2, &tail);
    }

    tail->next = L1 ? L1 : L2;

    return dummy_head->next;
}

// @exclude

#endif //ALGORITHM_ANALYSIS_MERGE_SORTED_LISTS_H
