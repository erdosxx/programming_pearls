#ifndef ALGORITHM_ANALYSIS_SCORE_PERMUTATION_TWO_TEAM_H
#define ALGORITHM_ANALYSIS_SCORE_PERMUTATION_TWO_TEAM_H
// 17.1.3 Variant Count the number of score combinations

#include <vector>

using std::vector;

struct two_scores {
    int scoreA;
    int scoreB;
};

// @include
int CountPermutations_two_teams(const two_scores& final_score, const vector<int>& score_ways) {
    vector<vector<int>> permutations(final_score.scoreA +1, vector<int>(final_score.scoreB +1, 0));

    permutations[0][0] = 1;  // One way to reach 0.

    for (int column_A_score = 0; column_A_score <= final_score.scoreA; ++column_A_score) {
        for (int column_B_score = 0; column_B_score <= final_score.scoreB; ++column_B_score) {
           for (int score : score_ways) {
               if (column_A_score >= score) {
                   permutations[column_A_score][column_B_score] += permutations[column_A_score - score][column_B_score];
               }
               if (column_B_score >= score) {
                   permutations[column_A_score][column_B_score] += permutations[column_A_score][column_B_score - score];
               }
           }
        }
    }

    return permutations[final_score.scoreA][final_score.scoreB];
}
// @exclude





#endif //ALGORITHM_ANALYSIS_SCORE_PERMUTATION_TWO_TEAM_H
