#ifndef ALGORITHM_ANALYSIS_ORDER_STATISTIC_H
#define ALGORITHM_ANALYSIS_ORDER_STATISTIC_H
// 12.8 Find the kth largest element

#include <algorithm>
#include <functional>
#include <stdexcept>
#include <vector>
#include <random>

using std::greater;
using std::length_error;
using std::less;
using std::max;
using std::min;
using std::swap;
using std::vector;
using std::default_random_engine;
using std::random_device;
using std::uniform_int_distribution;

// Partition A[left : right] around pivot_idx, returns the new index of the
// pivot, new_pivot_idx, after partition. After partitioning,
// A[left : new_pivot_idx - 1] contains elements that are greater than the
// pivot, and A[new_pivot_idx + 1 : right] contains elements that are less
// than the pivot.
//
// Note: "less than" is defined by the Compare object.
//
// Returns the new index of the pivot element after partition.
template <typename Compare>
int PartitionAroundPivot(int left, int right, int pivot_idx, Compare comp,
                         vector<int>* A_ptr) {
    vector<int>& A = *A_ptr;
    int pivot_value = A[pivot_idx];
    int new_pivot_idx = left;

    swap(A[pivot_idx], A[right]);
    for (int i = left; i < right; ++i) {
        if (comp(A[i], pivot_value)) {
            swap(A[i], A[new_pivot_idx++]);
        }
    }
    swap(A[right], A[new_pivot_idx]);
    return new_pivot_idx;
}

template <typename Compare>
int FindKth(int k, Compare comp, vector<int>* A_ptr) {
    vector<int>& A = *A_ptr;

    int left = 0;
    int right = A.size() - 1;

    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
    while (left <= right) {
        // Generates a random integer in [left, right].
        int pivot_idx = uniform_int_distribution<int>{left, right}(gen);

        int new_pivot_idx =
                PartitionAroundPivot(left, right, pivot_idx, comp, A_ptr);

        if (new_pivot_idx == k - 1) {
            return A[new_pivot_idx];
        } else if (new_pivot_idx > k - 1) {
            right = new_pivot_idx - 1;
        } else {  // new_pivot_idx < k - 1.
            left = new_pivot_idx + 1;
        }
    }
    throw length_error("no k-th node in array A");
}

// The numbering starts from one, i.e., if A = [3,1,-1,2] then
// FindKthLargest(1, A) returns 3, FindKthLargest(2, A) returns 2,
// FindKthLargest(3, A) returns 1, and FindKthLargest(4, A) returns -1.
int FindKthLargest(int k, vector<int>* A_ptr) {
    return FindKth(k, greater<int>(), A_ptr);
}

// The numbering starts from one, i.e., if A = [3,1,-1,2] then
// FindKthSmallest(1, A) returns -1, FindKthSmallest(2, A) returns 1,
// FindKthSmallest(3, A) returns 2, and FindKthSmallest(4, A) returns 3.
int FindKthSmallest(int k, vector<int>* A_ptr) {
    return FindKth(k, less<int>(), A_ptr);
}

#endif //ALGORITHM_ANALYSIS_ORDER_STATISTIC_H
