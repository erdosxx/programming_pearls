#ifndef ALGORITHM_ANALYSIS_SIMPLE_WEB_SERVER_H
#define ALGORITHM_ANALYSIS_SIMPLE_WEB_SERVER_H

#include <iostream>
#include <boost/asio.hpp>

using std::cout;
using std::endl;
using boost::system::error_code;
namespace asio = boost::asio;
using asio::ip::tcp;

void ProcessReq(tcp::socket& sock) {
    asio::streambuf sb;
    while (true) {
        error_code e;
        size_t n = asio::read_until(sock, sb, '\n', e);
        if (e == asio::error::eof) {
            cout << endl << "connection closed" << endl;
            break;
        }
        asio::write(sock, sb.data());
        cout << &sb;
    }
}

#endif //ALGORITHM_ANALYSIS_SIMPLE_WEB_SERVER_H
