#ifndef ALGORITHM_ANALYSIS_NUMBER_WAYS_H
#define ALGORITHM_ANALYSIS_NUMBER_WAYS_H

#include <vector>

using std::swap;
using std::vector;

int ComputeNumberOfWaysToXY(int, int, vector<vector<int>>&);

enum {undefined = 0};

// @include
int NumberOfWays(int n, int m) {
    vector<vector<int>> number_of_ways(n, vector<int>(m, undefined));
    return ComputeNumberOfWaysToXY(n - 1, m - 1, number_of_ways);
}

int ComputeNumberOfWaysToXY(int x, int y,
                            vector<vector<int>>& number_of_ways) {
    if (x == 0 && y == 0) {
        return 1;
    }

    if (number_of_ways[x][y] == undefined) {
        int ways_top =
                x == 0 ? 0 : ComputeNumberOfWaysToXY(x - 1, y, number_of_ways);
        int ways_left =
                y == 0 ? 0 : ComputeNumberOfWaysToXY(x, y - 1, number_of_ways);
        number_of_ways[x][y] = ways_top + ways_left;
    }
    return number_of_ways[x][y];
}
// @exclude

int ComputeNumberOfWaysSpaceEfficient(int n, int m) {
    if (n < m) {
        swap(n, m);
    }

    vector<int> A(m, 1);

    for (int i = 1; i < n; ++i) {
        int prev_res = 0;

        for (int j = 0; j < m; ++j) {
            A[j] = A[j] + prev_res;
            prev_res = A[j];
        }
    }
    return A[m - 1];
}

#endif //ALGORITHM_ANALYSIS_NUMBER_WAYS_H
