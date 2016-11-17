#ifndef ALGORITHM_ANALYSIS_MIN_INDEX_DISTANCE_H
#define ALGORITHM_ANALYSIS_MIN_INDEX_DISTANCE_H
// Source: Rakuten (Codility)

#include <vector>
#include <limits>
#include <map>
#include <iterator>

using std::vector;
using std::map;
using std::next;

int min_distance(const vector<int>& a, const vector<int> b) {
    int min_distance = numeric_limits<int>::max();

    int i = 0;
    int j = 0;
    while(i < a.size() && j < b.size()) {
        int new_dist = a[i] > b[j] ? a[i] - b[j++] : b[j] - a[i++];
        min_distance = new_dist < min_distance ? new_dist : min_distance;
    }

    return min_distance;
}

int Solution(vector<int>& A) {
    int min_dist = numeric_limits<int>::max();

    map<int, vector<int>> index_map;

    for (int i = 0; i < A.size() ; ++i) {
        index_map[A[i]].emplace_back(i);
    }

    // all same
    if (index_map.size() == 1) {
        return -1;
    }

    map<int, vector<int>>::iterator iter;
    for (iter = index_map.begin(); next(iter) != index_map.end(); ++iter) {
        vector<int>& vec1 = iter->second;
        vector<int>& vec2 = next(iter)->second;

        int new_dist = min_distance(vec1, vec2);
        min_dist = new_dist < min_dist ? new_dist : min_dist;
    }

    return min_dist;
}

#endif //ALGORITHM_ANALYSIS_MIN_INDEX_DISTANCE_H
