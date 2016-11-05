#ifndef ALGORITHM_ANALYSIS_LINKED_LIST_BOOT_CAMP_H
#define ALGORITHM_ANALYSIS_LINKED_LIST_BOOT_CAMP_H

#include <memory>
#include "Linked_list_prototype.h"

shared_ptr<ListNode<int>> SearchList(shared_ptr<ListNode<int>> L, int key) {
    while (L && L->data != key) {
        L = L->next;
    }

    return L;
}

// Insert new_node after node.
void InsertAfter(const shared_ptr<ListNode<int>>& node,
                const shared_ptr<ListNode<int>>& new_node) {
    new_node->next = node->next;
    node->next = new_node;
}

// Delete the node past this one.
void DeleteAfter(const shared_ptr<ListNode<int>>& node) {
    if (node && node->next) {
        node->next = node->next->next;
    }
}

#endif //ALGORITHM_ANALYSIS_LINKED_LIST_BOOT_CAMP_H
