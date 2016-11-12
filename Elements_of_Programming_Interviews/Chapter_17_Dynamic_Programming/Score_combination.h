#ifndef ALGORITHM_ANALYSIS_SCORE_COMBINATION_H
#define ALGORITHM_ANALYSIS_SCORE_COMBINATION_H
// 17.1 Count the number of score combinations

#include <vector>

using std::vector;

// @include
int NumCombinationsForFinalScore(int final_score,
                                 const vector<int>& individual_play_scores) {
    vector<vector<int>> num_combinations_for_score(
            individual_play_scores.size(), vector<int>(final_score + 1, 0));

    for (int row = 0; row < individual_play_scores.size(); ++row) {
        num_combinations_for_score[row][0] = 1;  // One way to reach 0.

        // see the table in EPI p.276
        for (int score_column = 1; score_column <= final_score; ++score_column) {
            int without_this_play =
                    row >= 1 ? num_combinations_for_score[row - 1][score_column] : 0;
            int with_this_play =
                    score_column >= individual_play_scores[row]
                    ? num_combinations_for_score[row][score_column - individual_play_scores[row]]
                    : 0;
            num_combinations_for_score[row][score_column] = without_this_play + with_this_play;
        }
    }
    return num_combinations_for_score.back().back();
}
// @exclude

#endif //ALGORITHM_ANALYSIS_SCORE_COMBINATION_H
