#ifndef ALGORITHM_ANALYSIS_BONUS_H
#define ALGORITHM_ANALYSIS_BONUS_H
// 25.14 Compute fair bonuses

#include <algorithm>
#include <functional>
#include <queue>
#include <numeric>
#include <string>
#include <vector>
#include <utility>

using std::function;
using std::max;
using std::priority_queue;
using std::vector;
using std::equal;


// @include
vector<int> CalculateBonus(const vector<int>& productivity) {
    struct EmployeeData {
        int index;
        int productivity;
    };

    // for the syntax of priority queue see the following url
    // http://stackoverflow.com/questions/16111337/declaring-a-priority-queue-in-c-with-a-custom-comparator
    priority_queue<EmployeeData, vector<EmployeeData>, function<bool(EmployeeData, EmployeeData)>>
            min_heap([](const EmployeeData& lhs, const EmployeeData& rhs) {
        return lhs.productivity > rhs.productivity;
    });

    for (int i = 0; i < productivity.size(); ++i) {
        min_heap.emplace(EmployeeData{i, productivity[i]});
    }

    // Initially assigns one ticket to everyone.
    vector<int> tickets(productivity.size(), 1);

    // Fills tickets from lowest rating to highest rating.
    while (!min_heap.empty()) {
        int next_dev = min_heap.top().index;

        // Handles the left neighbor.
        if (next_dev > 0) { // if left neighbor is exist
            if (productivity[next_dev] > productivity[next_dev - 1]) {
                tickets[next_dev] = tickets[next_dev - 1] + 1;
            }
        }

        // Handles the right neighbor.
        if (next_dev + 1 < tickets.size()) { // if right neighbor is exist
            if (productivity[next_dev] > productivity[next_dev + 1]) {
                tickets[next_dev] = max(tickets[next_dev], tickets[next_dev + 1] + 1);
            }
        }

        min_heap.pop();
    }
    return tickets;
}
// @exclude

template <typename T>
bool EqualVector(const vector<T>& A, const vector<T>& B) {
    return equal(A.begin(), A.end(), B.begin(), B.end());
}

#endif //ALGORITHM_ANALYSIS_BONUS_H
