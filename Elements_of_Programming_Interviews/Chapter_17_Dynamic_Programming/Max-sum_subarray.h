#ifndef ALGORITHM_ANALYSIS_MAX_SUM_SUBARRAY_H
#define ALGORITHM_ANALYSIS_MAX_SUM_SUBARRAY_H
// 17. Dynamic Programming boot camp

#include <utility>
#include <vector>
#include <algorithm>

using std::default_random_engine;
using std::random_device;
using std::uniform_int_distribution;
using std::vector;
using std::min;
using std::max;

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

// See 25.31 page 440
int FindMaximumSubarray2_1(const vector<int>& A) {
    int maxsum_ending_at_i = 0;
    int maxsum = 0;

    for (int i=0; i < A.size(); ++i) {
        maxsum_ending_at_i = max(A[i], maxsum_ending_at_i+A[i]);

        maxsum = max(maxsum, maxsum_ending_at_i);
    }

    return maxsum;
}

// For problem 25.31
int FindMinimumSubarray2(const vector<int>& A) {
    int minsum_ending_at_i = 0;
    int minsum = 0;

    for (int i=0; i < A.size(); ++i) {
        minsum_ending_at_i = min(A[i], minsum_ending_at_i+A[i]);

        minsum = min(minsum, minsum_ending_at_i);
    }

    return minsum;
}

int FindMaximumSubarrayHelper3(const vector<int>& A, const int& left, const int& right) {
    if (left > right) {
        return 0;
    }

    if (left == right) {
        return A[left] >= 0 ? A[left] : 0;
    }

    const int middle = left + (right - left)/2;
    // left maxsum ending at middle
    int left_maxsum =  0;
    int sum = 0;
    for (int i = middle; i >= left ; --i) {
        sum += A[i];
        left_maxsum = (sum > left_maxsum) ? sum : left_maxsum;
    }

    // left maxsum ending at middle
    int right_maxsum =  0;
    sum = 0;
    for (int i = middle+1; i <= right ; ++i) {
        sum += A[i];
        right_maxsum = (sum > right_maxsum) ? sum : right_maxsum;
    }

    int middle_sum = left_maxsum + right_maxsum;
    int left_sum = FindMaximumSubarrayHelper3(A, left, middle);
    int right_sum = FindMaximumSubarrayHelper3(A, middle+1, right);

    // max(middle_sum, left_sum, right_sum)
    return middle_sum > left_sum ?
            middle_sum > right_sum ? middle_sum : right_sum
           : left_sum > right_sum ? left_sum : right_sum;
}

// divide and conquer version.
// T(n) = 2T(n/2) +O(n),  T(n) = O(nlogn)
int FindMaximumSubarray3(const vector<int>& A) {
    return FindMaximumSubarrayHelper3(A, 0,A.size()-1);
}

int maxmac(const int &a, const int &b) {
    return a > b ? a : b;
}

int maxmac(const int& a, const int& b, const int& c) {
    return a > b ?
           a > c ? a : c
         : b > c ? b : c;
}

struct maxsum {
    int max_left;
    int max_right;
    int total;
    int maxsum;
};

maxsum FindMaximumSubarrayHelper4(const vector<int>& A, const int& left, const int& right) {
    if (left > right) {
        return maxsum{0,0,0,0};
    }

    if (left == right) {
        return A[left] >= 0 ? maxsum{A[left], A[left], A[left], A[left]} : maxsum{0, 0, A[left], 0};
    }

    int middle = left + (right - left)/2;
    maxsum left_result = FindMaximumSubarrayHelper4(A, left, middle);
    maxsum right_result = FindMaximumSubarrayHelper4(A, middle+1, right);

    int max_middle = left_result.max_right + right_result.max_left;

    // max(left_result.max_left, left_result.total + right_result.max_left)
    int max_left = maxmac(left_result.max_left, left_result.total + right_result.max_left);

    // max(right_result.max_right, right_result.max_all + left_result.max_right)
    int max_right = maxmac(right_result.max_right, right_result.total + left_result.max_right);

    int max_total = left_result.total + right_result.total;

    // max(max_middle, left_result.maxsum, right_result.maxsum)
    int max_val = maxmac(max_middle, left_result.maxsum, right_result.maxsum);

    return maxsum{max_left, max_right, max_total, max_val};
}

// divide and conquer version.
// T(n) = 2T(n/2) +O(1),  T(n) = O(n)
int FindMaximumSubarray4(const vector<int>& A) {
    return FindMaximumSubarrayHelper4(A, 0, A.size()-1).maxsum;
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
