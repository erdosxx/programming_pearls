#ifndef ALGORITHM_ANALYSIS_TASK_EXECUTION_WEB_SERVER_H
#define ALGORITHM_ANALYSIS_TASK_EXECUTION_WEB_SERVER_H

#include <functional>
#include <iostream>
#include <memory>
#include <thread>
#include <utility>
#include <boost/asio.hpp>
#include <boost/thread/sync_bounded_queue.hpp>

using std::move;
using std::unique_ptr;
using std::ref;
using std::cout;
using std::endl;
using std::thread;
using boost::system::error_code;
using boost::sync_bounded_queue;
namespace asio = boost::asio;
using asio::ip::tcp;

typedef sync_bounded_queue<unique_ptr<tcp::socket>> QueueType;

void ProcessReq(unique_ptr<tcp::socket>& sock) {
    asio::streambuf sb;
    while (true) {
        error_code e;
        size_t n = asio::read_until(*sock, sb, '\n', e);
        if (e == asio::error::eof) {
            cout << endl << "connection closed" << endl;
            break;
        }
        asio::write(*sock, sb.data());
        cout << &sb;
    }
}

// @include
void ThreadFunc(QueueType& q) {
    while (true) {
        unique_ptr<tcp::socket> sock;
        q >> sock;
        ProcessReq(sock);
    }
}

#endif //ALGORITHM_ANALYSIS_TASK_EXECUTION_WEB_SERVER_H
