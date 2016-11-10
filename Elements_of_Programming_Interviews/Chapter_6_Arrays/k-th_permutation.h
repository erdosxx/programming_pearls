#ifndef ALGORITHM_ANALYSIS_K_TH_PERMUTATION_H
#define ALGORITHM_ANALYSIS_K_TH_PERMUTATION_H
// 6.10 Variant Compute the next permutation

#include <cmath>
#include <vector>

using namespace std;

enum {used = -1};

// @include
int n_factor(int n) {
    int result = 1;
    while (n) {
        result *= n--;
    }
    return result;
}

// Algorithm: using counting for each case, we can get the kth elements
// Ex) 35th from 01234
// 0.... : 4! = 24
// 1.... : 4! = 24
// we know that 35th must be 1....
// In 35 - 24 = 11
// 10... : 3! = 6
// 12... : 3! = 6
// we know that 35th must be 12...
// In 11 - 6 = 5
// 120.. : 2! = 2
// 123.. : 2! = 2
// 124.. : 2! = 2
// we know that 35h must be 124..
// In 5 - 4 = 1
// 12403 is 35th
vector<int> generate_kth_permutation(int n, int k) {
    --k;  // adjust k to start from 0
    vector<int> A;
    for (int i = 0; i < n; ++i) {
        A.push_back(i);
    }

    vector<int> result;

    for (int i = 0; i < n; ++i) {
        int count = n_factor(n - i - 1);
        int index = k / count;
        k %= count;

        int c_idx = 0;

        for (int j = 0; j < n; ++j) {
            if (A[j] != used) {
                if (c_idx == index) {
                    result.push_back(A[j]);
                    A[j] = used;
                    break;
                }
                ++c_idx;
            }
        }
    }
    return result;
}
// @exclude


#endif //ALGORITHM_ANALYSIS_K_TH_PERMUTATION_H
