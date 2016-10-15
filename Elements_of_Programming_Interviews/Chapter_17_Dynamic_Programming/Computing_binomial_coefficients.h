#ifndef ALGORITHM_ANALYSIS_COMPUTING_BINOMIAL_COEFFICIENTS_H
#define ALGORITHM_ANALYSIS_COMPUTING_BINOMIAL_COEFFICIENTS_H

#include <vector>

using std::min;
using std::vector;

int ComputeXChooseY(int, int, vector<vector<int>>&);

enum {undefiend = 0};

// @include
int ComputeBinomialCoefficient(int n, int k) {
    vector<vector<int>> x_choose_y(n + 1, vector<int>(k + 1, undefined));
    return ComputeXChooseY(n, k, x_choose_y);
}

int ComputeXChooseY(int x, int y, vector<vector<int>>& x_choose_y) {
    if (y == 0 || x == y) {
        return 1;
    }

    if (x_choose_y[x][y] == undefiend) {
        int without_y = ComputeXChooseY(x - 1, y, x_choose_y);
        int with_y = ComputeXChooseY(x - 1, y - 1, x_choose_y);
        x_choose_y[x][y] = without_y + with_y;
    }
    return x_choose_y[x][y];
}
// @exclude

int ComputeBinomialCoefficientsSpaceEfficient(int n, int k) {
    k = min(k, n - k);
    vector<int> table(k + 1, undefined);
    // C(i, j) = C(i - 1, j) + C(i - 1, j - 1).

    for (int i = 1; i <= n; ++i) {
        table[0] = 1;  // One way to select zero element.

        for (int j = min(i, k); j >= 1; --j) {
            table[j] = table[j] + table[j - 1];
        }
    }
    return table[k];
}

#endif //ALGORITHM_ANALYSIS_COMPUTING_BINOMIAL_COEFFICIENTS_H
