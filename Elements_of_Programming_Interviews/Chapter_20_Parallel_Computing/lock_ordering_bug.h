#ifndef ALGORITHM_ANALYSIS_LOCK_ORDERING_BUG_H
#define ALGORITHM_ANALYSIS_LOCK_ORDERING_BUG_H

#include <chrono>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>

using std::ref;
using std::cout;
using std::endl;
using std::chrono::milliseconds;
using std::thread;
using std::this_thread::sleep_for;
using std::recursive_mutex;
using std::lock_guard;

namespace bug {
// @include
    class Account {
    public:
        Account(int balance) : balance_(balance), id_(++global_id_) {}

        int get_balance() { return balance_; }

        static void Transfer(Account &from, Account &to, int amount) {
            thread(&Account::Move, &from, ref(to), amount).detach();
        }

    private:
        bool Move(Account &to, int amount) {
            lock_guard<recursive_mutex> lock(mx_);
            {
                lock_guard<recursive_mutex> lock(to.mx_);
                if (amount > balance_) {
                    return false;
                }
                to.balance_ += amount;
                balance_ -= amount;
                cout << "returning true" << endl;
                return true;
            }
        }

        int balance_;
        int id_;
        recursive_mutex mx_;
        static int global_id_;
    };
// @exclude

    int Account::global_id_ = 0;
}

#endif //ALGORITHM_ANALYSIS_LOCK_ORDERING_BUG_H
