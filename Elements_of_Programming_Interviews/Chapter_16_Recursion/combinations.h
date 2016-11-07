#ifndef ALGORITHM_ANALYSIS_COMBINATIONS_H
#define ALGORITHM_ANALYSIS_COMBINATIONS_H
// 16.5 Generate all subsets of size k

#include <algorithm>
#include <vector>

using std::vector;

void DirectedCombinations(int n, int k, int offset, vector<int>* partial_combination, vector<vector<int>>* result);

// @include
vector<vector<int>> Combinations(int n, int k) {
    vector<vector<int>> result;
    DirectedCombinations(n, k, 1, new vector<int>, &result);
    return result;
}

void DirectedCombinations(int n, int k, int offset,
                          vector<int>* partial_combination,
                          vector<vector<int>>* result) {
    if (partial_combination->size() == k) {
        result->emplace_back(*partial_combination);
        return;
    }

    // Generate remaining combinations over {offset, ..., n - 1} of size
    // num_remaining.
    const int num_remaining = k - partial_combination->size();
    for (int i = offset; i <= n && num_remaining <= n - i + 1; ++i) {
        partial_combination->emplace_back(i);
        DirectedCombinations(n, k, i + 1, partial_combination, result);
        partial_combination->pop_back();
    }
}
// @exclude

#endif //ALGORITHM_ANALYSIS_COMBINATIONS_H
