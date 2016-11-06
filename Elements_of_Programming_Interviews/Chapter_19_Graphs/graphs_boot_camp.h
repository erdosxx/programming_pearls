#ifndef ALGORITHM_ANALYSIS_GRAPHS_BOOT_CAMP_H
#define ALGORITHM_ANALYSIS_GRAPHS_BOOT_CAMP_H

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using std::string;
using std::vector;
using std::make_unique;
using std::unordered_set;
using std::unordered_map;

// testing for const. This is related to the source of 19.9 ----------
struct const_with_null_test {
    const int a = 0;
    const int* b_ptr = nullptr;
};

struct const_test {
    const int a = 0;
    int* b_ptr = nullptr;
};
// ---------------------------

// See team_reachability.h for the source, match results.

#endif //ALGORITHM_ANALYSIS_GRAPHS_BOOT_CAMP_H
