#ifndef UTIL_H
#define UTIL_H

#include <iostream>

namespace util {
    namespace {
        bool is_digit(std::string str) {
            // atoi() returns
            //                  0           if str is not integer
            //                  its value   if str is integer
            // compare() for the case when str is "0"
            return atoi(str.c_str()) != 0 || str.compare("0") == 0;
        }

        int to_digit(std::string str) {
            return atoi(str.c_str());
        }

        std::string replace_all(std::string str, const std::string& from, const std::string& to) {
            size_t start_pos = 0;
            while((start_pos = str.find(from, start_pos)) != std::string::npos) {
                str.replace(start_pos, from.length(), to);
                start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
            }
            return str;
        }
    }
}

#endif