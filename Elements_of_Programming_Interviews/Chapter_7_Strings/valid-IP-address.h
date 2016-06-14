#ifndef ALGORITHM_ANALYSIS_VALID_IP_ADDRESS_H
#define ALGORITHM_ANALYSIS_VALID_IP_ADDRESS_H

#include <algorithm>
#include <string>
#include <vector>

using std::string;
using std::vector;

bool IsValidPart(const string& s);

// @include
vector<string> GetValidIPAddress(const string& s) {
  vector<string> result;

  for (size_t i = 1; i < 4 && i < s.size(); ++i) {
    auto first = s.substr(0, i); // string substr (size_t pos = 0, size_t len = npos) const;

    if (IsValidPart(first)) {
      for (size_t j = 1; i + j < s.size() && j < 4; ++j) {
        auto second = s.substr(i, j);

        if (IsValidPart(second)) {
          for (size_t k = 1; i + j + k < s.size() && k < 4; ++k) {
            auto third = s.substr(i + j, k);
            auto fourth = s.substr(i + j + k); // start at i+j+k to string::npos

            if (IsValidPart(third) && IsValidPart(fourth)) {
              result.emplace_back(first + "." + second + "." + third + "." +
                                  fourth);
            }
          }
        }
      }
    }
  }
  return result;
}

bool IsValidPart(const string& s) {
  if (s.size() > 3) {
    return false;
  }

  // "00", "000", "01", etc. are not valid, but "0" is valid.
  if (s.front() == '0' && s.size() > 1) {
    return false;
  }

  int val = stoi(s);
  return val <= 255 && val >= 0;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_VALID_IP_ADDRESS_H
