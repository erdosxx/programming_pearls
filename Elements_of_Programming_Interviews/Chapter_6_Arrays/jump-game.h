#ifndef ALGORITHM_ANALYSIS_JUMP_GAME_H
#define ALGORITHM_ANALYSIS_JUMP_GAME_H
// 6.4 Advancing through an array

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using std::max;
using std::vector;

// @include
bool CanReachEnd(const vector<int>& max_advance_steps) {
    int furthest_reach_so_far = 0;
    int last_index = max_advance_steps.size() - 1;

    for (int i = 0;
         i <= furthest_reach_so_far && furthest_reach_so_far < last_index;
         ++i) {
        furthest_reach_so_far =
                max(furthest_reach_so_far, max_advance_steps[i] + i);
    }
    return furthest_reach_so_far >= last_index;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_JUMP_GAME_H
