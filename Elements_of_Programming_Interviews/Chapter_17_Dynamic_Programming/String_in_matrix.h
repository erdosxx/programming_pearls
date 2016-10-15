#ifndef ALGORITHM_ANALYSIS_STRING_IN_MATRIX_H
#define ALGORITHM_ANALYSIS_STRING_IN_MATRIX_H

#include <algorithm>
#include <tuple>
#include <unordered_set>
#include <vector>

using std::get;
using std::hash;
using std::tuple;
using std::unordered_set;
using std::vector;

struct HashTuple;

bool IsPatternSuffixContainedStartingAtXY(
        const vector<vector<int>>&, int, int, const vector<int>&, int,
        unordered_set<tuple<int, int, int>, HashTuple>*);

// @include
struct HashTuple {
    size_t operator()(const tuple<int, int, int>& t) const {
        return hash<int>()(get<0>(t) ^ get<1>(t) * 1021 ^ get<2>(t) * 1048573);
    }
};

bool IsPatternContainedInGrid(const vector<vector<int>>& grid,
                              const vector<int>& pattern) {
    // Each entry in previous_attempts is a point in the grid and suffix of
    // pattern (identified by its offset). Presence in previousAttempts
    // indicates
    // the suffix is not contained in the grid starting from that point.
    unordered_set<tuple<int, int, int>, HashTuple> previous_attempts;

    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
            if (IsPatternSuffixContainedStartingAtXY(grid, i, j, pattern, 0,
                                                     &previous_attempts)) {
                return true;
            }
        }
    }
    return false;
}

bool IsPatternSuffixContainedStartingAtXY(
        const vector<vector<int>>& grid, int x, int y, const vector<int>& pattern,
        int offset,
        unordered_set<tuple<int, int, int>, HashTuple>* previous_attempts) {
    if (pattern.size() == offset) {
        // Nothing left to complete.
        return true;
    }

    // Check if (x, y) lies outside the grid.
    if (x < 0 || x >= grid.size() || y < 0 || y >= grid[x].size() ||
        previous_attempts->find({x, y, offset}) != previous_attempts->cend()) {
        return false;
    }

    if (grid[x][y] == pattern[offset] &&
        (IsPatternSuffixContainedStartingAtXY(grid, x - 1, y, pattern,
                                              offset + 1, previous_attempts) ||
         IsPatternSuffixContainedStartingAtXY(grid, x + 1, y, pattern,
                                              offset + 1, previous_attempts) ||
         IsPatternSuffixContainedStartingAtXY(grid, x, y - 1, pattern,
                                              offset + 1, previous_attempts) ||
         IsPatternSuffixContainedStartingAtXY(grid, x, y + 1, pattern,
                                              offset + 1, previous_attempts))) {
        return true;
    }
    previous_attempts->emplace(x, y, offset);
    return false;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_STRING_IN_MATRIX_H
