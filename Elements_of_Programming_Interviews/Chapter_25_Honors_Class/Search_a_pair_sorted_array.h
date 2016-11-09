#ifndef ALGORITHM_ANALYSIS_SEARCH_A_PAIR_SORTED_ARRAY_H
#define ALGORITHM_ANALYSIS_SEARCH_A_PAIR_SORTED_ARRAY_H
// 25.36 Search for a pair-sum in an abs-sorted array

#include <algorithm>
#include <functional>
#include <utility>
#include <vector>

using std::greater_equal;
using std::less;
using std::pair;
using std::vector;

struct IndexPair {
    int index_1, index_2;
};

template <typename Compare>
IndexPair FindPairUsingCompare(const vector<int>&, int, Compare);
IndexPair FindPositiveNegativePair(const vector<int>&, int);

// @include

IndexPair FindPairSumK(const vector<int>& A, int k) {
    // case 1: postive + negative
    IndexPair result = FindPositiveNegativePair(A, k);

    if (result.index_1 == -1 && result.index_2 == -1) {
        // case 2: positive + positive
        return k >= 0 ? FindPairUsingCompare(A, k, less<int>())  // first_arg < second_arg
               // case 3: negative + negative
                      : FindPairUsingCompare(A, k, greater_equal<int>());  // first_arg >= second_arg
    }

    return result;
}

template <typename Compare>
IndexPair FindPairUsingCompare(const vector<int>& A, int k, Compare comp) {
    IndexPair result = IndexPair{0, static_cast<int>(A.size() - 1)};

    while (result.index_1 < result.index_2 && comp(A[result.index_1], 0)) {
        ++result.index_1;
    }

    while (result.index_1 < result.index_2 && comp(A[result.index_2], 0)) {
        --result.index_2;
    }

    while (result.index_1 < result.index_2) {
        if (A[result.index_1] + A[result.index_2] == k) {
            return result;
        } else if (comp(A[result.index_1] + A[result.index_2], k)) {
            do {
                ++result.index_1;
            } while (result.index_1 < result.index_2 && comp(A[result.index_1], 0));
        } else {
            do {
                --result.index_2;
            } while (result.index_1 < result.index_2 && comp(A[result.index_2], 0));
        }
    }
    return {-1, -1};  // No answer.
}

IndexPair FindPositiveNegativePair(const vector<int>& A, int k) {
    // result.index_1 for positive, and result.index_2 for negative.
    IndexPair result = IndexPair{static_cast<int>(A.size() - 1),
                                 static_cast<int>(A.size() - 1)};
    // Find the last positive or zero.
    while (result.index_1 >= 0 && A[result.index_1] < 0) {
        --result.index_1;
    }

    // Find the last negative.
    while (result.index_2 >= 0 && A[result.index_2] >= 0) {
        --result.index_2;
    }

    while (result.index_1 >= 0 && result.index_2 >= 0) {
        if (A[result.index_1] + A[result.index_2] == k) {
            return result;
        } else if (A[result.index_1] + A[result.index_2] > k) {
            do {
                --result.index_1;
            } while (result.index_1 >= 0 && A[result.index_1] < 0);
        } else {  // A[result.index_1] + A[result.index_2] < k.
            do {
                --result.index_2;
            } while (result.index_2 >= 0 && A[result.index_2] >= 0);
        }
    }
    return {-1, -1};  // No answer.
}
// @exclude

#endif //ALGORITHM_ANALYSIS_SEARCH_A_PAIR_SORTED_ARRAY_H
