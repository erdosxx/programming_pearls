#ifndef ALGORITHM_ANALYSIS_REVERSE_LINKED_LIST_FROM_S_TO_F_H
#define ALGORITHM_ANALYSIS_REVERSE_LINKED_LIST_FROM_S_TO_F_H

#include <memory>

#include "Linked_list_prototype.h"

using std::make_shared;
using std::shared_ptr;

// @include
shared_ptr<ListNode<int>> ReverseSublist(shared_ptr<ListNode<int>> L,
                                         int start, int finish) {
    if (start == finish) {  // No need to reverse since start == finish.
        return L;
    }

    auto dummy_head = make_shared<ListNode<int>>(ListNode<int>{0, L});
    auto sublist_head = dummy_head;
    int k = 1;
    while (k++ < start) {
        sublist_head = sublist_head->next;
    }

    // Reverses sublist.
    // h -> A -> B -> C -> D
    // h -> B -> A -> C -> D
    // h -> C -> B -> A -> D
    // h -> D -> C -> B -> A
    auto sublist_iter = sublist_head->next;
    while (start++ < finish) {
        auto temp = sublist_iter->next;
        sublist_iter->next = temp->next;
        temp->next = sublist_head->next;
        sublist_head->next = temp;
    }
    return dummy_head->next;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_REVERSE_LINKED_LIST_FROM_S_TO_F_H
