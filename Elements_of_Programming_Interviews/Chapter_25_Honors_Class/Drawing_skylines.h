#ifndef ALGORITHM_ANALYSIS_DRAWING_SKYLINES_H
#define ALGORITHM_ANALYSIS_DRAWING_SKYLINES_H

#include <algorithm>
#include <vector>

using std::vector;

struct Rectangle {
    int left, right, height;
};

using Skyline = vector<Rectangle>;

void MergeIntersectSkylines(Skyline*, Rectangle*, int*, Rectangle*, int*);
Skyline MergeSkylines(Skyline*, Skyline*);
Skyline ComputeSkylineInInterval(const vector<Rectangle>&, int, int);

// @include

Skyline ComputeSkyline(const vector<Rectangle>& buildings) {
    return ComputeSkylineInInterval(buildings, 0, buildings.size());
}

Skyline ComputeSkylineInInterval(const vector<Rectangle>& buildings,
                                 int left_endpoint, int right_endpoint) {
    if (right_endpoint - left_endpoint <= 1) {  // 0 or 1 skyline, just copy it.
        return {buildings.cbegin() + left_endpoint,
                buildings.cbegin() + right_endpoint};
    }

    int mid = left_endpoint + ((right_endpoint - left_endpoint) / 2);

    auto left_skyline = ComputeSkylineInInterval(buildings, left_endpoint, mid);
    auto right_skyline =
            ComputeSkylineInInterval(buildings, mid, right_endpoint);

    return MergeSkylines(&left_skyline, &right_skyline);
}

Skyline MergeSkylines(Skyline* left_skyline, Skyline* right_skyline) {
    int i = 0, j = 0;
    Skyline merged;

    while (i < left_skyline->size() && j < right_skyline->size()) {
        //    |left|   |right|
        if ((*left_skyline)[i].right < (*right_skyline)[j].left) {
            merged.emplace_back((*left_skyline)[i++]);
        } //  |right|  |left|
        else if ((*right_skyline)[j].right < (*left_skyline)[i].left) {
            merged.emplace_back((*right_skyline)[j++]);
        } //  |left   |right
        else if ((*left_skyline)[i].left <= (*right_skyline)[j].left) {
            MergeIntersectSkylines(&merged, &(*left_skyline)[i], &i,
                                   &(*right_skyline)[j], &j);
        } //  |right  |left
        else {  // left_skyline[i].left > right_skyline[j].left.
            MergeIntersectSkylines(&merged, &(*right_skyline)[j], &j,
                                   &(*left_skyline)[i], &i);
        }
    }

    merged.insert(merged.end(), left_skyline->begin() + i, left_skyline->end());
    merged.insert(merged.end(), right_skyline->begin() + j, right_skyline->end());
    return merged;
}

void MergeIntersectSkylines(Skyline* merged, Rectangle* a, int* a_idx,
                            Rectangle* b, int* b_idx) {
    //    |a  |b  a|  b|
    if (a->right <= b->right) {
        if (a->height > b->height) {
            if (b->right != a->right) {
                merged->emplace_back(*a);
                ++*a_idx;
                b->left = a->right;
            } else {
                ++*b_idx;
            }
        } else if (a->height == b->height) {
            b->left = a->left;
            ++*a_idx;
        } else {  // a->height < b->height.
            if (a->left != b->left) {
                merged->emplace_back(Rectangle{a->left, b->left, a->height});
            }
            ++*a_idx;
        }
    }  //  |a  |b  b|  a|
    else {  // a->right > b->right.
        if (a->height >= b->height) {
            ++*b_idx;
        } else {  // a->height < b->height
            if (a->left != b->left) {
                merged->emplace_back(Rectangle{a->left, b->left, a->height});
            }
            a->left = b->right;
            merged->emplace_back(*b);
            ++*b_idx;
        }
    }
}
// @exclude

#endif //ALGORITHM_ANALYSIS_DRAWING_SKYLINES_H
