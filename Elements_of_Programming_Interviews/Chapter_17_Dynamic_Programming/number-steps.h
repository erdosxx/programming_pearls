#ifndef ALGORITHM_ANALYSIS_NUMBER_STEPS_H
#define ALGORITHM_ANALYSIS_NUMBER_STEPS_H

#include <algorithm>
#include <vector>

using std::vector;

namespace way_to_step {
    enum {uncalced = 0};

    int ComputeNumberOfWaysToH(int, int, vector<int> *);

// @include
    int NumberOfWaysToTop(int top, int maximum_step) {
        vector<int> number_of_ways_to_h(top + 1, uncalced);
        return ComputeNumberOfWaysToH(top, maximum_step, &number_of_ways_to_h);
    }

    int ComputeNumberOfWaysToH(int height, int maximum_step,
                               vector<int> *number_of_ways_to_h_ptr) {
        if (height <= 1) {
            return 1;
        }

        vector<int> &number_of_ways_to_h = *number_of_ways_to_h_ptr;

        if (number_of_ways_to_h[height] == uncalced) {
            for (int i = 1; i <= maximum_step && height - i >= 0; ++i) {
                number_of_ways_to_h[height] +=
                        ComputeNumberOfWaysToH(height - i, maximum_step, number_of_ways_to_h_ptr);
            }
        }
        return number_of_ways_to_h[height];
    }
// @exclude
}

#endif //ALGORITHM_ANALYSIS_NUMBER_STEPS_H
