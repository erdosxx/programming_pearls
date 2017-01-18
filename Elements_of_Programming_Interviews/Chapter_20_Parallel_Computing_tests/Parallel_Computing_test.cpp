#include <gtest/gtest.h>
#include <random>
#include <limits>
#include <functional>
#include <unordered_set>
#include <cmath>
#include <string>
#include <deque>
#include <thread>
#include "s1.h"
#include "s2.h"
#include "two_thread_increment.h"
#include "odd_even.h"
#include "simple_web_server.h"
#include "task_execution_web_server.h"
#include "thread_per_task_webserver.h"
#include "lock_ordering_bug.h"
#include "lock_ordering_works.h"
#include "collatz.h"
#include "object_closure.h"

using std::istringstream;
using std::stringstream;
using std::default_random_engine;
using std::random_device;
using std::unique_ptr;
using std::numeric_limits;
using std::uniform_int_distribution;
using std::uniform_real_distribution;
using std::is_sorted;
using std::unordered_set;
using std::max;
using std::min;
using std::cout;
using std::endl;
using std::ostream_iterator;
using std::to_string;
using std::boolalpha;
using std::deque;
using std::string;
using std::thread;
using std::this_thread::sleep_for;
using std::bind;

class Ch20_Parallel_Computing_Fixture : public ::testing::Test {
private:

protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

public:
    Ch20_Parallel_Computing_Fixture() : Test() {

    }

    virtual ~Ch20_Parallel_Computing_Fixture() {
    }
};

TEST_F(Ch20_Parallel_Computing_Fixture, thread_1_Function) {
    int i = 0;
    while (i < 10) {
        thread(s1::ServiceThread, "req:" + to_string(i + 1)).detach();
        if (i > 0) {
            // while req:i+1 is computed we could return req:i from the cache
            thread(s1::ServiceThread, "req:" + to_string(i)).detach();
        }
        sleep_for(milliseconds(500));
        ++i;
    }
}

TEST_F(Ch20_Parallel_Computing_Fixture, thread_2_Function) {
    int i = 0;
    while (i < 10) {
        thread(s2::ServiceThread, "req:" + to_string(i + 1)).detach();
        if (i > 0) {
            // while req:i+1 is computed we could return req:i from the cache
            thread(s2::ServiceThread, "req:" + to_string(i)).detach();
        }
        sleep_for(milliseconds(500));
        ++i;
    }
}

TEST_F(Ch20_Parallel_Computing_Fixture, two_thread_inc_Function) {
    int N = 10000000;
    TwoThreadIncrementDriver(N);
}

TEST_F(Ch20_Parallel_Computing_Fixture, odd_even_Function) {
    OddEvenMonitor monitor;
    thread t1(OddThread, ref(monitor));
    thread t2(EvenThread, ref(monitor));
    t1.join();
    t2.join();
}

TEST_F(Ch20_Parallel_Computing_Fixture, simple_web_server_Function) {
    const unsigned short SERVERPORT = 8080;

    asio::io_service io_service;
    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), SERVERPORT));
    // TODO:: bug fix
    // no matching constructor for initialization of 'std::__1::thread'
    // thread(ProcessReq, sock).detach();
    while (true) {
        tcp::socket sock(io_service);
        acceptor.accept(sock);
        ProcessReq(sock);
    }
}

/* TODO: Need to fix for compile.
TEST_F(Ch20_Parallel_Computing_Fixture, thread_per_task_webserver_Function) {
    const unsigned short SERVERPORT = 8080;

    asio::io_service io_service;
    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), SERVERPORT));
    // TODO:: bug fix
    // no matching constructor for initialization of 'std::__1::thread'
    // thread(ProcessReq, sock).detach();
    while (true) {
        shared_ptr <tcp::socket> sock(new tcp::socket(io_service));
        acceptor.accept(*sock);
        thread(ProcessReq, sock).detach();
    }
}
 */

/* TODO: Need to fix for compiling.
TEST_F(Ch20_Parallel_Computing_Fixture, task_execution_web_server_Function) {
    const unsigned short kServerPort = 8080;
    const int kNThreads = 2;

    QueueType1 q(kNThreads);
    for (int i = 0; i < kNThreads; ++i) {
        thread(ThreadFunc, ref(q)).detach();
    }
    asio::io_service io_service;
    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), kServerPort));
    while (true) {
        unique_ptr<tcp::socket> sock(new tcp::socket(io_service));
        acceptor.accept(*sock);
        q << move(sock);
    }
}
 */

TEST_F(Ch20_Parallel_Computing_Fixture, lock_ordering_bug_Function) {
    bug::Account from(200);
    bug::Account to(100);
    cout << "Initial balances = " << from.get_balance() << ' '
         << to.get_balance() << endl;
    bug::Account::Transfer(from, to, 50);
    sleep_for(milliseconds(100));
    cout << "New balances = " << from.get_balance() << ' ' << to.get_balance()
         << endl;
}

TEST_F(Ch20_Parallel_Computing_Fixture, lock_ordering_works_Function) {
    Account from(200);
    Account to(100);
    cout << "Initial balances = " << from.get_balance() << ' '
         << to.get_balance() << endl;
    Account::Transfer(from, to, 50);
    sleep_for(milliseconds(100));
    cout << "New balances = " << from.get_balance() << ' ' << to.get_balance()
         << endl;
    Account::Transfer(from, from, 50);
    sleep_for(milliseconds(100));
    cout << "New balances = " << from.get_balance() << ' ' << to.get_balance()
         << endl;
}

/* TODO: need to fix for compiling
TEST_F(Ch20_Parallel_Computing_Fixture, Collatz_Function) {
    CollatzInt N = 10000000;
    CollatzInt RANGESIZE = 1000000;
    int NTHREADS = 4;
    // @exclude

    ASSERT_TRUE(CollatzCheck(1, unordered_set<CollatzInt>()));
    ASSERT_TRUE(CollatzCheck(3, unordered_set<CollatzInt>()));
    ASSERT_TRUE(CollatzCheck(8, unordered_set<CollatzInt>()));
    auto start_time = system_clock::now();

    // @include
    // Uses synchronized bounded queue for task assignment and load balancing
    QueueType1 q(NTHREADS);
    thread_group threads;
    for (int i = 0; i < NTHREADS; ++i) {
        // for bind exmaple, see Programming Language Pragmatics P.514
        threads.create_thread(bind(ThreadFunc, ref(q)));
    }
    for (CollatzInt i = 0; i < N / RANGESIZE; ++i) {
        q << make_pair(i * RANGESIZE + 1, (i + 1) * RANGESIZE);
    }
    q.close();
    threads.join_all();

    // @exclude
    cout << "Finished all threads" << endl;
    auto running_time =
            duration_cast<milliseconds>(system_clock::now() - start_time).count();
    cout << "time in milliseconds for checking to " << N << " is "
         << running_time << '(' << N / running_time << " per ms)";
}
 */


