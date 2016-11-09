#ifndef ALGORITHM_ANALYSIS_FIND_KTH_ELEMENT_IN_TWO_SORTED_ARRAYS_H
#define ALGORITHM_ANALYSIS_FIND_KTH_ELEMENT_IN_TWO_SORTED_ARRAYS_H
// 25.16 Search in two sorted arrays

#include <algorithm>
#include <limits>
#include <vector>

using std::max;
using std::min;
using std::numeric_limits;
using std::vector;

template <typename T>
T FindKthInTwoSortedArrays(
        const vector<T> &A, const vector<T> &B, int k) {
    // Not enough elements in A and B
    if (k > A.size() + B.size()) {
        return -1;  // no k-th element
    }

    int l_A = 0;
    int r_A = min(static_cast<int>(A.size() - 1), k - 1);
    int l_B = 0;
    int r_B = min(static_cast<int>(B.size() - 1), k - 1);

    while (true) {
        // Averagely get k - 1 elements from A and B
        int num_A = r_A - l_A + 1;
        int num_B = r_B - l_B + 1;

        // assign i and j elements to A and B respectively according to the ratio of elements
        int i = num_A * (k - 1) / (num_A + num_B);
        int j = (k - 1) - i;

        T A_i_1 = (l_A + i == 0 ? numeric_limits<int>::min() : A[l_A + i - 1]);
        T A_i = (l_A + i == A.size() ? numeric_limits<int>::max() : A[l_A + i]);

        T B_j_1 = (l_B + j == 0 ? numeric_limits<int>::min() : B[l_B + j - 1]);
        T B_j = (l_B + j == B.size() ? numeric_limits<int>::max() : B[l_B + j]);

        if (B_j_1 <= A_i && A_i <= B_j) {
            return A_i;  // A_i is the k-th element
        } else if (A_i_1 <= B_j && B_j <= A_i) {
            return B_j;  // B_j is the k-th element
        }

        if (A_i < B_j) {
            // Exclude the elements <= A_i and >= B_j
            l_A += i + 1;
            k -= (i + 1);
        } else {
            // Exclude the elements <= B_j and >= A_i
            l_B += j + 1;
            k -= (j + 1);
        }
    }
}

// @include
int FindKthInTwoSortedArrays(const vector<int>& A, const vector<int>& B,
                             const int k) {
    // Lower bound of elements we will choose in A.
    int low = max(0, static_cast<int>(k - B.size()));
    // Upper bound of elements we will choose in A.
    int high = min(static_cast<int>(A.size()), k);

    while (low < high) {
        int x = low + ((high - low) / 2);

        // A_x_1 = last element in bound. Total x elements in A
        int A_x_1 = (x <= 0 ? numeric_limits<int>::min() : A[x - 1]);
        // A_x = next element in out of bound
        int A_x = (x >= A.size() ? numeric_limits<int>::max() : A[x]);

        // B_k_x_1 = last element in bound. Total k - x elements in B
        int B_k_x_1 = (k - x <= 0 ? numeric_limits<int>::min() : B[k - x - 1]);
        // B_k_x = next element in out of bound
        int B_k_x = (k - x >= B.size() ? numeric_limits<int>::max() : B[k - x]);

        if (A_x < B_k_x_1) {  // A need to include more elements
            low = x + 1;
        } else if (A_x_1 > B_k_x) {  // B need to include more elements
            high = x - 1;
        } else {
            // B[k - x - 1] <= A[x] && A[x - 1] <= B[k - x].
            return max(A_x_1, B_k_x_1);
        }
    }

    int A_low_1 = low <= 0 ? numeric_limits<int>::min() : A[low - 1];
    int B_k_low_1 = k - low - 1 < 0 ? numeric_limits<int>::min() : B[k - low - 1];
    return max(A_low_1, B_k_low_1);
}
// @exclude

template <typename T>
T CheckAnswer(const vector<T>& A, const vector<T>& B, int k) {
    int i = 0, j = 0, count = 0;
    T ret;

    while ((i < A.size() || j < B.size()) && count < k) {
        if (i < A.size() && j < B.size()) {
            if (A[i] < B[j]) {
                ret = A[i];
                ++i;
            } else {
                ret = B[j];
                ++j;
            }
        } else if (i < A.size()) {
            ret = A[i];
            ++i;
        } else {
            ret = B[j];
            ++j;
        }
        ++count;
    }
    return ret;
}

#endif //ALGORITHM_ANALYSIS_FIND_KTH_ELEMENT_IN_TWO_SORTED_ARRAYS_H
