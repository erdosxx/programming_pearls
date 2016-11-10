#ifndef ALGORITHM_ANALYSIS_BIGNUMBER_MULTIPLICATION_H
#define ALGORITHM_ANALYSIS_BIGNUMBER_MULTIPLICATION_H
// 6.3 Multiply two arbitrary-precision integers

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include "execute-shell.h"

using std::cout;
using std::default_random_engine;
using std::endl;
using std::max;
using std::ostream_iterator;
using std::random_device;
using std::string;
using std::stringstream;
using std::uniform_int_distribution;
using std::vector;

namespace multiply {
// @include
    vector<int> Multiply(vector<int> num1, vector<int> num2) {
        int sign = num1.front() < 0 ^ num2.front() < 0 ? -1 : 1;
        num1.front() = abs(num1.front()), num2.front() = abs(num2.front());

        vector<int> result(num1.size() + num2.size(), 0);
        for (int i = num1.size() - 1; i >= 0; --i) {
            for (int j = num2.size() - 1; j >= 0; --j) {
                result[i + j + 1] += num1[i] * num2[j];
                result[i + j] += result[i + j + 1] / 10;
                result[i + j + 1] %= 10;
            }
        }

        // find first element that is not 0.
        result = vector < int > {find_if(begin(result), end(result), [](int a) {
            return a;
        }), end(result)};

        if (result.empty()) {
            return {0};
        }
        result.front() *= sign;
        return result;
    }
// @exclude

    vector<int> RandVector(int len) {
        if (!len) return {0};

        default_random_engine gen((random_device())());
        uniform_int_distribution<int> dis(1, 9);
        vector<int> ret;
        ret.emplace_back(dis(gen));
        --len;
        while (len--) {
            uniform_int_distribution<int> dis(0, 9);
            ret.emplace_back(dis(gen));
        }

        uniform_int_distribution<int> positive_or_negative(0, 1);
        if (positive_or_negative(gen)) {
            ret.front() *= -1;
        }
        return ret;
    }

    bool EqualVector(const vector<int> &A, const vector<int> &B) {
        // following equal is from C++14
        return equal(A.begin(), A.end(), B.begin(), B.end());
    }

    //TODO: analysis for following code
    string VectorToString(const vector<int> &A) {
        stringstream converter;
        copy(A.begin(), A.end(), ostream_iterator<int>(converter, ""));
        return converter.str();
    }
}

#endif //ALGORITHM_ANALYSIS_BIGNUMBER_MULTIPLICATION_H
