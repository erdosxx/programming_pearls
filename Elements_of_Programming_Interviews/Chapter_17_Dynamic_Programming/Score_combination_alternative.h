#ifndef ALGORITHM_ANALYSIS_SCORE_COMBINATION_ALTERNATIVE_H
#define ALGORITHM_ANALYSIS_SCORE_COMBINATION_ALTERNATIVE_H
// 17.1 Count the number of score combinations

#include <vector>

using std::vector;

// @include
int CountCombinationsAlt(int total_score, const vector<int>& score_ways) {
    vector<int> combinations(total_score + 1, 0);
    combinations[0] = 1;  // One way to reach 0.

    for (int score : score_ways) {
        vector<int> new_combinations(total_score + 1, 0);
        new_combinations = combinations;

        for (int column_score = 1; column_score <= total_score; ++column_score) {
            for (int num_of_used_score = 1; num_of_used_score <= column_score / score; ++num_of_used_score) {
                new_combinations[column_score] += combinations[column_score - num_of_used_score * score];
            }
        }
        combinations = new_combinations;
    }

    return combinations[total_score];
}
// @exclude


#endif //ALGORITHM_ANALYSIS_SCORE_COMBINATION_ALTERNATIVE_H
