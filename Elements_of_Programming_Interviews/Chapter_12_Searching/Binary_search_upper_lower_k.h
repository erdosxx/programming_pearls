#ifndef ALGORITHM_ANALYSIS_BINARY_SEARCH_UPPER_LOWER_K_H
#define ALGORITHM_ANALYSIS_BINARY_SEARCH_UPPER_LOWER_K_H
// 12.1.3 Variant Search a sorted array for first occurrence of k

#include "Binary_search_first_k.h"
#include <vector>

using std::vector;

struct low_high {
    int low = -1;
    int high = -1;
};

int SearchLastOfK(const vector<int>& A, int left, int right, const int& k);
int SearchLastOfK(const vector<int>& A, const int& k);

low_high lower_upper(const vector<int>& A, int left, int right, const int& k) {
    low_high result = {-1, -1};

    if ( left > right) {
        return result;
    }

    while (left <= right) {
        int middle = left + (right - left)/2;

        if (A[middle] < k) {
            left = middle +1;
        } else if (A[middle] > k) {
            right = middle -1;
        } else { // A[middle] = k
            result.low = SearchFirstOfK(A, left, middle, k);
            result.high = SearchLastOfK(A, middle, right, k);
            return result;
        }
    }

    return result;
}

low_high lower_upper(const vector<int>& A, const int& k) {
    return lower_upper(A, 0, A.size()-1, k);
}

// For Variant 12.1.3
int SearchLastOfK(const vector<int>& A, int left, int right, const int& k) {
    int result = -1;

    if (left > right) {
        return result;
    }

    // [left : right] is the candidate set.
    while (left <= right) {
        int mid = left + ((right - left) / 2);

        if (A[mid] > k) {
            right = mid - 1;
        } else if (A[mid] == k) {
            result = mid;
            // Nothing to the right of mid can be the first occurrence of k.
            left = mid + 1;
        } else {  // A[mid] < k.
            left = mid + 1;
        }
    }

    return result;
}

int SearchLastOfK(const vector<int>& A, const int& k) {
    return SearchLastOfK(A, 0, A.size()-1, k);
}
#endif //ALGORITHM_ANALYSIS_BINARY_SEARCH_UPPER_LOWER_K_H
