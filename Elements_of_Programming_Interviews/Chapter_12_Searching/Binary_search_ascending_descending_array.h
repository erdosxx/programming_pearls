#ifndef ALGORITHM_ANALYSIS_BINARY_SEARCH_ASCENDING_DESCENDING_ARRAY_H
#define ALGORITHM_ANALYSIS_BINARY_SEARCH_ASCENDING_DESCENDING_ARRAY_H
// 12.3.1 Variant Search a cyclically sorted array

#include <vector>
#include <stdexcept>

using std::vector;
using std::invalid_argument;

int diff(const vector<int>& A, size_t index) {
    if (index >= A.size()-1) {
         throw invalid_argument("diff is not defined in the last element of array.");
    }

    return A[index+1] - A[index];
}

int Search_AD_max(const vector<int>& A) {
    if (A.size() == 1) {
        return A[0];
    } else if (A.size() == 2) {
        return A[0] > A[1] ? A[0] : A[1];
    }

    size_t left = 0;
    size_t right = A.size()-1;
    size_t middle;

    while (left < right) {
        middle = left + (right - left)/2;

        if (diff(A, middle) > 0) {
            left = middle +1;
        } else {  // diff(A, middle) < 0
            right = middle;
        }
    }

    return A[right];
}

#endif //ALGORITHM_ANALYSIS_BINARY_SEARCH_ASCENDING_DESCENDING_ARRAY_H
