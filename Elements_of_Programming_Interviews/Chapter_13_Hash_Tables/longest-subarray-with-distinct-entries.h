#ifndef ALGORITHM_ANALYSIS_LONGEST_SUBARRAY_WITH_DISTINCT_ENTRIES_H
#define ALGORITHM_ANALYSIS_LONGEST_SUBARRAY_WITH_DISTINCT_ENTRIES_H
// 13.9 Find the longest subarray with distinct entries

#include <algorithm>
#include <string>
#include <unordered_map>
#include <unordered_set>

using std::max;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

namespace distinct {
// @include
    int LongestSubarrayWithDistinctEntries(const vector<int> &A) {
        // Records the most recent occurrences of each entry.
        unordered_map<int, size_t> most_recent_occurrence;
        size_t longest_dup_free_subarray_start_idx = 0;
        size_t result = 0;

        for (size_t i = 0; i < A.size(); ++i) {
            // unordered_map::emplace
            // If the insertion takes place (because no other element
            // existed with the same key), the function returns a pair object,
            // whose first component is an iterator to the inserted element,
            // and whose second component is true.
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
// @exclude

// O(n^2) checking solution.
    int CheckAns(const vector<int> &A) {
        size_t len = 0;
        for (size_t i = 0; i < A.size(); ++i) {
            unordered_set<int> table;
            size_t j;
            for (j = i; A.size() - i > len && j < A.size(); ++j) {
                if (!table.emplace(A[j]).second) { // if A[i] is already exist
                    break;
                }
            }
            len = max(len, j - i);
        }
        return len;
    }
}

#endif //ALGORITHM_ANALYSIS_LONGEST_SUBARRAY_WITH_DISTINCT_ENTRIES_H
