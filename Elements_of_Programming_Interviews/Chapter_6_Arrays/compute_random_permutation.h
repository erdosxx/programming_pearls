#ifndef ALGORITHM_ANALYSIS_COMPUTE_RANDOM_PERMUTATION_H
#define ALGORITHM_ANALYSIS_COMPUTE_RANDOM_PERMUTATION_H

// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <vector>

#include "Offline_sampling.h"

using std::vector;

// @include
vector<int> ComputeRandomPermutation(int n) {
    vector<int> permutation(n);
    // Initializes permutation to 0, 1, 2, ..., n - 1.
    iota(permutation.begin(), permutation.end(), 0);
    RandomSampling(permutation.size(), &permutation);
    return permutation;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_COMPUTE_RANDOM_PERMUTATION_H
