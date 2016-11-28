#ifndef ALGORITHM_ANALYSIS_BUILD_BST_FROM_SORTED_ARRAY_H
#define ALGORITHM_ANALYSIS_BUILD_BST_FROM_SORTED_ARRAY_H
// 15.9 Build a minimum height BST from a sorted array

#include <memory>
#include <vector>

#include "BST_prototype.h"

using std::make_unique;
using std::unique_ptr;
using std::vector;

// Build a min-height BST over the entries in A[start : end - 1].
unique_ptr<BSTNode<int>> BuildMinHeightBSTFromSortedArrayHelper(
        const vector<int>& A, const int& start, const int& end) {
  if (start >= end) {
    return nullptr;
  }

  int mid = start + ((end - start) / 2);

  return make_unique<BSTNode<int>>(BSTNode<int>{
          A[mid], BuildMinHeightBSTFromSortedArrayHelper(A, start, mid),
          BuildMinHeightBSTFromSortedArrayHelper(A, mid + 1, end)});
}

unique_ptr<BSTNode<int>> BuildMinHeightBSTFromSortedArray(
        const vector<int>& A) {
  return BuildMinHeightBSTFromSortedArrayHelper(A, 0, A.size());
}


#endif //ALGORITHM_ANALYSIS_BUILD_BST_FROM_SORTED_ARRAY_H
