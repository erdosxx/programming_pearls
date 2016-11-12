#ifndef ALGORITHM_ANALYSIS_DELETION_LIST_H
#define ALGORITHM_ANALYSIS_DELETION_LIST_H
// 8.6 Delete a node from a singly linked list

#include <memory>

#include "Linked_list_prototype.h"

using std::make_shared;
using std::shared_ptr;

// @include
// Assumes node_to_delete is not tail.
void DeletionFromList(const shared_ptr<ListNode<int>>& node_to_delete) {
    node_to_delete->data = node_to_delete->next->data;
    node_to_delete->next = node_to_delete->next->next;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_DELETION_LIST_H
