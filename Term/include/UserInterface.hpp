#ifndef INTERFACE_H
#define INTERFACE_H

#include <Editor.hpp>

using namespace std;

namespace UI {
    void printInterface(Editor& e, string console_msg);

    inline string input() {
        string input;
        cin >> input;
        return input;
    }
};

#endif