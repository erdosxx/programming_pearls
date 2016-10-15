#ifndef ALGORITHM_ANALYSIS_TWO_THREAD_INCREMENT_H
#define ALGORITHM_ANALYSIS_TWO_THREAD_INCREMENT_H

#include <iostream>
#include <string>
#include <thread>

using std::cout;
using std::endl;
using std::thread;

// @include
static int counter = 0;

void IncrementThread(int N) {
    for (int i = 0; i < N; ++i) {
        ++counter;
    }
}

void TwoThreadIncrementDriver(int N) {
    thread T1(IncrementThread, N);
    thread T2(IncrementThread, N);
    T1.join();
    T2.join();

    cout << counter << endl;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_TWO_THREAD_INCREMENT_H
