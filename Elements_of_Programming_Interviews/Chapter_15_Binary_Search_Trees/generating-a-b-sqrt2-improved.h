#ifndef ALGORITHM_ANALYSIS_GENERATING_A_B_SQRT2_IMPROVED_H
#define ALGORITHM_ANALYSIS_GENERATING_A_B_SQRT2_IMPROVED_H
// 15.7 Enumerate numbers of the form a + b sqrt(2)

#include <functional>
#include <set>
#include <vector>

using std::min;
using std::set;
using std::vector;

namespace improved {
// @include
    struct ABSqrt2 {
        ABSqrt2(int a, int b) : a(a), b(b), val(a + b * sqrt(2)) { }

        bool operator<(const ABSqrt2 &that) const { return val < that.val; }
        bool operator==(const ABSqrt2 &that) const { return val == that.val; }

        int a, b;
        double val;
    };

    vector<ABSqrt2> GenerateFirstKABSqrt2(int k) {
        // Will store the first k numbers of the form a + b sqrt(2).
        vector<ABSqrt2> result;
        result.emplace_back(0, 0);

        int i = 0, j = 0;
        for (int n = 1; n < k; ++n) {
            ABSqrt2 result_i_plus_1(result[i].a + 1, result[i].b);
            ABSqrt2 result_j_plus_sqrt2(result[j].a, result[j].b + 1);

            result.emplace_back(min(result_i_plus_1, result_j_plus_sqrt2));
            if (result_i_plus_1.val == result.back().val) {
                ++i;
            }

            if (result_j_plus_sqrt2.val == result.back().val) {
                ++j;
            }
        }
        return result;
    }
// @exclude

    vector<ABSqrt2> Golden(int k) {
        // std::set
        // Internally, the elements in a set are always sorted following
        // a specific strict weak ordering criterion indicated by its
        // internal comparison object (of type Compare).
        set<ABSqrt2> candidates;
        // Initial for 0 + 0 * sqrt(2).
        candidates.emplace(0, 0);

        vector<ABSqrt2> result;
        while (result.size() < k) {
            auto next_smallest = candidates.cbegin();
            result.emplace_back(*next_smallest);

            // Adds the next two numbers derived from next_smallest.
            candidates.emplace(next_smallest->a + 1, next_smallest->b);
            candidates.emplace(next_smallest->a, next_smallest->b + 1);
            candidates.erase(next_smallest);
        }
        return result;
    }
}

#endif //ALGORITHM_ANALYSIS_GENERATING_A_B_SQRT2_IMPROVED_H
