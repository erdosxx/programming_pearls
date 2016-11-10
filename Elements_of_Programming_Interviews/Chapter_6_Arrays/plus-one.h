#ifndef ALGORITHM_ANALYSIS_PLUS_ONE_H
#define ALGORITHM_ANALYSIS_PLUS_ONE_H
// 6.2 Increment an arbitrary-precision integer

#include <algorithm>
#include <vector>

using std::vector;

// @include
namespace plusone {
    vector<int> PlusOne(vector<int> A) {
        ++A.back();
        for (int i = A.size() - 1; i > 0 && A[i] == 10; --i) {
            A[i] = 0, ++A[i - 1];
        }
        if (A[0] == 10) {
            // Need additional digit as the most significant digit (i.e., A[0]) has a
            // carry-out.
            A[0] = 0;
            A.insert(A.begin(), 1);
        }
        return A;
    }
}
#endif //ALGORITHM_ANALYSIS_PLUS_ONE_H
