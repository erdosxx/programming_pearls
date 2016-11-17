#ifndef ALGORITHM_ANALYSIS_CIRCULAR_QUEUE_H
#define ALGORITHM_ANALYSIS_CIRCULAR_QUEUE_H
// 9.8 Implement a circular queue

#include <algorithm>
#include <stdexcept>
#include <vector>

using std::exception;
using std::length_error;
using std::vector;

namespace circular_queue {
// @include
    class Queue {
    public:
        explicit Queue(size_t capacity) : entries_(capacity) { }

        // head: position to pop
        // tail: position to push
        void Enqueue(int x) {
            if (num_queue_elements == entries_.size()) {  // Needs to resize.
                // Makes the queue elements appear consecutively.
                rotate(entries_.begin(), entries_.begin() + head_, entries_.end());

                head_ = 0;
                tail_ = num_queue_elements;  // Resets head and tail.
                entries_.resize(entries_.size() * kScaleFactor);
            }

            entries_[tail_] = x;
            tail_ = (tail_ + 1) % entries_.size();
            ++num_queue_elements;
        }

        int Dequeue() {
            if (num_queue_elements == 0) {
                throw length_error("empty queue");
            }

            --num_queue_elements;
            int ret = entries_[head_];
            head_ = (head_ + 1) % entries_.size();
            return ret;
        }

        size_t size() const { return num_queue_elements; }

    private:
        const int kScaleFactor = 2;
        size_t head_ = 0;
        size_t tail_ = 0;
        size_t num_queue_elements = 0;
        vector<int> entries_;
    };
// @exclude
}

#endif //ALGORITHM_ANALYSIS_CIRCULAR_QUEUE_H
