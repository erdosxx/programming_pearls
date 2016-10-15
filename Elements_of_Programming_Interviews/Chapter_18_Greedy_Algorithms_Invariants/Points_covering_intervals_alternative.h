#ifndef ALGORITHM_ANALYSIS_POINTS_COVERING_INTERVALS_ALTERNATIVE_H
#define ALGORITHM_ANALYSIS_POINTS_COVERING_INTERVALS_ALTERNATIVE_H

#include <algorithm>
#include <unordered_set>
#include <vector>

using std::unordered_set;
using std::vector;

namespace alt {
    enum {Right = 0, Left = 1};

    struct EndPoint;

    vector<int> FindMinimumVisitsHelper(const vector<EndPoint> &);

// @include
    struct Interval {
        int left, right;
    };

    struct EndPoint {
        bool operator<(const EndPoint &that) const {
            const int a = is_left ? ptr->left : ptr->right;
            const int b = that.is_left ? that.ptr->left : that.ptr->right;

            return a < b || (a == b && is_left && !that.is_left);
        }

        const Interval *ptr;
        bool is_left;
    };

    vector<int> FindMinimumVisits(const vector<Interval> &intervals) {
        vector<EndPoint> endpoints;

        for (size_t i = 0; i < intervals.size(); ++i) {
            endpoints.emplace_back(EndPoint{&intervals[i], Left});
            endpoints.emplace_back(EndPoint{&intervals[i], Right});
        }

        sort(endpoints.begin(), endpoints.end());

        return FindMinimumVisitsHelper(endpoints);
    }

    vector<int> FindMinimumVisitsHelper(const vector<EndPoint> &endpoints) {
        vector<int> S;  // A minimum set of visit times.
        unordered_set<const Interval *> covered;
        vector<const Interval *> covering;

        for (const EndPoint &e : endpoints) {
            if (e.is_left) {
                covering.emplace_back(e.ptr);
            } else if (covered.find(e.ptr) == covered.end()) {
                // e's interval has not been covered.
                S.emplace_back(e.ptr->right);
                // Adds all intervals in covering to covered.
                covered.insert(covering.cbegin(), covering.cend());
                covering.clear();  // e is contained in all intervals in covering.
            }
        }

        return S;
    }
// @exclude
}

#endif //ALGORITHM_ANALYSIS_POINTS_COVERING_INTERVALS_ALTERNATIVE_H
