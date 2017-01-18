#ifndef PROGRAMMING_PEARLS_BASIC_H
#define PROGRAMMING_PEARLS_BASIC_H

#include <string>
#include <map>
#include <iostream>
#include "gtest/gtest_prod.h"

using std::cout;
using std::endl;
using std::string;
using std::map;

#define CMD_NAME "cmd"

#define LOGIN_VAL "login"
#define BBSLIST_VAL "bbslist"
#define BBSREAD_VAL "bbsread"

class Request {
public:
    string GetValue (string name) {
        return nvList_[name];
    }

    void SetNameValue(string name, string value) {
        nvList_[name] = value;
    }

private:
    map<string, string> nvList_;
};

class RequestParser {
public:
    bool GetRequest(string input, Request& req) {
        string key, value, str;
        size_t start = 0, pos = 0;

        while (pos != string::npos) {
            pos = input.find("=", start);
            if (pos == string::npos) continue;

            key = input.substr(start, pos - start);
            start = pos +1;

            pos = input.find("&", start);

            if (pos == string::npos)
                value = input.substr(start, input.length() - start);
            else
                value = input.substr(start, pos - start);
            start = pos + 1;

            if (! key.empty()) {
                req.SetNameValue(DecodeString(key), DecodeString(value));
                key = "";
            }
        }
        return true;
    }

protected:
    string DecodeString(string s) {
        string output;
        int len = s.length();

        for(int i=0; i < len; i++) {
            if (s[i] == '+')
                output += ' ';
            else if (s[i] == '%') {
                const char* pStr = s.data() + i + 1;
                char ch = Hex2Digit(pStr);
                output += ch;
                i += 2;
            } else
                output += s[i];
        }
        return output;
    }

    FRIEND_TEST(Command_Fixture, hax2digit_test);
    unsigned Hex2Digit(const char* hex) {
        unsigned digit;
        digit = hex[0] >= 'A' ? (hex[0] - 'A') + 10 : hex[0] - '0';
        digit <<= 4;
        digit += hex[1] >= 'A' ? (hex[1] - 'A') + 10 : hex[1] - '0';

        return digit;
    }

private:
};

class UserManager {
public:
    bool CheckPasswd(Request& req) {
        cout << "Passwd OK" << endl;
        return true;
    }
};

class BBS {
public :
    void DisplayList(Request& req) {
        cout << "Display BBS List" << endl;
    }

    void DisplayItem(Request& req) {
        cout << "Display BBS Item" << endl;
    }
};

#endif //PROGRAMMING_PEARLS_BASIC_H
