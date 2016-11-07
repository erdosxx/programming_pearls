#ifndef ALGORITHM_ANALYSIS_PERMUTATIONS_H
#define ALGORITHM_ANALYSIS_PERMUTATIONS_H
// 16.3 Generate permutations

#include <algorithm>
#include <string>
#include <vector>

using std::vector;

// @include
vector<vector<int>> Permutations(vector<int> A) {
    vector<vector<int>> result;
    // Generate the first permutation in dictionary order.
    sort(A.begin(), A.end());
    do {
        result.emplace_back(A);
    } while (next_permutation(A.begin(), A.end()));
    return result;
}
// @exclude


#endif //ALGORITHM_ANALYSIS_PERMUTATIONS_H
