#ifndef ALGORITHM_ANALYSIS_ONLINE_SAMPLING_H
#define ALGORITHM_ANALYSIS_ONLINE_SAMPLING_H

#include <algorithm>
#include <random>
#include <unordered_map>
#include <vector>

using std::default_random_engine;
using std::random_device;
using std::uniform_int_distribution;
using std::unordered_map;
using std::vector;

// @include
// Returns a random k-sized subset of {0, 1, ..., n - 1}.
// See: TAOCP II page 148 #15

using umap_type = unordered_map<int,int>;
using umap_iter_type = umap_type ::iterator;

enum {not_exist=-1};

void exchange_position(unordered_map<int, int> &changed_elements, const int &select_position, const int &random_position);

int search_position(umap_type &umap, int position) {
    umap_iter_type position_iter = umap.find(position);
    return position_iter != umap.end() ? position_iter->second : not_exist;
}

vector<int> RandomSubset(int n, int k) {
    // map position with datq.
    unordered_map<int, int> changed_elements;

    default_random_engine seed((random_device())());  // Random num generator.

    for (int select_position = 0; select_position < k; ++select_position) {
        // Generate a random index in [i, n - 1].
        int random_position = uniform_int_distribution<int>{select_position, n - 1}(seed);

        exchange_position(changed_elements, select_position, random_position);
    }

    vector<int> result;
    for (int i = 0; i < k; ++i) {
        result.emplace_back(changed_elements[i]);
    }
    return result;
}

// exchange data between select_position and random_position.
void exchange_position(umap_type& changed_elements, const int& select_position, const int& random_position) {
    int rand_idx = search_position(changed_elements, random_position);
    int select_idx = search_position(changed_elements, select_position);

    if (rand_idx == not_exist &&
        select_idx == not_exist) {
        changed_elements[random_position] = select_position;
        changed_elements[select_position] = random_position;

    } else if (rand_idx == not_exist &&
               select_idx != not_exist) {
        changed_elements[random_position] = changed_elements[select_idx];
        changed_elements[select_idx] = random_position;

    } else if (rand_idx != not_exist &&
               select_idx == not_exist) {
        changed_elements[select_position] = changed_elements[rand_idx];
        changed_elements[rand_idx] = select_position;

    } else {
        swap(changed_elements[select_idx], changed_elements[rand_idx]);
    }
}
// @exclude

#endif //ALGORITHM_ANALYSIS_ONLINE_SAMPLING_H
