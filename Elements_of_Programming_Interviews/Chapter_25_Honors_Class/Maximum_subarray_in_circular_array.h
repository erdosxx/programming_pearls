#ifndef ALGORITHM_ANALYSIS_MAXIMUM_SUBARRAY_IN_CIRCULAR_ARRAY_H
#define ALGORITHM_ANALYSIS_MAXIMUM_SUBARRAY_IN_CIRCULAR_ARRAY_H
// 25.31 Compute the maximum subarray sum in a circular array

#include <algorithm>
#include <vector>

using std::max;
using std::vector;

// Calculates the non-circular solution.
int FindMaxSubarray(const vector<int>& A) {
    int maximum_till = 0;
    int maximum = 0;

    for (int a : A) {
        maximum_till = max(a, a + maximum_till);
        maximum = max(maximum, maximum_till);
    }
    return maximum;
}

int FindCircularMaxSubarray(const vector<int>& A);

// @include
int MaxSubarraySumInCircular(const vector<int>& A) {
    return max(FindMaxSubarray(A), FindCircularMaxSubarray(A));
}

// Calculates the solution which is circular.
int FindCircularMaxSubarray(const vector<int>& A) {
    // Maximum subarray sum starts at index 0 and ends at or before index i.
    vector<int> maximum_begin;
    int sum = A.front();
    maximum_begin.emplace_back(sum);

    for (int i = 1; i < A.size(); ++i) {
        sum += A[i];
        maximum_begin.emplace_back(max(maximum_begin.back(), sum));
    }

    // Maximum subarray sum starts at index i + 1 and ends at the last element.
    vector<int> maximum_end(A.size());
    maximum_end.back() = 0;
    sum = 0;

    for (int i = A.size() - 2; i >= 0; --i) {
        sum += A[i + 1];
        maximum_end[i] = max(maximum_end[i + 1], sum);
    }

    // Calculates the maximum subarray which is circular.
    int circular_max = 0;
    for (int i = 0; i < A.size(); ++i) {
        circular_max = max(circular_max, maximum_begin[i] + maximum_end[i]);
    }

    return circular_max;
}
// @exclude
#endif //ALGORITHM_ANALYSIS_MAXIMUM_SUBARRAY_IN_CIRCULAR_ARRAY_H
