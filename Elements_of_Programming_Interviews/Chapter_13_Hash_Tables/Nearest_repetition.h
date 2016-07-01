#ifndef ALGORITHM_ANALYSIS_NEAREST_REPETITION_H
#define ALGORITHM_ANALYSIS_NEAREST_REPETITION_H

#include <algorithm>
#include <limits>
#include <string>
#include <unordered_map>
#include <vector>

using std::max;
using std::min;
using std::string;
using std::unordered_map;
using std::vector;
using std::numeric_limits;

namespace near {

    string RandString(int len) {
        default_random_engine gen((random_device()) ());
        string ret = "";
        while (len--) {
            uniform_int_distribution<int> dis('a', 'z');
            ret += dis(gen);
        }
        return ret;
    }

// @include
    int FindNearestRepetition(const vector<string> &paragraph) {
        unordered_map<string, int> word_to_latest_index;
        int nearest_repeated_distance = numeric_limits<int>::max();

        for (int i = 0; i < paragraph.size(); ++i) {
            auto latest_equal_word = word_to_latest_index.find(paragraph[i]);
            if (latest_equal_word != word_to_latest_index.end()) {
                nearest_repeated_distance =
                        min(nearest_repeated_distance, i - latest_equal_word->second);
            }
            word_to_latest_index[paragraph[i]] = i;
        }
        return nearest_repeated_distance;
    }
// @exclude

// O(n^2) checking
    int CheckAnswer(const vector<string> &s) {
        int nearest_repeated_distance = numeric_limits<int>::max();
        for (int i = 0; i < s.size(); ++i) {
            for (int j = i + 1; j < s.size(); ++j) {
                if (s[i] == s[j]) {
                    nearest_repeated_distance = min(nearest_repeated_distance, j - i);
                }
            }
        }
        return nearest_repeated_distance;
    }
}

#endif //ALGORITHM_ANALYSIS_NEAREST_REPETITION_H
