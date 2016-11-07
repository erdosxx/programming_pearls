#ifndef ALGORITHM_ANALYSIS_MAX_SUM_SUBARRAY_H
#define ALGORITHM_ANALYSIS_MAX_SUM_SUBARRAY_H
// 17. Dynamic Programming boot camp

#include <utility>
#include <vector>

using std::default_random_engine;
using std::random_device;
using std::uniform_int_distribution;
using std::vector;

// @include
int FindMaximumSubarray(const vector<int>& A) {
    int min_sum = 0;
    int sum = 0;
    int max_sum = 0;

    for (int i = 0; i < A.size(); ++i) {
        sum += A[i];
        if (sum < min_sum) {
            min_sum = sum;
        }

        if (sum - min_sum > max_sum) {
            max_sum = sum - min_sum;
        }
    }
    return max_sum;
}
// @exclude

int FindMaximumSubarray2(const vector<int>& A) {
    int maxsum_ending_at_i = 0;
    int maxsum = 0;

    for (int i=0; i < A.size(); ++i) {
        if (maxsum_ending_at_i >= 0) {
            maxsum_ending_at_i += A[i];
        } else { // maxsum_ending < 0
            maxsum_ending_at_i = A[i];
        }

        if (maxsum_ending_at_i > maxsum) {
            maxsum = maxsum_ending_at_i;
        }
    }

    return maxsum;
}

template <typename T>
vector<T> RandVector(int len) {
    vector<T> ret;
    default_random_engine gen((random_device())());

    while (len--) {
        uniform_int_distribution<int> dis(-1000, 1000);
        ret.push_back(dis(gen));
    }

    return ret;
}

#endif //ALGORITHM_ANALYSIS_MAX_SUM_SUBARRAY_H
