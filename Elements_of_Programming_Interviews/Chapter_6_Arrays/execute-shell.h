#ifndef ALGORITHM_ANALYSIS_EXECUTE_SHELL_H
#define ALGORITHM_ANALYSIS_EXECUTE_SHELL_H

#include <cstdio>
#include <iostream>
#include <string>

using std::string;

string execute_shell(const string& cmd) {
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) {
        return "ERROR";
    }
    char buffer[128];
    string result;
    while (!feof(pipe)) {
        if (!fgets(buffer, 128, pipe)) {
            result += buffer;
        }
    }
    pclose(pipe);
    return result;
}

#endif //ALGORITHM_ANALYSIS_EXECUTE_SHELL_H
