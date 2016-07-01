#ifndef ALGORITHM_ANALYSIS_BINARY_SEARCH_FIRST_K_H
#define ALGORITHM_ANALYSIS_BINARY_SEARCH_FIRST_K_H

#include <algorithm>
#include <iterator>
#include <vector>

using std::vector;

// @include
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
// @exclude

/* Programming Pearls */
/* Alg 3: From PP, Col 9, Page 93 */
// Find the FIRST occurrence of the integer t
int binary_search_first(const vector<int>& x, int value) {
    int middle;
    int low = -1;
    int high = x.size();

    // invariant: x[low] < value && x[high] >= value && low < high
    while (low + 1 != high) {
        middle = (low + high) / 2;

        if (x[middle] < value)
            low = middle;
        else
            high = middle;
    }

    if (high >= x.size() || x[high] != value)
        return -1;
    return high;
}

int SearchFirstOfKAlternative(const vector<int>& A, int k) {
    auto result = lower_bound(A.begin(), A.end(), k);
    if (*result == k) {
        return distance(A.begin(), result);
    }
    return -1;
}

#endif //ALGORITHM_ANALYSIS_BINARY_SEARCH_FIRST_K_H
