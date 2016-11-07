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

    for (int i = 0; i < individual_play_scores.size(); ++i) {
        num_combinations_for_score[i][0] = 1;  // One way to reach 0.

        // see the table in EPI p.276
        for (int j = 1; j <= final_score; ++j) {
            int without_this_play =
                    i >= 1 ? num_combinations_for_score[i - 1][j] : 0;
            int with_this_play =
                    j >= individual_play_scores[i]
                    ? num_combinations_for_score[i][j - individual_play_scores[i]]
                    : 0;
            num_combinations_for_score[i][j] = without_this_play + with_this_play;
        }
    }
    return num_combinations_for_score.back().back();
}
// @exclude

#endif //ALGORITHM_ANALYSIS_SCORE_COMBINATION_H
