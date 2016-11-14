#ifndef ALGORITHM_ANALYSIS_MERGE_SORTED_DOUBLY_LINKED_LISTS_H
#define ALGORITHM_ANALYSIS_MERGE_SORTED_DOUBLY_LINKED_LISTS_H
// 8.1.1 Variant Merge two sorted lists

#include <memory>
#include "Doubly_linked_list_prototype.h"

using std::shared_ptr;
using std::make_shared;
//using DL::ListNode;
using node_ptr_type = shared_ptr<DL::ListNode<int>>;

void AppendDoublyNode(node_ptr_type* node, node_ptr_type* tail) {
    (*tail)->next = *node;
    (*node)->prev = *tail;
    *tail = *node;
    *node = (*node)->next;
}

node_ptr_type MergeTwoSortedDoublyLists(node_ptr_type L1,
                                              node_ptr_type L2) {
    node_ptr_type dummy(new DL::ListNode<int>);
    //node_ptr_type dummy = make_shared<DL::ListNode<int>>(DL::ListNode<int>{});

    node_ptr_type tail = dummy;

    while(L1 && L2) {
        AppendDoublyNode(L1->data < L2->data ? &L1 : &L2, &tail);
    }

    if (L1) { // L1 is remained
        tail->next = L1;
        L1->prev = tail;
    } else {  // L2 is remained
        tail->next = L2;
        L2->prev = tail;
    }

    return dummy->next;
}
#endif //ALGORITHM_ANALYSIS_MERGE_SORTED_DOUBLY_LINKED_LISTS_H
