#ifndef ALGORITHM_ANALYSIS_DUTCH_NATIONAL_FLAG_BENTLEY_H
#define ALGORITHM_ANALYSIS_DUTCH_NATIONAL_FLAG_BENTLEY_H
// 6.1 The Dutch national flag problem

#include <algorithm>
#include <vector>
#include "Dutch_national_flag.h"

using std::swap;
using std::vector;
using DutchFlag::Color;
using std::min;

// @include
namespace DutchFlag_bentley {
// See TAOCP III p. 137 #41.
// Weiss C++ page 362 #7.28
    void DutchFlagPartition(int pivot_index, vector<Color> *A_ptr) {
        vector<Color> &A = *A_ptr;
        Color pivot = A[pivot_index];

        //  |   =   |    <    |   unknown   |    >   |   =   |
        //           |next_to_equal_front
        //                     |next_to_smaller
        //                                 |next_to_larger
        //                                          |next_to_equal_back

        int next_to_equal_front = 0; int next_to_smaller = 0;
        int next_to_larger = A.size() - 1; int next_to_equal_back = A.size() - 1;

        for (; ;) {
            while (next_to_smaller <= next_to_larger && A[next_to_smaller] <= pivot) {
                if (A[next_to_smaller] == pivot)
                    swap(A[next_to_equal_front++], A[next_to_smaller]);
                next_to_smaller++;
            }

            while (next_to_larger >= next_to_smaller && A[next_to_larger] >= pivot) {
                if (A[next_to_larger] == pivot)
                    swap(A[next_to_equal_back--], A[next_to_larger]);
                next_to_larger--;
            }

            if (next_to_smaller > next_to_larger)
                break;
            // x[b] > pivot and x[c] < pipot
            swap(A[next_to_smaller++], A[next_to_larger--]);
        }

        int low, high;
        int num_of_exchange = min(next_to_equal_front, next_to_smaller - next_to_equal_front);
        //for (l = 0, h = b - s; s; s--)
        //    swap(A[l++], A[h++]);
        // following code is more simple than above
        for (low = 0, high = next_to_smaller -1; num_of_exchange; num_of_exchange--)
            swap(A[low++], A[high--]);

        num_of_exchange = min(next_to_equal_back - next_to_larger, static_cast<int>(A.size()) - 1 - next_to_equal_back);
        //for (l = b, h = A.size() - s; s; s--)
        //    swap(A[l++], A[h++]);
        // following code is more simple than above
        for (low = next_to_larger+1, high = A.size() - 1; num_of_exchange; num_of_exchange--)
            swap(A[low++], A[high--]);
    }
}

#endif //ALGORITHM_ANALYSIS_DUTCH_NATIONAL_FLAG_BENTLEY_H
