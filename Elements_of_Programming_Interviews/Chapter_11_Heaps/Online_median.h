#ifndef ALGORITHM_ANALYSIS_ONLINE_MEDIAN_H
#define ALGORITHM_ANALYSIS_ONLINE_MEDIAN_H
// 11.5 Compute the median of online data

#include <functional>
#include <queue>
#include <random>
#include <sstream>
#include <string>
#include <vector>

using std::endl;
using std::greater;
using std::istringstream;
using std::less;
using std::priority_queue;
using std::string;
using std::stringstream;
using std::vector;

// @include
vector<double> OnlineMedian(istringstream* sequence) {
    vector<double> result;
    // min_heap stores the larger half seen so far.
    priority_queue<int, vector<int>, greater<>> min_heap;
    // max_heap stores the smaller half seen so far.
    priority_queue<int, vector<int>, less<>> max_heap;

    int x;
    while (*sequence >> x) {
        if (min_heap.empty()) {
            // This is the very first element.
            min_heap.emplace(x);
        } else {
            if (x >= min_heap.top()) {
                min_heap.emplace(x);
            } else {
                max_heap.emplace(x);
            }
        }
        // Ensure min_heap and max_heap have equal number of elements if
        // an even number of elements is read; otherwise, min_heap must have
        // one more element than max_heap.
        if (min_heap.size() > max_heap.size() + 1) {
            max_heap.emplace(min_heap.top());
            min_heap.pop();
        } else if (max_heap.size() > min_heap.size()) {
            min_heap.emplace(max_heap.top());
            max_heap.pop();
        }

        // @exclude
        result.emplace_back(min_heap.size() == max_heap.size()
                                   ? 0.5 * (min_heap.top() + max_heap.top())
                                   : min_heap.top());
        // @include
//        cout << (min_heap.size() == max_heap.size()
//                 ? 0.5 * (min_heap.top() + max_heap.top())
//                 : min_heap.top())
//        << endl;
    }
    return result;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_ONLINE_MEDIAN_H
