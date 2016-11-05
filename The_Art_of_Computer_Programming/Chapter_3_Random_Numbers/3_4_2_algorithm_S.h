#ifndef ALGORITHM_ANALYSIS_3_4_2_ALGORITHM_S_H
#define ALGORITHM_ANALYSIS_3_4_2_ALGORITHM_S_H

// TAOCP I 3.4.2 Algorithm S page 142.

#include <vector>
#include <random>

using std::vector;
using std::default_random_engine;
using std::random_device;
using std::uniform_int_distribution;

vector<int> selection_sampling(const int num_of_selects, vector<int>* A_ptr) {
    vector<int>& A = *A_ptr;
    default_random_engine seed((random_device())());

    int select_so_far = 0;
    vector<int> result(num_of_selects);

    for(int t = 0; t < A.size(); t++) {
        // Generate a random int in [0, A.size() -t -1].
        int random_n = uniform_int_distribution<int>{0, static_cast<int>(A.size()-t-1)}(seed);

        int remaining = num_of_selects - select_so_far;
        if( random_n < remaining ) { // select with probability: remaining/(A.size() -t +1)
            result[select_so_far++] = A[t]; // save selected items from the first.
        };

        if(select_so_far == num_of_selects) {
            break;
        }
    }
    return result;
}

#endif //ALGORITHM_ANALYSIS_3_4_2_ALGORITHM_S_H
