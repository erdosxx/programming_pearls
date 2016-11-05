#ifndef ALGORITHM_ANALYSIS_3_4_2_FLOYD_ALGORITHM_H
#define ALGORITHM_ANALYSIS_3_4_2_FLOYD_ALGORITHM_H

#include <vector>
#include <random>
#include <unordered_map>

using std::random_device;
using std::uniform_int_distribution;
using std::default_random_engine;
using std::unordered_map;

enum {selected = 1};

vector<int> floyd_sampling(int n, vector<int>* array_ptr) {
    vector<int>& array = *array_ptr;

    default_random_engine seed((random_device())());

    int array_size = static_cast<int>(array.size());

    unordered_map<int, int> sampling_pool;
    vector<int> result;

    for(int i = array_size - n; i < array_size; i++) {
        int random_num = uniform_int_distribution<int>{0, i}(seed);

        if (sampling_pool.find(random_num) == sampling_pool.end()) {
            sampling_pool[random_num] = selected;
            result.emplace_back(array[random_num]);
        } else {
            sampling_pool[i] = selected;
            result.emplace_back(array[i]);
        }
    }

    return result;
}

#endif //ALGORITHM_ANALYSIS_3_4_2_FLOYD_ALGORITHM_H
