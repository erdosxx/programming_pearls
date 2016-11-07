#ifndef ALGORITHM_ANALYSIS_LONGEST_NONDECREASING_SUBSEQUENCE_NLOGN_H
#define ALGORITHM_ANALYSIS_LONGEST_NONDECREASING_SUBSEQUENCE_NLOGN_H
// 17.12 Find the longest nondecreasing subsequence

#include <algorithm>
#include <vector>

using std::vector;

namespace LNS_nlogn {

// @include
    int LongestNondecreasingSubsequenceLength(const vector<int>& A) {
        vector<int> tail_values;

        for (int a : A) {
            // template <class ForwardIterator, class T>
            // ForwardIterator upper_bound (ForwardIterator first, ForwardIterator last,
            //                             const T& val);
            // Returns an iterator pointing to the first element in the range
            // [first,last) which compares greater than val.
            auto it = upper_bound(tail_values.begin(), tail_values.end(), a);

            if (it == tail_values.end()) {
                tail_values.emplace_back(a);
            } else {
                *it = a;
            }
        }
        return tail_values.size();
    }
// @exclude

}  // LNS_nlogn

#endif //ALGORITHM_ANALYSIS_LONGEST_NONDECREASING_SUBSEQUENCE_NLOGN_H
