#ifndef ALGORITHM_ANALYSIS_SEARCH_POSTINGS_LIST_RECURSIVE_H
#define ALGORITHM_ANALYSIS_SEARCH_POSTINGS_LIST_RECURSIVE_H

#include <cassert>
#include <memory>

#include "Postings_list_prototype.h"

using std::make_shared;
using std::shared_ptr;

namespace postings_rec {
    enum {UNDIFINED = -1};
    void SetJumpOrderHelper(const shared_ptr<PostingListNode> &L, int *order);

// @include
    void SetJumpOrder(const shared_ptr<PostingListNode> &L) {
        int order = 0;
        SetJumpOrderHelper(L, &order);
    }

    void SetJumpOrderHelper(const shared_ptr<PostingListNode> &L, int *order) {
        if (L && L->order == UNDIFINED) {
            L->order = (*order)++;
            SetJumpOrderHelper(L->jump, order);
            SetJumpOrderHelper(L->next, order);
        }
    }
// @exclude
}

#endif //ALGORITHM_ANALYSIS_SEARCH_POSTINGS_LIST_RECURSIVE_H
