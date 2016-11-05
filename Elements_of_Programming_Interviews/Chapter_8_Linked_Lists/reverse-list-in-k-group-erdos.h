#ifndef ALGORITHM_ANALYSIS_REVERSE_LIST_IN_K_GROUP_ERDOS_H
#define ALGORITHM_ANALYSIS_REVERSE_LIST_IN_K_GROUP_ERDOS_H

#include <memory>
#include "Linked_list_prototype.h"

using std::shared_ptr;
using std::make_shared;
using node_ptr = shared_ptr<ListNode<int>>;

node_ptr reverse_list_first_k (const node_ptr & sublist_predecessor, int k);
bool check_k_elements_exist (node_ptr sublist_predecessor, size_t k);

node_ptr reverse_list_in_k_group (const node_ptr & L, const size_t & k) {
    if (k <= 1 || L == nullptr) {
        return L;
    }

    // for the start case, we use dummy head.
    node_ptr dummy_head = make_shared<ListNode<int>>(ListNode<int> {0, L});

    node_ptr new_head;
    new_head = reverse_list_first_k(dummy_head, k);

    while (new_head != nullptr){
        new_head = reverse_list_first_k(new_head, k);
    };

    return dummy_head->next;
}

//input: sublist_predecessor, k=3
//    sublist_predecessor -> 1 -> 2 -> 3 -> 4
//    sublist_predecessor -> 3 -> 2 -> 1 -> 4
// output:                             |-- current
node_ptr reverse_list_first_k (const node_ptr & sublist_predecessor, int k) {
    if (sublist_predecessor == nullptr) {
        return sublist_predecessor;
    }

    if (k == 1) {
        return sublist_predecessor->next;
    }

    // K >=2; check k elements are available in list
    if (check_k_elements_exist(sublist_predecessor, k)) {
        node_ptr curr = sublist_predecessor->next;
        node_ptr c_next;

        while (--k >0) {
            c_next = curr->next;
            curr->next = c_next->next;
            c_next->next = sublist_predecessor->next;
            sublist_predecessor->next = c_next;
        }

        return curr;
    } else { // not enough elements
        return nullptr;
    }
}

// check k elements which are next to head
// sublist_predecessor -> 1 -> 2 -> 3
// 3 elements are exist. (sublist_predecessor, 3]
bool check_k_elements_exist (node_ptr sublist_predecessor, size_t k) {
    if (sublist_predecessor == nullptr || k == 0) {
        return false;
    }

    size_t & num_of_remaining = k;

    while (num_of_remaining) {
        sublist_predecessor = sublist_predecessor->next;
        if(!sublist_predecessor) {
            break;
        }
        num_of_remaining--;
    }
    return num_of_remaining==0 ? true : false;
}


#endif //ALGORITHM_ANALYSIS_REVERSE_LIST_IN_K_GROUP_ERDOS_H
