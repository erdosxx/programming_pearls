#ifndef ALGORITHM_ANALYSIS_LONGEST_CONTAINED_RANGE_H
#define ALGORITHM_ANALYSIS_LONGEST_CONTAINED_RANGE_H
// 13.10 Find the length of a longest contained interval

#include <algorithm>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <vector>

using std::max;
using std::unordered_map;
using std::unordered_set;
using std::vector;

namespace p_13_10 {
    int CheckAns(vector<int> A) {
        sort(A.begin(), A.end());
        int max_interval_size = 1;
        int pre = A[0], len = 1;
        for (size_t i = 1; i < A.size(); ++i) {
            if (A[i] == pre + 1) {
                ++len;
            } else if (A[i] != pre) {
                max_interval_size = max(max_interval_size, len);
                len = 1;
            }
            pre = A[i];
        }
        max_interval_size = max(max_interval_size, len);
        // cout << max_interval_size << endl;
        return max_interval_size;
    }

    int FindLongestContainedRange(const vector<int> &A) {
        if (A.empty()) {
            return 0;
        }

        unordered_set<int> t;  // records the unique appearance.
        // U[i] stores the upper range for i.
        // closed range [i,  U[i]],   {x: i <= x <= U[i]}
        unordered_map<int, int> U;
        // L[i] stores the lower range for i.
        // closed range [L[i],  i],   {x: L[i] <= x <= i}
        unordered_map<int, int> L;
        for (size_t i = 0; i < A.size(); ++i) {
            if (t.emplace(A[i]).second) { // if A[i] is new entry in the set
                U[A[i]] = L[A[i]] = A[i];
                // Merges with the interval starting on A[i] + 1.
                // U: |------------------------------->
                // U: |----->     |------------------->
                //     <------------------------------|  : L
                //     <-----|     <------------------|  : L
                //    [ A[i] ]  + [ A[i]+1            ]
                if (U.find(A[i] + 1) != U.cend()) {
                    //U[L[A[i]]] = U[A[i] + 1]; equivalent to the following.
                    U[A[i]] = U[A[i] + 1];
                    //L[U[A[i] + 1]] = L[A[i]]; equivalent to the following.
                    L[U[A[i] + 1]] = A[i];
                    U.erase(A[i] + 1);
                    L.erase(A[i]);
                    // in U we only keep smallest i that has U[i]
                    // That is, if U[1] = 3, U[2] =3 than U[1]= 3 is kept and delete U[2]=3
                    // in L we only keep largest i that has L[i]
                    // That is, if L[3] = 0, L[2] = 0 than L[3]= 0 is kept and delete L[2]=0
                }
                // Merges with the interval ending on A[i] - 1.
                // U: |------------------------------->
                // U: |------------------>     |------>
                //     <------------------------------|  : L
                //     <------------------|     <-----|  : L
                //    [           A[i] -1 ]  + [ A[i] ]
                if (L.find(A[i] - 1) != L.cend()) {
                    L[U[A[i]]] = L[A[i] - 1];
                    U[L[A[i] - 1]] = U[A[i]];
                    L.erase(A[i] - 1);
                    U.erase(A[i]);
                }
            }
        }

        /*
        auto m =
                max_element(U.cbegin(), U.cend(), [](const auto &a, const auto &b) {
                    return a.second - a.first < b.second - b.first;
                });
        return m->second - m->first + 1;
        above code is equivalent to the following code.
        */
        auto m =
                max_element(L.cbegin(), L.cend(), [](const auto &a, const auto &b) {
                    return a.first - a.second < b.first - b.second;
                });

        return m->first - m->second + 1;
    }

// @include
    int LongestContainedRange(const vector<int> &A) {
        // unprocessed_entries records the existence of each entry in A.
        unordered_set<int> unprocessed_entries(A.begin(), A.end());

        int max_interval_size = 0;
        while (!unprocessed_entries.empty()) {
            int a = *unprocessed_entries.begin();
            unprocessed_entries.erase(a);

            // Finds the lower bound of the largest range containing a.
            int lower_bound = a - 1;
            while (unprocessed_entries.count(lower_bound)) {
                unprocessed_entries.erase(lower_bound);
                --lower_bound;
            }

            // Finds the upper bound of the largest range containing a.
            int upper_bound = a + 1;
            while (unprocessed_entries.count(upper_bound)) {
                unprocessed_entries.erase(upper_bound);
                ++upper_bound;
            }

            max_interval_size = max(max_interval_size, upper_bound - lower_bound - 1);
        }
        return max_interval_size;
    }
// @exclude
}


#endif //ALGORITHM_ANALYSIS_LONGEST_CONTAINED_RANGE_H
