#ifndef ALGORITHM_ANALYSIS_SUBSEQ_COVER_H
#define ALGORITHM_ANALYSIS_SUBSEQ_COVER_H
// 13.8 Find smallest subarray sequentially covering all values

#include <algorithm>
#include <limits>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include "Smallest_subarray_covering_set.h"

using std::numeric_limits;
using std::string;
using std::unordered_map;
using std::vector;

Subarray FindSmallestSequentiallyCoveringSubset(
        const vector<string>& paragraph, const vector<string>& keywords) {
    // Maps each keyword to its index in the keywords array.
    unordered_map<string, int> keyword_to_idx;
    // Initializes keyword_to_idx.
    for (int i = 0; i < keywords.size(); ++i) {
        keyword_to_idx.emplace(keywords[i], i);
    }

    // Since keywords are uniquely identified by their indices in keywords
    // array, we can use those indices as keys to lookup in a vector.
    vector<int> latest_occurrence(keywords.size(), -1);
    // For each keyword (identified by its index in keywords array), stores the
    // length of the shortest subarray ending at the most recent occurrence of
    // that keyword that sequentially cover all keywords up to that keyword.
    vector<int> shortest_subarray_length(keywords.size(),
                                         numeric_limits<int>::max());

    int shortest_distance = numeric_limits<int>::max();
    Subarray result = Subarray{-1, -1};

    for (int i = 0; i < paragraph.size(); ++i) {
        if (keyword_to_idx.count(paragraph[i])) {
            //int keyword_idx = keyword_to_idx.find(paragraph[i])->second;
            int keyword_idx = keyword_to_idx.at(paragraph[i]);

            if (keyword_idx == 0) {  // First keyword.
                shortest_subarray_length[keyword_idx] = 1;
            } else if (shortest_subarray_length[keyword_idx - 1] !=
                       numeric_limits<int>::max()) {
                int distance_to_previous_keyword =
                        i - latest_occurrence[keyword_idx - 1];
                shortest_subarray_length[keyword_idx] =
                        distance_to_previous_keyword +
                        shortest_subarray_length[keyword_idx - 1];
            }
            latest_occurrence[keyword_idx] = i;

            // Last keyword, look for improved subarray.
            if (keyword_idx == keywords.size() - 1 &&
                shortest_subarray_length.back() < shortest_distance) {
                shortest_distance = shortest_subarray_length.back();
                result = {i - shortest_subarray_length.back() + 1, i};
            }
        }
    }
    return result;
}


#endif //ALGORITHM_ANALYSIS_SUBSEQ_COVER_H
