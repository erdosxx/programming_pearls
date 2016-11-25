#ifndef ALGORITHM_ANALYSIS_OFFLINE_SAMPLING_H
#define ALGORITHM_ANALYSIS_OFFLINE_SAMPLING_H
// 6.11 Sample offline data

#include <algorithm>
#include <random>
#include <vector>

using std::default_random_engine;
using std::random_device;
using std::swap;
using std::uniform_int_distribution;
using std::vector;

// @include
void RandomSampling(int k, vector<int>* A_ptr) {
    vector<int>& A = *A_ptr;
    random_device rd;
    default_random_engine seed(rd());
    //default_random_engine seed((random_device())());  // Random num generator.

    for (int i = 0; i < k; ++i) {
        // Generate a random index in [i, A.size() - 1].
        swap(A[i], A[uniform_int_distribution<int>{
                i, static_cast<int>(A.size()) - 1}(seed)]);
    }
}
// @exclude

#endif //ALGORITHM_ANALYSIS_OFFLINE_SAMPLING_H
