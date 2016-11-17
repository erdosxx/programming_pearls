#ifndef ALGORITHM_ANALYSIS_REMOVE_KTH_LAST_LIST_H
#define ALGORITHM_ANALYSIS_REMOVE_KTH_LAST_LIST_H
// 8.7 Remove the kth last element from a list

#include <memory>

#include "Linked_list_prototype.h"

using std::make_shared;
using std::shared_ptr;

// Assumes L has at least k nodes, deletes the k-th last node in L.
shared_ptr<ListNode<int>> RemoveKthLast(const shared_ptr<ListNode<int>>& L,
                                        int k) {
    auto dummy_head = make_shared<ListNode<int>>(ListNode<int>{0, L});

    auto first = dummy_head->next;

    while (k--) {
        first = first->next;
    }

    // When first reach nullptr, make second to k+1 th node.
    auto second = dummy_head;

    while (first) {
        second = second->next;
        first = first->next;
    }
    // second points to the (k + 1)-th last node, deletes its successor(k-th node).
    second->next = second->next->next;
    return dummy_head->next;
}

#endif //ALGORITHM_ANALYSIS_REMOVE_KTH_LAST_LIST_H
