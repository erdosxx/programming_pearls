#ifndef ALGORITHM_ANALYSIS_BUILD_BST_FROM_SORTED_ARRAY_H
#define ALGORITHM_ANALYSIS_BUILD_BST_FROM_SORTED_ARRAY_H

#include <memory>
#include <vector>

#include "BST_prototype.h"

using std::make_unique;
using std::unique_ptr;
using std::vector;

unique_ptr<BSTNode<int>> BuildMinHeightBSTFromSortedArrayHelper(
        const vector<int>&, int, int);

// @include
unique_ptr<BSTNode<int>> BuildMinHeightBSTFromSortedArray(
        const vector<int>& A) {
  return BuildMinHeightBSTFromSortedArrayHelper(A, 0, A.size());
}

// Build a min-height BST over the entries in A[start : end - 1].
unique_ptr<BSTNode<int>> BuildMinHeightBSTFromSortedArrayHelper(
        const vector<int>& A, int start, int end) {
  if (start >= end) {
    return nullptr;
  }

  int mid = start + ((end - start) / 2);

  return make_unique<BSTNode<int>>(BSTNode<int>{
          A[mid], BuildMinHeightBSTFromSortedArrayHelper(A, start, mid),
          BuildMinHeightBSTFromSortedArrayHelper(A, mid + 1, end)});
}
// @exclude

#endif //ALGORITHM_ANALYSIS_BUILD_BST_FROM_SORTED_ARRAY_H
