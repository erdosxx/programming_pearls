#ifndef ALGORITHM_ANALYSIS_LEAD_CHANGES_H
#define ALGORITHM_ANALYSIS_LEAD_CHANGES_H
// 17.1.4 Variant Count the number of score combinations

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::max;

enum Lead {A_Lead = 1, TIE=0, B_Lead= -1};
enum {UNREAL= -1};

namespace lead {
    struct two_scores {
        int scoreA;
        int scoreB;
    };

    Lead get_lead(const int& score_A, const int& score_B) {
        if (score_A > score_B) {
            return A_Lead;
        } else if (score_A < score_B) {
            return B_Lead;
        } else { // score_A == score_B
            return TIE;
        }
    }

    int make_next_lead_real (const int& max_lead) {
        return (max_lead == UNREAL) ? 0 : max_lead;
    }

    // This is my code and seems correct.
    int max_lead_changes(const two_scores &final_score, const vector<int> &score_ways) {
        vector<vector<int>> max_lead(final_score.scoreA + 1, vector<int>(final_score.scoreB + 1, UNREAL));

        max_lead[0][0] = 0;  // One way to reach 0.

        Lead curr_lead, next_lead;
        int curr_max_lead, next_max_lead;
        for (int column_A_score = 0; column_A_score <= final_score.scoreA; ++column_A_score) {
            for (int column_B_score = 0; column_B_score <= final_score.scoreB; ++column_B_score) {
                if (max_lead[column_A_score][column_B_score] != UNREAL ) {
                    curr_lead = get_lead(column_A_score, column_B_score);
                    curr_max_lead = max_lead[column_A_score][column_B_score];

                    for (int score : score_ways) {
                        if (column_A_score + score <= final_score.scoreA) {
                            next_lead = get_lead(column_A_score + score, column_B_score);
                            // make score real.
                            next_max_lead = make_next_lead_real(max_lead[column_A_score + score][column_B_score]);

                            if (curr_lead != TIE && next_lead != TIE && curr_lead != next_lead) {
                                max_lead[column_A_score + score][column_B_score] = max(curr_max_lead+1, next_max_lead);
                            } else {
                                max_lead[column_A_score + score][column_B_score] = max(curr_max_lead, next_max_lead);
                            }
                        }
                        if (column_B_score + score <= final_score.scoreB) {
                            next_lead = get_lead(column_A_score, column_B_score + score);
                            // make score real.
                            next_max_lead = make_next_lead_real(max_lead[column_A_score][column_B_score + score]);

                            if (curr_lead != TIE && next_lead != TIE && curr_lead != next_lead) {
                                max_lead[column_A_score][column_B_score + score] = max(curr_max_lead+1, next_max_lead);
                            } else {
                                max_lead[column_A_score][column_B_score + score] = max(curr_max_lead, next_max_lead);
                            }
                        }
                    }
                }
            }
        }

        return max_lead[final_score.scoreA][final_score.scoreB];
    }

    // This seems wrong. This code is from EPI.
    int count_lead_changes(int s, int t, const vector<int> &score_ways) {
        vector<vector<int>> lead_changes(s + 1, vector<int>(t + 1, -1));
        lead_changes[0][0] = 0;

        for (int i = 0; i <= s; ++i) {
            for (int j = 0; j <= t; ++j) {
                if (lead_changes[i][j] >= 0) {  // legal scores
                    for (const int &score : score_ways) {
                        int next_i = i + score;
                        int next_j = j + score;

                        if (next_j <= t && lead_changes[i][next_j] == -1) {
                            lead_changes[i][next_j] = 0;
                        }

                        if (next_j <= t) {
                            lead_changes[i][next_j] +=
                                    lead_changes[i][j] + (j < i && i < next_j);
                        }

                        if (next_i <= s && lead_changes[next_i][j] == -1) {
                            lead_changes[next_i][j] = 0;
                        }

                        if (next_i <= s) {
                            lead_changes[next_i][j] +=
                                    lead_changes[i][j] + (i < j && next_i > j);
                        }
                    }
                }
            }
        }
        return lead_changes[s][t];
    }
}

#endif //ALGORITHM_ANALYSIS_LEAD_CHANGES_H
