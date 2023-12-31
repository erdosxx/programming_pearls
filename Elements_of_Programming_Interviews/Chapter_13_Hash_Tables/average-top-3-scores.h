#ifndef ALGORITHM_ANALYSIS_AVERAGE_TOP_3_SCORES_H
#define ALGORITHM_ANALYSIS_AVERAGE_TOP_3_SCORES_H
//13.11 Compute the average of the top three scores.

#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

using std::default_random_engine;
using std::greater;
using std::ifstream;
using std::map;
using std::ofstream;
using std::priority_queue;
using std::random_device;
using std::string;
using std::uniform_int_distribution;
using std::unordered_map;
using std::vector;

namespace p_13_11 {
    int GetTopThreeScoresSum(priority_queue<int, vector<int>, greater<>>);

// @include
    string FindStudentWithHighestBestOfThreeScores(ifstream *ifs) {
        // Use a multiset to handle duplicated test scores.
        unordered_map<string, priority_queue<int, vector<int>, greater<>>>
                student_scores;
        string name;
        int score;
        while (*ifs >> name >> score) {
            student_scores[name].emplace(score);
            if (student_scores[name].size() > 3) {
                student_scores[name].pop();  // Only keep the top 3 scores.
            }
        }

        string top_student = "no such student";
        int current_top_three_scores_sum = 0;
        for (const auto &scores : student_scores) {
            if (scores.second.size() == 3) {
                int current_scores_sum = GetTopThreeScoresSum(scores.second);
                if (current_scores_sum > current_top_three_scores_sum) {
                    current_top_three_scores_sum = current_scores_sum;
                    top_student = scores.first;
                }
            }
        }
        return top_student;
    }

// Returns the sum of top three scores.
    int GetTopThreeScoresSum(priority_queue<int, vector<int>, greater<>> scores) {
        int sum = 0;
        while (!scores.empty()) {
            sum += scores.top();
            scores.pop();
        }
        return sum;
    }
// @exclude

    string RandString(int len) {
        random_device rd;
        default_random_engine gen(rd());
        //default_random_engine gen((random_device()) ());
        uniform_int_distribution<int> dis('a', 'z');
        string ret;
        while (len--) {
            ret += dis(gen);
        }
        return ret;
    }
}

#endif //ALGORITHM_ANALYSIS_AVERAGE_TOP_3_SCORES_H
