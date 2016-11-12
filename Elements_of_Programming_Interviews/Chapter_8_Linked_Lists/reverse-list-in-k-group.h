#ifndef ALGORITHM_ANALYSIS_REVERSE_LIST_IN_K_GROUP_H
#define ALGORITHM_ANALYSIS_REVERSE_LIST_IN_K_GROUP_H
// 8.2.2 Variant Reverse a single sublist

#include <memory>

#include "Linked_list_prototype.h"
#include "Reverse_linked_list_iterative.h"

using std::make_shared;
using std::shared_ptr;

// @include
shared_ptr<ListNode<int>> ReverseK(const shared_ptr<ListNode<int>>& L, const int k) {
    auto dummy_head = make_shared<ListNode<int>>(ListNode<int>{0, L});

    shared_ptr<ListNode<int>> sublist_predecessor = dummy_head,
    //             dummy_head -> sublist_head
    //      sublist_successor    sublist_tail
            sublist_head = dummy_head->next,
            sublist_successor = dummy_head,
            sublist_tail = dummy_head->next;

    while (sublist_head) {
        // Identify the tail of sublist of k nodes to be reversed.
        int num_remaining = k;

        // sublist_successor : last element for reversing.
        // sublist_successor] -> sublist_tail
        while (num_remaining) {
            sublist_successor = sublist_tail;
            sublist_tail = sublist_tail->next;
            --num_remaining;
            if (!sublist_tail) {
                break;
            }
        }

        if (num_remaining > 0) {
            // Specification says not to reverse.
            return dummy_head->next;
        }

        sublist_successor->next = nullptr;
        ReverseLinkedList(sublist_head);

        // Splice the reversed sublist.
        sublist_predecessor->next = sublist_successor;
        // Go on to the head of next sublist.
        sublist_predecessor = sublist_head;
        sublist_head->next = sublist_tail;

        sublist_head = sublist_tail;
        sublist_successor = nullptr;
    }
    return dummy_head->next;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_REVERSE_LIST_IN_K_GROUP_H
