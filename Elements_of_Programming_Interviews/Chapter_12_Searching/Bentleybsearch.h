#ifndef ALGORITHM_ANALYSIS_BENTLEYBSEARCH_H
#define ALGORITHM_ANALYSIS_BENTLEYBSEARCH_H

#include <vector>

using std::vector;

// @include
int bsearch(int t, const vector<int>& A) {
    int L = 0, U = A.size() - 1;
    while (L <= U) {
        // int M = (L + U) / 2;
        int M = L + (U - L) / 2;
        if (A[M] < t) {
            L = M + 1;
        } else if (A[M] == t) {
            return M;
        } else {
            U = M - 1;
        }
    }
    return -1;
}
// @exclude


#endif //ALGORITHM_ANALYSIS_BENTLEYBSEARCH_H
