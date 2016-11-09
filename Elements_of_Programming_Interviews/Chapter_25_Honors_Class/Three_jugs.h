#ifndef ALGORITHM_ANALYSIS_THREE_JUGS_H
#define ALGORITHM_ANALYSIS_THREE_JUGS_H
// 25.30 Measure with defective jugs

#include <unordered_set>
#include <utility>
#include <vector>

using std::hash;
using std::unordered_set;
using std::vector;

struct Jug {
    int low, high;
};

struct VolumeRange {
    int low, high;

    bool operator==(const VolumeRange& that) const {
        return low == that.low && high == that.high;
    }
};

struct HashVolumeRange {
    size_t operator()(const VolumeRange& p) const {
        return hash<int>()(p.low) ^ hash<int>()(p.high);
    }
};

bool CheckFeasibleHelper(const vector<Jug>&, int, int,
                         unordered_set<VolumeRange, HashVolumeRange>*);

// @include
bool CheckFeasible(const vector<Jug>& jugs, int L, int H) {
    unordered_set<VolumeRange, HashVolumeRange> cache;
    return CheckFeasibleHelper(jugs, L, H, &cache);
}

bool CheckFeasibleHelper(const vector<Jug>& jugs, int L, int H,
                         unordered_set<VolumeRange, HashVolumeRange>* c) {
    if (L > H || c->find({L, H}) != c->cend() || (L < 0 && H < 0)) {
        return false;
    }

    // Checks the volume for each jug to see if it is possible.
    for (const Jug& j : jugs) {
        if ((L <= j.low && j.high <= H) ||  // Base case: j is contained in [L, H]
            CheckFeasibleHelper(jugs, L - j.low, H - j.high, c)) {
            return true;
        }
    }
    c->emplace(VolumeRange{L, H});  // Marks this as impossible.
    return false;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_THREE_JUGS_H
