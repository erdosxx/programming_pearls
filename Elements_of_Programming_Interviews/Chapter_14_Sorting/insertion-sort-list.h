#ifndef ALGORITHM_ANALYSIS_INSERTION_SORT_LIST_H
#define ALGORITHM_ANALYSIS_INSERTION_SORT_LIST_H
// 14.9 Implement a fast sorting algorithm for lists

#include <memory>

#include "Linked_list_prototype.h"

using std::make_shared;
using std::shared_ptr;

shared_ptr<ListNode<int>> InsertionSort(const shared_ptr<ListNode<int>>& L) {
    auto dummy_head = make_shared<ListNode<int>>(ListNode<int>{0, L});
    auto iter = L;
    // The sublist consisting of nodes up to and including iter is sorted in
    // increasing order. We need to ensure that after we move to iter->next
    // this property continues to hold. We do this by swapping iter->next
    // with its predecessors in the list till it's in the right place.
    while (iter && iter->next) {
        if (iter->data > iter->next->data) {
            auto target = iter->next;
            auto pre = dummy_head;

            while (pre->next->data < target->data) {
                pre = pre->next;
            }

            // pre -> target -> pre_next
            auto temp = pre->next;
            pre->next = target;
            iter->next = target->next;
            target->next = temp;
        } else {
            iter = iter->next;
        }
    }
    return dummy_head->next;
}

#endif //ALGORITHM_ANALYSIS_INSERTION_SORT_LIST_H
