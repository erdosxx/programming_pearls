#ifndef ALGORITHM_ANALYSIS_SERVICE_DEF_H
#define ALGORITHM_ANALYSIS_SERVICE_DEF_H

#include <vector>
#include <string>
#include <chrono>

using std::string;
using std::vector;
using std::chrono::milliseconds;
using std::this_thread::sleep_for;

class ServiceRequest {
public:
    ServiceRequest(const string &s) : request_(s) {}

    string ExtractWordToCheckFromRequest() { return request_; }

private:
    string request_;
};

class ServiceResponse {
public:
    const vector<string> &response() { return response_; }

    void EncodeIntoResponse(const vector<string> &s) { response_ = s; }

private:
    vector<string> response_;
};

vector<string> ClosestInDictionary(const string &w) {
    sleep_for(milliseconds(200));
    return {w + "_result"};
}

#endif //ALGORITHM_ANALYSIS_SERVICE_DEF_H
