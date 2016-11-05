#ifndef ALGORITHM_ANALYSIS_REVERSE_LINKED_LIST_RECURSIVE_H
#define ALGORITHM_ANALYSIS_REVERSE_LINKED_LIST_RECURSIVE_H

#include <memory>

#include "Linked_list_prototype.h"

using std::shared_ptr;

// 1 -> 2 -> 3 -> 4 -> 5
// 1 -> 2 -> 3 -> 4 <- 5
// 1 -> 2 -> 3 <- 4 <- 5
// 1 -> 2 <- 3 <- 4 <- 5
// 1 <- 2 <- 3 <- 4 <- 5
//                     new_head

namespace rec {
// @include
    shared_ptr <ListNode<int>> ReverseLinkedList(
            const shared_ptr <ListNode<int>> &head) {
        if (!head || !head->next) { // null list or singleton list
            return head;
        }

        auto new_head = rec::ReverseLinkedList(head->next);
        head->next->next = head;
        head->next = nullptr;
        return new_head;
    }
// @exclude
}

#endif //ALGORITHM_ANALYSIS_REVERSE_LINKED_LIST_RECURSIVE_H
