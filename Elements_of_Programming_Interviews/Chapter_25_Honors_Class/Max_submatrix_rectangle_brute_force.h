#ifndef ALGORITHM_ANALYSIS_MAX_SUBMATRIX_RECTANGLE_BRUTE_FORCE_H
#define ALGORITHM_ANALYSIS_MAX_SUBMATRIX_RECTANGLE_BRUTE_FORCE_H

#include <deque>
#include <vector>

using std::deque;
using std::vector;

// O(m^3 n^3) time solution.
int MaxRectangleSubmatrixBruteForce(const vector<deque<bool>> &A) {
    int max = 0;
    for (int a = 0; a < A.size(); ++a) {
        for (int b = 0; b < A[a].size(); ++b) {
            for (int height = a; height < A.size(); ++height) {
                for (int width = b; width < A[height].size(); ++width) {
                    bool all_1 = true;
                    int count = 0;
                    for (int i = a; i <= height; ++i) {
                        for (int j = b; j <= width; ++j) {
                            if (A[i][j] == false) {
                                all_1 = false;
                                count = 0;
                                break;
                            } else {
                                ++count;
                            }
                        }
                        if (all_1 == false) {
                            break;
                        }
                    }
                    if (all_1 == true && count > max) {
                        max = count;
                    }
                }
            }
        }
    }
    return max;
}

#endif //ALGORITHM_ANALYSIS_MAX_SUBMATRIX_RECTANGLE_BRUTE_FORCE_H
