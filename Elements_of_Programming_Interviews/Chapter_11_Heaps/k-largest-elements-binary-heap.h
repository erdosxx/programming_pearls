#ifndef ALGORITHM_ANALYSIS_K_LARGEST_ELEMENTS_BINARY_HEAP_H
#define ALGORITHM_ANALYSIS_K_LARGEST_ELEMENTS_BINARY_HEAP_H
// 11.6 Compute the k largest elements in a max-heap

#include <functional>
#include <queue>
#include <utility>
#include <vector>

using std::function;
using std::pair;
using std::priority_queue;
using std::vector;

// @include
vector<int> KLargestInBinaryHeap(const vector<int>& A, int k) {
    if (k <= 0) {
        return {};
    }

    struct HeapEntry {
        int index, value;
    };

    priority_queue<HeapEntry, vector<HeapEntry>,
            function<bool(HeapEntry, HeapEntry)>>
            candidate_max_heap([](const HeapEntry& a, const HeapEntry& b) -> bool {
        return a.value < b.value;
    });

    // The largest element in A is at index 0.
    candidate_max_heap.emplace(HeapEntry{0, A[0]});
    vector<int> result;

    for (int i = 0; i < k; ++i) {
        int candidate_idx = candidate_max_heap.top().index;
        result.emplace_back(candidate_max_heap.top().value);
        candidate_max_heap.pop();

        int left_child_idx = 2 * candidate_idx + 1;
        if (left_child_idx < A.size()) {
            candidate_max_heap.emplace(
                    HeapEntry{left_child_idx, A[left_child_idx]});
        }
        int right_child_idx = 2 * candidate_idx + 2;
        if (right_child_idx < A.size()) {
            candidate_max_heap.emplace(
                    HeapEntry{right_child_idx, A[right_child_idx]});
        }
    }
    return result;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_K_LARGEST_ELEMENTS_BINARY_HEAP_H
