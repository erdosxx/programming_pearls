#ifndef ALGORITHM_ANALYSIS_BINARY_SEARCH_CIRCULAR_ARRAY_WITH_DUPLICATES_H
#define ALGORITHM_ANALYSIS_BINARY_SEARCH_CIRCULAR_ARRAY_WITH_DUPLICATES_H
// 12.3 Search a cyclically sorted array

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::random_device;
using std::stoi;
using std::uniform_int_distribution;
using std::vector;

namespace duplicate {
    int SearchSmallestHelper(const vector<int> &, int, int);

// @include
    int SearchSmallest(const vector<int> &A) {
        return SearchSmallestHelper(A, 0, A.size() - 1);
    }

    int SearchSmallestHelper(const vector<int> &A, int left, int right) {
        if (left == right) {
            return left;
        }

        int mid = left + ((right - left) / 2);
        if (A[mid] > A[right]) {
            return SearchSmallestHelper(A, mid + 1, right);
        } else if (A[mid] < A[right]) {
            return SearchSmallestHelper(A, left, mid);
        } else {  // A[mid] == A[right].
            // We cannot eliminate either side so we compare the results from both
            // sides.
            int left_result = SearchSmallestHelper(A, left, mid);
            int right_result = SearchSmallestHelper(A, mid + 1, right);
            return A[right_result] < A[left_result] ? right_result : left_result;
        }
    }
// @exclude
}

#endif //ALGORITHM_ANALYSIS_BINARY_SEARCH_CIRCULAR_ARRAY_WITH_DUPLICATES_H
