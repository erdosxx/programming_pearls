#ifndef ALGORITHM_ANALYSIS_REMOVE_DUPLICATES_FROM_SORTED_ARRAY_H
#define ALGORITHM_ANALYSIS_REMOVE_DUPLICATES_FROM_SORTED_ARRAY_H

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::random_device;
using std::stoul;
using std::uniform_int_distribution;
using std::vector;

// @include
// Returns the number of valid entries after deletion.
int DeleteDuplicates(vector<int>* A_ptr) {
    vector<int>& A = *A_ptr;
    if (A.empty()) {
        return 0;
    }

    int write_index = 1;
    for (int i = 1; i < A.size(); ++i) {
        if (A[write_index - 1] != A[i]) {
            A[write_index++] = A[i];
        }
    }
    return write_index;
}
// @exclude

bool CheckAns(const vector<int>& A, size_t n) {
    for (size_t i = 1; i < n; ++i) {
        if( A[i - 1] == A[i] )
            return false;
    }
    return true;
}

#endif //ALGORITHM_ANALYSIS_REMOVE_DUPLICATES_FROM_SORTED_ARRAY_H
