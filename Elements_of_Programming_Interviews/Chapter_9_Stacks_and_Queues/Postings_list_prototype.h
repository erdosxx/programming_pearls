#ifndef ALGORITHM_ANALYSIS_POSTINGS_LIST_PROTOTYPE_H
#define ALGORITHM_ANALYSIS_POSTINGS_LIST_PROTOTYPE_H

#include <memory>

using std::shared_ptr;

// @include
class PostingListNode {
public:
    int order;
    shared_ptr<PostingListNode> next, jump;
};
// @exclude

#endif //ALGORITHM_ANALYSIS_POSTINGS_LIST_PROTOTYPE_H
