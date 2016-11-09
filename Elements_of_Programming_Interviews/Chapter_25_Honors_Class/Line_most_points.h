#ifndef ALGORITHM_ANALYSIS_LINE_MOST_POINTS_H
#define ALGORITHM_ANALYSIS_LINE_MOST_POINTS_H
// 25.19 Find the line through the most points

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "GCD2.h"

using std::hash;
using std::max;
using std::unordered_map;
using std::unordered_set;
using std::vector;
using GCD2::GCD;

// @include
struct Point {
    // Equal function for hash.
    bool operator==(const Point& that) const {
        return x == that.x && y == that.y;
    }

    int x, y;
};

// Hash function for Point.
struct HashPoint {
    size_t operator()(const Point& p) const {
        return hash<int>()(p.x) ^ hash<int>()(p.y);
    }
};

struct Rational {
    bool operator==(const Rational& that) const {
        return numerator == that.numerator && denominator == that.denominator;
    }

    int numerator, denominator;
};

Rational GetCanonicalForm(int a, int b) {
    int gcd = GCD(abs(a), abs(b));
    a /= gcd, b /= gcd;
    return b < 0 ? Rational{-a, -b} : Rational{a, b};
}

// Line function of two points, a and b, and the equation is
// y = x(b.y - a.y) / (b.x - a.x) + (b.x * a.y - a.x * b.y) / (b.x - a.x).
struct Line {
    Line(const Point& a, const Point& b) {
        slope =
                a.x != b.x ? GetCanonicalForm(b.y - a.y, b.x - a.x) : Rational{1, 0};
        intercept = a.x != b.x
                    ? GetCanonicalForm(b.x * a.y - a.x * b.y, b.x - a.x)
                    : Rational{a.x, 1};
    }

    // Equal function for Line.
    bool operator==(const Line& that) const {
        return slope == that.slope && intercept == that.intercept;
    }

    // slope is a rational number. Note that if the line is parallel to y-axis
    // that we store 1/0.
    Rational slope;
    // intercept is a rational number for the y-intercept unless
    // the line is parallel to y-axis in which case it is the x-intercept.
    Rational intercept;
};

// Hash function for Line.
struct HashLine {
    size_t operator()(const Line& l) const {
        return hash<int>()(l.slope.numerator) ^ hash<int>()(l.slope.denominator) ^
               hash<int>()(l.intercept.numerator) ^
               hash<int>()(l.intercept.denominator);
    }
};
// @exclude

// @include

size_t FindLineWithMostPoints(const vector<Point>& P) {
    // Add all possible lines into hash table.
    unordered_map<Line, unordered_set<Point, HashPoint>, HashLine> table;

    for (int i = 0; i < P.size(); ++i) {
        for (int j = i + 1; j < P.size(); ++j) {
            Line l(P[i], P[j]);
            table[l].emplace(P[i]), table[l].emplace(P[j]);
        }
    }

    // @include
    // Return the line with most points have passed.
    return max_element(table.cbegin(), table.cend(),
                       [](const auto& a, const auto& b) {
                           return a.second.size() < b.second.size();
                       })
            ->second.size();
}
// @exclude


#endif //ALGORITHM_ANALYSIS_LINE_MOST_POINTS_H
