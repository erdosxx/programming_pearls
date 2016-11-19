#ifndef ALGORITHM_ANALYSIS_BINARY_SEARCH_K_CIRCULAR_ARRAY_H
#define ALGORITHM_ANALYSIS_BINARY_SEARCH_K_CIRCULAR_ARRAY_H
// 12.3.2 Variant Search a cyclically sorted array

#include <vector>

using std::vector;

enum {NOT_EXIST= -1};

// search in ascending sorted array.
int Search_k_circular(const vector<int>& A, const int& k) {
    if(A[0] == k) {
        return 0;
    }

    size_t left = 0;
    size_t right = A.size() -1;
    size_t middle;
    int position = NOT_EXIST;

    if (k > A[0]) {
        while (left <= right) {
            middle = left + (right - left)/2;
            if (A[0] <= A[middle] && A[middle] < k) {
                left = middle +1;
            } else if (A[middle] > k || A[middle] < A[0]) {
                right = middle -1;
            } else { // A[middle] == k
                position = middle;
                return position;
            }

        }
    } else { // k < A[0]
        while (left <= right) {
            middle = left + (right - left)/2;
            if (A[0] <= A[middle]) {
                left = middle +1;
            } else if (k < A[middle] && A[middle] < A[0]) {
                right = middle -1;
            } else if (A[middle] < k) {
                left = middle +1;
            } else { // A[middle] == k
                position = middle;
                return position;
            }
        }
    }

    return position;
}

#endif //ALGORITHM_ANALYSIS_BINARY_SEARCH_K_CIRCULAR_ARRAY_H
