#ifndef ALGORITHM_ANALYSIS_PASCAL_TRIANGLE_1_H
#define ALGORITHM_ANALYSIS_PASCAL_TRIANGLE_1_H

#include <algorithm>
#include <vector>

using std::vector;

// @include
vector<vector<int>> GeneratePascalTriangle(int num_rows) {
    vector<vector<int>> pascal_triangle;

    for (int i = 0; i < num_rows; ++i) {
        vector<int> curr_row;

        for (int j = 0; j <= i; ++j) {
            // Sets this entry to the sum of the two above adjacent entries if they
            // exist.
            curr_row.emplace_back((0 < j && j < i)
                                  ? pascal_triangle.back()[j - 1] +
                                    pascal_triangle.back()[j]
                                  : 1);
        }
        pascal_triangle.emplace_back(curr_row);
    }
    return pascal_triangle;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_PASCAL_TRIANGLE_1_H
