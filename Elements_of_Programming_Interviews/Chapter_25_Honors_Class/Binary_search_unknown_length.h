#ifndef ALGORITHM_ANALYSIS_BINARY_SEARCH_UNKNOWN_LENGTH_H
#define ALGORITHM_ANALYSIS_BINARY_SEARCH_UNKNOWN_LENGTH_H

#include <algorithm>
#include <vector>

using std::exception;
using std::max;
using std::vector;

// @include
int BinarySearchUnknownLength(const vector<int>& A, int k) {
    // Find the possible range where k exists.
    int p = 0;

    while (true) {
        try {
            int idx = (1 << p) - 1;  // 2^p - 1.
            if (A.at(idx) == k) {
                return idx;
            } else if (A.at(idx) > k) {
                break;
            }
        } catch (const exception& e) {
            break;
        }
        ++p;
    }

    // Binary search between indices 2^(p - 1) and 2^p - 2, inclusive.
    int left = max(0, 1 << (p - 1));
    int right = (1 << p) - 2;

    while (left <= right) {
        int mid = left + ((right - left) / 2);
        try {
            if (A.at(mid) == k) {
                return mid;
            } else if (A.at(mid) > k) {
                right = mid - 1;
            } else {  // A.at(mid) < k
                left = mid + 1;
            }
        } catch (const exception& e) {
            right = mid - 1;  // Search the left part if out-of-bound.
        }
    }
    return -1;  // Nothing matched k.
}
// @exclude

#endif //ALGORITHM_ANALYSIS_BINARY_SEARCH_UNKNOWN_LENGTH_H
