#ifndef ALGORITHM_ANALYSIS_REVERSE_LINKED_LIST_ITERATIVE_H
#define ALGORITHM_ANALYSIS_REVERSE_LINKED_LIST_ITERATIVE_H
// 8.2.1 Variant Reverse a single sublist

#include <memory>

#include "Linked_list_prototype.h"

using std::shared_ptr;

// @include
// reverse linked list
// input: A -> B -> C -> null
// output: null <- A <- B <- C
//                           |prev
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

// See TAOCP I p.546 #7.
// P: next,   Q:  curr,   R: prev
shared_ptr<ListNode<int>> ReverseLinkedList_knuth(const shared_ptr<ListNode<int>>& head) {
    auto next = head;
    shared_ptr<ListNode<int>> curr = nullptr;

    while (next) {
        // shift
        // prev-curr-next
        //      prev-curr-next
        auto prev = curr;
        curr = next;
        // next = curr->next;
        next = next->next;

        //reverse link
        curr->next = prev;
    }
    return curr;
}

#endif //ALGORITHM_ANALYSIS_REVERSE_LINKED_LIST_ITERATIVE_H
