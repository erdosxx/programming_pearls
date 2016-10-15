#ifndef ALGORITHM_ANALYSIS_S1_H
#define ALGORITHM_ANALYSIS_S1_H

#include <chrono>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <string>
#include <utility>
#include <vector>
#include <thread>
#include "service_def.h"

using std::move;
using std::string;
using std::to_string;
using std::vector;
using std::cout;
using std::endl;
using std::setprecision;
using std::chrono::system_clock;
using std::chrono::milliseconds;
using std::chrono::duration;
using std::chrono::duration_cast;
using std::mutex;
using std::lock_guard;
using std::unique_lock;
using std::this_thread::sleep_for;

namespace s1 {
// @include
    class SpellCheckService {
    public:
        static void Service(ServiceRequest &req, ServiceResponse &resp) {
            string w = req.ExtractWordToCheckFromRequest();

            if (w != w_last_) {
                w_last_ = move(w);
                closest_to_last_word_ = ClosestInDictionary(w_last_);
            }
            resp.EncodeIntoResponse(closest_to_last_word_);
        }

    private:
        static string w_last_;
        static vector<string> closest_to_last_word_;
    };
// @exclude

    string SpellCheckService::w_last_;
    vector<string> SpellCheckService::closest_to_last_word_;

    void ServiceThread(const string &data) {
        static mutex mx;
        auto start_time = system_clock::now();

        ServiceRequest req(data);
        ServiceResponse resp;

        lock_guard<mutex> lock(mx);

        SpellCheckService::Service(req, resp);

        duration<float> running_time = system_clock::now() - start_time;

        cout << data << " -> " << resp.response()[0] << " (" << setprecision(3)
             << running_time.count() << " sec)" << endl;
    }
}

#endif //ALGORITHM_ANALYSIS_S1_H
