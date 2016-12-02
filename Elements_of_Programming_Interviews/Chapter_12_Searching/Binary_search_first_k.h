#ifndef ALGORITHM_ANALYSIS_BINARY_SEARCH_FIRST_K_H
#define ALGORITHM_ANALYSIS_BINARY_SEARCH_FIRST_K_H
// 12.1 Search a sorted array for first occurrence of k

#include <algorithm>
#include <iterator>
#include <vector>

using std::vector;

/*
int SearchFirstOfK(const vector<int>& A, int k) {
    int left = 0;
    int right = A.size() - 1;
    int result = -1;

    // [left : right] is the candidate set.
    while (left <= right) {
        int mid = left + ((right - left) / 2);
        if (A[mid] > k) {
            right = mid - 1;
        } else if (A[mid] == k) {
            result = mid;
            // Nothing to the right of mid can be the first occurrence of k.
            right = mid - 1;
        } else {  // A[mid] < k.
            left = mid + 1;
        }
    }
    return result;
}
 */

int SearchFirstOfK(const vector<int>& A, int left, int right, const int& k) {
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
            right = mid - 1;
        } else {  // A[mid] < k.
            left = mid + 1;
        }
    }
    return result;
}

int SearchFirstOfK(const vector<int>& A, const int& k) {
    return SearchFirstOfK(A, 0, A.size()-1, k);
}

/* Programming Pearls */
/* Alg 3: From PP, Col 9, Page 93 */
// Find the FIRST occurrence of the integer t
int binary_search_first(const vector<int>& x, const int& value) {
    int middle;
    int low = -1;
    int high = x.size();

    // invariant: x[low] < timestamp && x[high] >= timestamp && low < high
    //while (low + 1 != high) {
    while (high - low > 1) {
        middle = low + (high - low)/2;

        if (x[middle] < value)
            low = middle;
        else
            high = middle;
    }

    if (high == x.size() || x[high] != value)
        return -1;
    return high;
}

int SearchFirstOfKAlternative(const vector<int>& A, const int& k) {
    auto result = lower_bound(A.begin(), A.end(), k);
    if (*result == k) {
        return distance(A.begin(), result);
    }
    return -1;
}

#endif //ALGORITHM_ANALYSIS_BINARY_SEARCH_FIRST_K_H
