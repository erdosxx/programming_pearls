#ifndef ALGORITHM_ANALYSIS_HEIGHT_DETERMINATION_H
#define ALGORITHM_ANALYSIS_HEIGHT_DETERMINATION_H

#include <vector>

using std::vector;

int GetHeightHelper(int, int, vector<vector<int>>*);

enum {unknown = -1};

// @include
int GetHeight(int cases, int drops) {
    vector<vector<int>> F(cases + 1, vector<int>(drops + 1, unknown));
    return GetHeightHelper(cases, drops, &F);
}

int GetHeightHelper(int cases, int drops, vector<vector<int>>* F) {
    if (cases == 0 || drops == 0) {
        return 0;
    } else if (cases == 1) {
        return drops;
    } else {
        if ((*F)[cases][drops] == unknown) {
            (*F)[cases][drops] = GetHeightHelper(cases, drops - 1, F) +
                                 GetHeightHelper(cases - 1, drops - 1, F) + 1;
        }
        return (*F)[cases][drops];
    }
}
// @exclude

#endif //ALGORITHM_ANALYSIS_HEIGHT_DETERMINATION_H
