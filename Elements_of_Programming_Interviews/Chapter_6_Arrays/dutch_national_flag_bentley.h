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
// See TAOCP III p. 635
    void DutchFlagPartition(int pivot_index, vector<Color> *A_ptr) {
        vector<Color> &A = *A_ptr;
        Color pivot = A[pivot_index];

        int a, b, c, d, l, h, s;

        a = b = 0;
        c = d = A.size() - 1;
        for (; ;) {
            while (b <= c && A[b] <= pivot) {
                if (A[b] == pivot)
                    swap(A[a++], A[b]);
                b++;
            }
            while (c >= b && A[c] >= pivot) {
                if (A[c] == pivot)
                    swap(A[d--], A[c]);
                c--;
            }
            if (b > c)
                break;
            // x[b] > pivot and x[c] < pipot
            swap(A[b++], A[c--]);
        }

        s = min(a, b - a);
        for (l = 0, h = b - s; s; s--)
            swap(A[l++], A[h++]);

        s = min(d - c, static_cast<int>(A.size()) - 1 - d);
        for (l = b, h = A.size() - s; s; s--)
            swap(A[l++], A[h++]);
    }
}

#endif //ALGORITHM_ANALYSIS_DUTCH_NATIONAL_FLAG_BENTLEY_H
