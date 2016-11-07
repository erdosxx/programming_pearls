#ifndef ALGORITHM_ANALYSIS_POWER_SET_ALTERNATIVE_H
#define ALGORITHM_ANALYSIS_POWER_SET_ALTERNATIVE_H
// 16.4 Generate the power set

#include <algorithm>
#include <vector>

using std::vector;

namespace alt {
    void DirectedPowerSet(const vector<int> & input_set, int to_be_selected, vector<int> *selected_so_far,
                          vector<vector<int>> *power_set);

// @include
    vector<vector<int>> GeneratePowerSet(const vector<int> &input_set) {
        vector<vector<int>> power_set;
        DirectedPowerSet(input_set, 0, new vector<int>, &power_set);
        return power_set;
    }

// Generate all subsets whose intersection with input_set[0], ...,
// input_set[to_be_selected - 1] is exactly selected_so_far.
    void DirectedPowerSet(const vector<int> &input_set, int to_be_selected,
                          vector<int> *selected_so_far,
                          vector<vector<int>> *power_set) {
        if (to_be_selected == input_set.size()) {
            power_set->emplace_back(*selected_so_far);
            return;
        }
        // Generate all subsets that contain input_set[to_be_selected].
        selected_so_far->emplace_back(input_set[to_be_selected]);
        DirectedPowerSet(input_set, to_be_selected + 1, selected_so_far, power_set);
        // Generate all subsets that do not contain input_set[to_be_selected].
        selected_so_far->pop_back();
        DirectedPowerSet(input_set, to_be_selected + 1, selected_so_far, power_set);
    }
// @exclude
}

#endif //ALGORITHM_ANALYSIS_POWER_SET_ALTERNATIVE_H
