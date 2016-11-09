#ifndef ALGORITHM_ANALYSIS_COPYING_POSTINGS_LIST_H
#define ALGORITHM_ANALYSIS_COPYING_POSTINGS_LIST_H
// 25.10 Copy a postings list

#include <memory>

#include "Postings_list_prototype.h"

using std::make_shared;
using std::shared_ptr;

// @include
shared_ptr<PostingListNode> CopyPostingsList(
        const shared_ptr<PostingListNode>& L) {
    if (L == nullptr) {
        return nullptr;
    }

    // Stage 1: Makes a copy of the original list without assigning the jump
    //          field, and creates the mapping for each node in the original
    //          list to the copied list.
    auto iter = L;
    while (iter) {
        auto new_node = make_shared<PostingListNode>(
                PostingListNode{iter->order, iter->next, nullptr});
        iter->next = new_node;
        iter = new_node->next;
    }

    // Stage 2: Assigns the jump field in the copied list.
    iter = L;
    while (iter) {
        if (iter->jump) {
            iter->next->jump = iter->jump->next;
        }
        iter = iter->next->next;
    }

    // Stage 3: Reverts the original list, and assigns the next field of
    //          the copied list.
    iter = L;
    auto new_list_head = iter->next;
    while (iter->next) {
        auto temp = iter->next;
        iter->next = temp->next;
        iter = temp;
    }
    return new_list_head;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_COPYING_POSTINGS_LIST_H
