#ifndef ALGORITHM_ANALYSIS_THREAD_PER_TASK_WEBSERVER_H
#define ALGORITHM_ANALYSIS_THREAD_PER_TASK_WEBSERVER_H

#include <iostream>
#include <memory>
#include <thread>
#include <boost/asio.hpp>

using std::shared_ptr;
using std::cout;
using std::endl;
using std::thread;
using boost::system::error_code;
namespace asio = boost::asio;
using asio::ip::tcp;

void ProcessReq(shared_ptr<tcp::socket> sock) {
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

#endif //ALGORITHM_ANALYSIS_THREAD_PER_TASK_WEBSERVER_H
