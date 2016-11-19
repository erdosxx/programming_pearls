#ifndef ALGORITHM_ANALYSIS_NEAREST_REPETITION_H
#define ALGORITHM_ANALYSIS_NEAREST_REPETITION_H
// 13.6 Find the nearest repeated entries in an array

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

    size_t FindNearestRepetition(const vector<string>& paragraph) {
        unordered_map<string, size_t> word_to_latest_index;
        size_t nearest_repeated_distance = numeric_limits<size_t>::max();

        for (int i = 0; i < paragraph.size(); ++i) {
            auto latest_equal_word = word_to_latest_index.find(paragraph[i]);
            if (latest_equal_word != word_to_latest_index.end()) {
                nearest_repeated_distance = min(nearest_repeated_distance, i - latest_equal_word->second);
            }
            word_to_latest_index[paragraph[i]] = i;
        }
        return nearest_repeated_distance;
    }

}

#endif //ALGORITHM_ANALYSIS_NEAREST_REPETITION_H
