#ifndef ALGORITHM_ANALYSIS_REVERSE_LINKED_LIST_ITERATIVE_H
#define ALGORITHM_ANALYSIS_REVERSE_LINKED_LIST_ITERATIVE_H

#include <memory>

#include "Linked_list_prototype.h"

using std::shared_ptr;

// @include
// reverse linked list
// input: A -> B -> C -> null
// output: null <- A <- B <- C
shared_ptr<ListNode<int>> ReverseLinkedList(
        const shared_ptr<ListNode<int>>& head) {
    shared_ptr<ListNode<int>> prev = nullptr;
    auto curr = head;

    while (curr) {
        auto next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_REVERSE_LINKED_LIST_ITERATIVE_H
