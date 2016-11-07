#ifndef ALGORITHM_ANALYSIS_POWER_SET_H
#define ALGORITHM_ANALYSIS_POWER_SET_H
// 16.4 Generate the power set

#include <cmath>
#include <vector>

using std::vector;

// @include
vector<vector<int>> GeneratePowerSet(const vector<int>& input_set) {
    vector<vector<int>> power_set;

    for (int int_for_subset = 0; int_for_subset < (1 << input_set.size()); ++int_for_subset) {
        int bit_array = int_for_subset;
        vector<int> subset;
        int least_1_bit;

        while (bit_array) {
            least_1_bit = bit_array & ~(bit_array -1);
            subset.emplace_back(input_set[log2(least_1_bit)]);
            // remove least 1 bit
            bit_array &= bit_array - 1;
        }
        power_set.emplace_back(subset);
    }
    return power_set;
}
// @exclude


#endif //ALGORITHM_ANALYSIS_POWER_SET_H
