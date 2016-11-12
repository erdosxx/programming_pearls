#ifndef ALGORITHM_ANALYSIS_DUTCH_NATIONAL_FLAG_H
#define ALGORITHM_ANALYSIS_DUTCH_NATIONAL_FLAG_H
// 6.1 The Dutch national flag problem

#include <algorithm>
#include <vector>

using std::swap;
using std::vector;

// @include
namespace DutchFlag {
//typedef enum { RED, WHITE, BLUE } Color;
    using Color = enum {
        RED, WHITE, BLUE
    };

    void DutchFlagPartition(const int& pivot_index, vector<Color>* A_ptr) {
        vector<Color> &A = *A_ptr;
        // alias A does not necessary. Instead of A[i], we can use A_ptr->at(i)
        // But more simplicity, we use alias.
        Color pivot = A[pivot_index];
        /**
         * Keep the following invariants during partitioning:
         * bottom group: A[0 : smaller - 1].
         * middle group: A[smaller : equal - 1].
         * unclassified group: A[equal : larger - 1].
         * top group: A[larger : A.size() - 1].
         */
        //  |    <    |    =            |    unknown        |     >     |
        //             |next_to_small    | next_to_equal     | right_most_greater
        //
        int next_to_small = 0, next_to_equal = 0, right_most_greater = A.size();
        // Keep iterating as long as there is an unclassified element.
        while (next_to_equal < right_most_greater) {
            // A[equal] is the incoming unclassified element.
            if (A[next_to_equal] < pivot) {
                swap(A[next_to_small++], A[next_to_equal++]);
            } else if (A[next_to_equal] == pivot) {
                ++next_to_equal;
            } else {  // A[equal] > pivot.
                swap(A[next_to_equal], A[--right_most_greater]);
            }
        }
    }
}
#endif //ALGORITHM_ANALYSIS_DUTCH_NATIONAL_FLAG_H
