#ifndef ALGORITHM_ANALYSIS_UNIFORM_RANDOM_NUMBER_GENERATION_H
#define ALGORITHM_ANALYSIS_UNIFORM_RANDOM_NUMBER_GENERATION_H
// 5.10 Generate uniform random numbers

#include <random>

using std::default_random_engine;
using std::random_device;
using std::uniform_int_distribution;

int ZeroOneRandom() {
    random_device rd;
    default_random_engine gen(rd());
    //default_random_engine gen((random_device())());
    uniform_int_distribution<int> dis(0, 1);
    return dis(gen);
}

// @include
int UniformRandom(int lower_bound, int upper_bound) {
    int number_of_outcomes = upper_bound - lower_bound + 1;
    int result;

    do {
        result = 0;
        for (int i = 0; (1 << i) < number_of_outcomes; ++i) {
            // ZeroOneRandom() is the provided random number generator.
            result = (result << 1) | ZeroOneRandom();
        }
    } while (result >= number_of_outcomes);
    return result + lower_bound;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_UNIFORM_RANDOM_NUMBER_GENERATION_H
