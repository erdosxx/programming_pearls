#ifndef ALGORITHM_ANALYSIS_BONUS_IMPROVED_H
#define ALGORITHM_ANALYSIS_BONUS_IMPROVED_H
//25.14 Compute fair bonuses

#include <algorithm>
#include <numeric>
#include <string>
#include <vector>
#include <utility>

using std::max;
using std::pair;
using std::vector;
using std::equal;

namespace imp {
// @include
    vector<int> CalculateBonus(const vector<int> &productivity) {
        // Initially assigns one ticket to everyone.
        vector<int> tickets(productivity.size(), 1);

        // From left to right.
        for (int i = 1; i < productivity.size(); ++i) {
            if (productivity[i] > productivity[i - 1]) {
                tickets[i] = tickets[i - 1] + 1;
            }
        }
        // From right to left.
        for (int i = productivity.size() - 2; i >= 0; --i) {
            if (productivity[i] > productivity[i + 1]) {
                tickets[i] = max(tickets[i], tickets[i + 1] + 1);
            }
        }
        return tickets;
    }
// @exclude

    template<typename T>
    bool EqualVector(const vector <T> &A, const vector <T> &B) {
        return equal(A.begin(), A.end(), B.begin(), B.end());
    }
}

#endif //ALGORITHM_ANALYSIS_BONUS_IMPROVED_H
