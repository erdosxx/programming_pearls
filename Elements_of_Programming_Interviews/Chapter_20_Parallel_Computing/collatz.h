#ifndef ALGORITHM_ANALYSIS_COLLATZ_H
#define ALGORITHM_ANALYSIS_COLLATZ_H

#include <cassert>
#include <chrono>
#include <chrono>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_set>
#include <boost/thread.hpp>
#include <boost/thread/sync_bounded_queue.hpp>

using std::stoi;
using std::bind;
using std::ref;
using std::pair;
using std::make_pair;
using std::unordered_set;
using std::cout;
using std::endl;
using std::chrono::system_clock;
using std::chrono::milliseconds;
using std::chrono::duration_cast;
using boost::thread_group;
using boost::sync_bounded_queue;
using boost::queue_op_status;

//typedef unsigned long long CollatzInt;
using CollatzInt = unsigned long long;
//typedef sync_bounded_queue<pair<CollatzInt, CollatzInt>> QueueType1;
using QueueType1 = sync_bounded_queue<pair<CollatzInt, CollatzInt>>;
void Worker(CollatzInt lower, CollatzInt upper);
bool CollatzCheck(CollatzInt x, unordered_set<CollatzInt>& visited);

// @include
void ThreadFunc(QueueType1& q) {
    pair<CollatzInt, CollatzInt> args;
    while (q.wait_pull_front(args) == queue_op_status::success) {
        Worker(args.first, args.second);
    }
}

// Performs basic unit of work
void Worker(CollatzInt lower, CollatzInt upper) {
    unordered_set<CollatzInt> collset;
    for (CollatzInt i = lower; i <= upper; ++i) {
        //assert(CollatzCheck(i, unordered_set<CollatzInt>()));
        assert(CollatzCheck(i, collset));
    }
    cout << '(' << lower << ',' << upper << ')' << endl;
}

// Checks an individual number
bool CollatzCheck(CollatzInt x, unordered_set<CollatzInt>& visited) {
    if (x == 1) {
        return true;
    }
    if (!visited.emplace(x).second) {
        return false;
    }
    if (x & 1) {  // odd number
        return CollatzCheck(3 * x + 1, visited);
    } else {  // even number
        return CollatzCheck(x >> 1, visited);  // divide by 2
    }
}
// @exclude

// @include


    // @include
// @exclude

#endif //ALGORITHM_ANALYSIS_COLLATZ_H
