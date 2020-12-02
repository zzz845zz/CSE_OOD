#ifndef UTIL_H
#define UTIL_H

#include <iostream>

namespace util {
    bool isDigit(std::string str) {
        // atoi() returns
        //                  0           if str is not integer
        //                  its value   if str is integer
        // compare() for the case when str is "0"
        return atoi(str.c_str()) != 0 || str.compare("0") == 0;
    }

    int toDigit(std::string str) {
        return atoi(str.c_str());
    }
}

#endif