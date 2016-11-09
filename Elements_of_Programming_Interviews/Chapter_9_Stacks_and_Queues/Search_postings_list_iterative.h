#ifndef ALGORITHM_ANALYSIS_SEARCH_POSTINGS_LIST_ITERATIVE_H
#define ALGORITHM_ANALYSIS_SEARCH_POSTINGS_LIST_ITERATIVE_H
// 9.5 Search a postings list

#include <cassert>
#include <memory>
#include <stack>

#include "Postings_list_prototype.h"

using std::make_shared;
using std::shared_ptr;
using std::stack;

// Similiar DFS with jump edge first.
namespace postings_itr {
    enum {UNDIFINED= -1};
// @include
    void SetJumpOrder(const shared_ptr<PostingListNode> &L) {
        stack<shared_ptr<PostingListNode>> s;
        int order = 0;
        s.emplace(L);
        while (!s.empty()) {
            auto curr = s.top();
            s.pop();
            if (curr && curr->order == UNDIFINED) {
                curr->order = order++;
                // Stack is last-in, first-out, and we want to process
                // the jump node first, so push next, then push jump.
                s.emplace(curr->next);
                s.emplace(curr->jump);
            }
        }
    }
// @exclude
}

#endif //ALGORITHM_ANALYSIS_SEARCH_POSTINGS_LIST_ITERATIVE_H
