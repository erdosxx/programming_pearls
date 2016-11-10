#ifndef ALGORITHM_ANALYSIS_RESERVOIR_SAMPLING_H
#define ALGORITHM_ANALYSIS_RESERVOIR_SAMPLING_H
// 6.12 Sample online data

#include <cassert>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

using std::default_random_engine;
using std::random_device;
using std::string;
using std::vector;
using std::istringstream;
using std::uniform_int_distribution;

// See TAOCP II p.144 Algorith R

// @include
// Assumption: there are at least k elements in the stream.
vector<int> OnlineRandomSample(istringstream* sin, int k) {
    int x;
    vector<int> running_sample;
    // Stores the first k elements.
    // clang-format off
    for (int i = 0; i < k && *sin >> x; ++i) {
        // clang-format on
        running_sample.emplace_back(x);
    }

    default_random_engine seed((random_device())());  // Random num generator.
    // Have read the first k elements.
    int num_seen_so_far = k;
    while (*sin >> x) {
        ++num_seen_so_far;
        // Generate a random number in [0, num_seen_so_far - 1], and if this
        // number is in [0, k - 1], we replace that element from the sample with
        // x.
        int idx_to_replace =
                uniform_int_distribution<int>{0, num_seen_so_far - 1}(seed);
        if (idx_to_replace < k) {
            running_sample[idx_to_replace] = x;
        }
    }
    return running_sample;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_RESERVOIR_SAMPLING_H
