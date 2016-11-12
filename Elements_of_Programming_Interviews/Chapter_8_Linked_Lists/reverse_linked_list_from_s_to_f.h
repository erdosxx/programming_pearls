#ifndef ALGORITHM_ANALYSIS_REVERSE_LINKED_LIST_FROM_S_TO_F_H
#define ALGORITHM_ANALYSIS_REVERSE_LINKED_LIST_FROM_S_TO_F_H
// 8.2 Reverse a single sublist

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

    // This function give same results for [start, finish] = [0, 2] and [start, finish] = [1,3].
    // According to the problem statement, index which starts from 1 is correct.

    // To make simple consistent code for case start=0, we use dummy_head.
    //  1             -> [2              -> 3 -> 4] -> 5 -> 6
    //  sublist_head      sublist_iter
    auto dummy_head = make_shared<ListNode<int>>(ListNode<int>{0, L});
    auto sublist_head = dummy_head;
    int k = 1;
    while (k++ < start) {
        sublist_head = sublist_head->next;
    }

    // Reverses sublist.
    //  1 -> [2 -> 3 -> 4] -> 5 -> 6
    //  1 -> [3 -> 2 -> 4] -> 5 -> 6
    //  1 -> [4 -> 3 -> 2] -> 5 -> 6
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
