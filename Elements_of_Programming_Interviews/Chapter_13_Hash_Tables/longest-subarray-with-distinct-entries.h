#ifndef ALGORITHM_ANALYSIS_LONGEST_SUBARRAY_WITH_DISTINCT_ENTRIES_H
#define ALGORITHM_ANALYSIS_LONGEST_SUBARRAY_WITH_DISTINCT_ENTRIES_H
// 13.9 Find the longest subarray with distinct entries

#include <algorithm>
#include <string>
#include <unordered_map>

using std::max;
using std::string;
using std::unordered_map;
using std::vector;

namespace distinct {

    int LongestSubarrayWithDistinctEntries(const vector<int> &A) {
        // Records the most recent occurrences of each entry.
        unordered_map<int, size_t> most_recent_occurrence;
        size_t longest_dup_free_subarray_start_idx = 0;
        size_t result = 0;

        for (size_t i = 0; i < A.size(); ++i) {
            // unordered_map
            // pair<iterator, bool> emplace ( Args&&... args );
            auto dup_idx = most_recent_occurrence.emplace(A[i], i);
            // Defer updating dup_idx until we see a duplicate.
            if (!dup_idx.second) { // if A[i] is already exist in most_recent_occurrence
                // A[i] appeared before. Did it appear in the longest current subarray?
                if (dup_idx.first->second >= longest_dup_free_subarray_start_idx) {
                    result = max(result, i - longest_dup_free_subarray_start_idx);
                    longest_dup_free_subarray_start_idx = dup_idx.first->second + 1;
                }
                dup_idx.first->second = i;
            }
        }
        result = max(result, A.size() - longest_dup_free_subarray_start_idx);
        return result;
    }
}

#endif //ALGORITHM_ANALYSIS_LONGEST_SUBARRAY_WITH_DISTINCT_ENTRIES_H
