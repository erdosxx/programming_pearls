#ifndef ALGORITHM_ANALYSIS_GRAY_CODE_BACKTRACK_H
#define ALGORITHM_ANALYSIS_GRAY_CODE_BACKTRACK_H

#include <algorithm>
#include <string>
#include <unordered_set>
#include <vector>

using std::string;
using std::unordered_set;
using std::vector;

namespace backtrack {

    bool DirectedGrayCode(int, unordered_set<int> *, vector<int> *);

    bool DiffersByOneBit(int, int);

// @include
    vector<int> GrayCode(int num_bits) {
        vector<int> result({0});
        DirectedGrayCode(num_bits, new unordered_set<int>({0}), &result);
        return result;
    }

    bool DirectedGrayCode(int num_bits, unordered_set<int> *history,
                          vector<int> *result) {
        if (result->size() == (1 << num_bits)) {
            // Check if the first and last codes differ by one bit.
            return DiffersByOneBit(result->front(), result->back());
        }

        for (int i = 0; i < num_bits; ++i) {
            int previous_code = result->back();
            int candidate_next_code = previous_code ^(1 << i);

            if (!history->count(candidate_next_code)) {
                history->emplace(candidate_next_code);
                result->emplace_back(candidate_next_code);

                if (DirectedGrayCode(num_bits, history, result)) {
                    return true;
                }

                history->erase(candidate_next_code);
                result->pop_back();
            }
        }
        return false;
    }

    bool DiffersByOneBit(int x, int y) {
        int bit_difference = x ^y;
        return bit_difference && !(bit_difference & (bit_difference - 1));
    }
// @exclude
}

#endif //ALGORITHM_ANALYSIS_GRAY_CODE_BACKTRACK_H
