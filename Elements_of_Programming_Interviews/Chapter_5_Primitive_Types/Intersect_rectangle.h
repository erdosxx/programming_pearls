#ifndef ALGORITHM_ANALYSIS_INTERSECT_RECTANGLE_H
#define ALGORITHM_ANALYSIS_INTERSECT_RECTANGLE_H
// 5.11 Rectangle intersection

#include <algorithm>
#include <iostream>
#include <random>
#include <string>

using std::cout;
using std::endl;
using std::max;
using std::min;
using std::string;

struct Rectangle;
bool IsIntersect(const Rectangle&, const Rectangle&);

// @include
struct Rectangle {
    int x, y, width, height;
    // @exclude
    void print(string s) const {
        cout << s << this->x << ' ' << this->y << ' ' << this->width << ' '
        << this->height << endl;
    }
    // @include
};

Rectangle IntersectRectangle(const Rectangle& R1, const Rectangle& R2) {
    if (IsIntersect(R1, R2)) {
        return {max(R1.x, R2.x), max(R1.y, R2.y),
                min(R1.x + R1.width, R2.x + R2.width) - max(R1.x, R2.x),
                min(R1.y + R1.height, R2.y + R2.height) - max(R1.y, R2.y)};
    }
    return {0, 0, -1, -1};  // No intersection.
}

bool IsIntersect(const Rectangle& R1, const Rectangle& R2) {
    return R1.x <= R2.x + R2.width && R1.x + R1.width >= R2.x &&
           R1.y <= R2.y + R2.height && R1.y + R1.height >= R2.y;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_INTERSECT_RECTANGLE_H
