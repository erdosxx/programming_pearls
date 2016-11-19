#ifndef ALGORITHM_ANALYSIS_APPROXIMATE_SORT_H
#define ALGORITHM_ANALYSIS_APPROXIMATE_SORT_H
// 11.3 Sort an almost-sorted array

#include <functional>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

using std::greater;
using std::istringstream;
using std::priority_queue;
using std::string;
using std::stringstream;
using std::vector;

// @include
vector<int> SortApproximatelySortedData(istringstream* sequence, int k) {
    vector<int> result = {};
    priority_queue<int, vector<int>, greater<>> min_heap;
    // Adds the first k elements into min_heap. Stop if there are fewer than k
    // elements.
    int x;
    // clang-format off
    for (int i = 0; i < k && *sequence >> x; ++i) {
        // clang-format on
        min_heap.push(x);
    }

    // For every new element, add it to min_heap and extract the smallest.
    while (*sequence >> x) {
        min_heap.push(x);
        //cout << min_heap.top() << endl;
        result.emplace_back(min_heap.top());
        min_heap.pop();
    }

    // sequence is exhausted, iteratively extracts the remaining elements.
    while (!min_heap.empty()) {
        result.emplace_back(min_heap.top());
        // cout << min_heap.top() << endl;
        min_heap.pop();
    }
    return result;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_APPROXIMATE_SORT_H
