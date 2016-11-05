#ifndef ALGORITHM_ANALYSIS_QUEUES_BOOT_CAMP_H
#define ALGORITHM_ANALYSIS_QUEUES_BOOT_CAMP_H

#include <list>
#include <stdexcept>

using std::list;
using std::length_error;

class Queue {
public:
    void Enqueue(int x) {
        data_.emplace_back(x);
    }

    int Dequeue() {
        if (data_.empty()) {
            throw length_error("empty queue");
        }
        int val = data_.front();
        data_.pop_front();
        return val;
    }

    int Max() const {
        if(data_.empty()) {
            throw length_error("Cannot perform Max() on empty queue.");
        }
        return *max_element(data_.cbegin(), data_.cend());
    }

    int Front() const {
        if(data_.empty()) {
            throw length_error("Cannot perform Top() on empty queue.");
        }
        return data_.front();
    }

private:
    list<int> data_;
};

#endif //ALGORITHM_ANALYSIS_QUEUES_BOOT_CAMP_H
