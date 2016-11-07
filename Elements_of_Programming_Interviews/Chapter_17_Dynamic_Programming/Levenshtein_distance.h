#ifndef ALGORITHM_ANALYSIS_LEVENSHTEIN_DISTANCE_H
#define ALGORITHM_ANALYSIS_LEVENSHTEIN_DISTANCE_H
// 17.2 Compute the Levenshtein distance

#include <algorithm>
#include <numeric>
#include <string>
#include <vector>

using std::min;
using std::string;
using std::vector;

int ComputeDistanceBetweenPrefixes(const string&, int, const string&, int,
                                   vector<vector<int>>&);

// @include
int LevenshteinDistance(const string& A, const string& B) {
    vector<vector<int>> distance_between_prefixes(A.size(),
                                                  vector<int>(B.size(), -1));
    return ComputeDistanceBetweenPrefixes(A, A.size() - 1, B, B.size() - 1,
                                          distance_between_prefixes);
}

int ComputeDistanceBetweenPrefixes(
        const string& A, int A_idx, const string& B, int B_idx,
        vector<vector<int>>& distance_between_prefixes) {

    if (A_idx < 0) {
        // A is empty so add all of B's characters.
        return B_idx + 1;
    } else if (B_idx < 0) {
        // B is empty so delete all of A's characters.
        return A_idx + 1;
    }

    if (distance_between_prefixes[A_idx][B_idx] == -1) {
        if (A[A_idx] == B[B_idx]) {
            distance_between_prefixes[A_idx][B_idx] =
                    ComputeDistanceBetweenPrefixes(A, A_idx - 1, B, B_idx - 1,
                                                   distance_between_prefixes);
        } else {
            int substitute_last = ComputeDistanceBetweenPrefixes(
                    A, A_idx - 1, B, B_idx - 1, distance_between_prefixes);
            int add_last = ComputeDistanceBetweenPrefixes(
                    A, A_idx - 1, B, B_idx, distance_between_prefixes);
            int delete_last = ComputeDistanceBetweenPrefixes(
                    A, A_idx, B, B_idx - 1, distance_between_prefixes);
            distance_between_prefixes[A_idx][B_idx] =
                    1 + min({substitute_last, add_last, delete_last});
        }
    }
    return distance_between_prefixes[A_idx][B_idx];
}
// @exclude

#endif //ALGORITHM_ANALYSIS_LEVENSHTEIN_DISTANCE_H
