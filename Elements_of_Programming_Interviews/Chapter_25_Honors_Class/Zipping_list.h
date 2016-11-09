#ifndef ALGORITHM_ANALYSIS_ZIPPING_LIST_H
#define ALGORITHM_ANALYSIS_ZIPPING_LIST_H
// 25.9 Implement list zipping

#include <memory>
#include <string>

#include "Linked_list_prototype.h"
#include "Reverse_linked_list_iterative.h"

using std::make_shared;
using std::shared_ptr;

// @include
shared_ptr<ListNode<int>> ZippingLinkedList(
        const shared_ptr<ListNode<int>>& L) {
    if (!L || !L->next) {
        return L;
    }

    // Finds the second half of L.
    auto slow = L;
    auto fast = L;

    while (fast && fast->next) {
        fast = fast->next->next;
        slow = slow->next;
    }

    auto first_half_head = L;
    auto second_half_head = slow->next;
    slow->next = nullptr;  // Splits the list into two lists.

    second_half_head = ReverseLinkedList(second_half_head);

    // Interleave the first half and the reversed of the second half.
    auto first_half_iter = first_half_head;
    auto second_half_iter = second_half_head;

    while (second_half_iter) {
        auto temp = second_half_iter->next;
        second_half_iter->next = first_half_iter->next;
        first_half_iter->next = second_half_iter;

        // update for next loop
        first_half_iter = first_half_iter->next->next;
        second_half_iter = temp;
    }
    return first_half_head;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_ZIPPING_LIST_H
