#ifndef ALGORITHM_ANALYSIS_POINTS_COVERING_INTERVALS_H
#define ALGORITHM_ANALYSIS_POINTS_COVERING_INTERVALS_H

#include <algorithm>
#include <set>
#include <vector>

using std::set;
using std::vector;

// @include
struct Interval {
    int left, right;
};

struct LeftComp {
    bool operator()(const Interval* a, const Interval* b) const {
        return a->left != b->left ? a->left < b->left : a->right < b->right;
    }
};

struct RightComp {
    bool operator()(const Interval* a, const Interval* b) const {
        return a->right != b->right ? a->right < b->right : a->left < b->left;
    }
};

vector<int> FindMinimumVisits(const vector<Interval>& intervals) {
    set<const Interval*, LeftComp> L;
    set<const Interval*, RightComp> R;

    for (const Interval& i : intervals) {
        L.emplace(&i);
        R.emplace(&i);
    }

    vector<int> S;

    while (!L.empty() && !R.empty()) {
        int b = (*R.cbegin())->right;
        S.emplace_back(b);

        // Removes the intervals which intersect with R.cbegin().
        auto it = L.cbegin();

        while (it != L.cend() && (*it)->left <= b) {
            R.erase(*it); // Because it is a iterator of L, we need to delete it in R by value(*it).
            L.erase(it++);
        }
    }

    return S;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_POINTS_COVERING_INTERVALS_H
