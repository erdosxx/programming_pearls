#ifndef ALGORITHM_ANALYSIS_NONUNIFORM_RANDOM_NUMBER_GENERATION_H
#define ALGORITHM_ANALYSIS_NONUNIFORM_RANDOM_NUMBER_GENERATION_H
// 6.15 Generate nonuniform random numbers

#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <random>
#include <vector>

using std::distance;
using std::numeric_limits;
using std::random_device;
using std::vector;
using std::generate_canonical;

// @include
int NonuniformRandomNumberGeneration(const vector<int>& values,
                                     const vector<double>& probabilities) {
    vector<double> prefix_sums_of_probabilities;
    prefix_sums_of_probabilities.emplace_back(0.0);
    // Creating the endpoints for the intervals corresponding to the
    // probabilities.
    partial_sum(probabilities.cbegin(), probabilities.cend(),
                back_inserter(prefix_sums_of_probabilities));

    default_random_engine seed((random_device())());
    double uniform_0_1 =
            generate_canonical<double, numeric_limits<double>::digits>(seed);
    // Find the index of the interval that uniform_0_1 lies in, which is the
    // return value of upper_bound() minus 1.
    //TODO: why distance function is needed.
    // See ref: http://stackoverflow.com/questions/13505562/getting-index-of-set-element-via-iterator
    long interval_idx =
            distance(
                    prefix_sums_of_probabilities.cbegin(),
                    upper_bound(prefix_sums_of_probabilities.cbegin(),
                                prefix_sums_of_probabilities.cend(), uniform_0_1)) -
            1;
    return values[interval_idx];
}
// @exclude

#endif //ALGORITHM_ANALYSIS_NONUNIFORM_RANDOM_NUMBER_GENERATION_H
