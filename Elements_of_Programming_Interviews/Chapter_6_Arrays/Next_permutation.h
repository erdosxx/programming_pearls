#ifndef ALGORITHM_ANALYSIS_NEXT_PERMUTATION_H
#define ALGORITHM_ANALYSIS_NEXT_PERMUTATION_H
// 6.10 Compute the next permutation

#include <algorithm>
#include <vector>

using std::swap;
using std::vector;

// See TAOCP IV p.319 Algorithm L
// @include
vector<int> NextPermutation(vector<int> perm) {
    int k = perm.size() - 2;

    while (k >= 0 && perm[k] >= perm[k + 1]) {
        --k;
    }

    if (k == -1) {
        return {};  // perm is the last permutation.
    }

    // Swap the smallest entry after index k that is greater than perm[k]. We
    // exploit the fact that perm[k + 1 : perm.size() - 1] is decreasing so if
    // we
    // search in reverse order, the first entry that is greater than perm[k] is
    // the smallest such entry.
    for (int i = perm.size() - 1; i > k; --i) {
        if (perm[i] > perm[k]) {
            swap(perm[k], perm[i]);
            break;
        }
    }

    // Since perm[k + 1 : perm.size() - 1] is in decreasing order, we can build
    // the smallest dictionary ordering of this subarray by reversing it.
    reverse(perm.begin() + k + 1, perm.end());
    return perm;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_NEXT_PERMUTATION_H
