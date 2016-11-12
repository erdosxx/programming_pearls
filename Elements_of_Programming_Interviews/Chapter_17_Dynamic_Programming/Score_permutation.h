#ifndef ALGORITHM_ANALYSIS_SCORE_PERMUTATION_H
#define ALGORITHM_ANALYSIS_SCORE_PERMUTATION_H
// 17.1.2, 17.1.5, 17.10 Variant Count the number of score combinations

#include <vector>

using std::vector;

// @include
int CountPermutations(int final_score, const vector<int>& score_ways) {
    vector<int> permutations(final_score + 1, 0);
    permutations[0] = 1;  // One way to reach 0.

    for (int column_score = 1; column_score <= final_score; ++column_score) {
        for (int score : score_ways) {
            if (column_score >= score) {
                permutations[column_score] += permutations[column_score - score];
            }
        }
    }
    return permutations[final_score];
}
// @exclude


#endif //ALGORITHM_ANALYSIS_SCORE_PERMUTATION_H
