#ifndef TYPE_H
#define TYPE_H

#include <memory.h>
#include <string>
#include <vector>
#include <Util.hpp>

using namespace std;

// Argument
enum ArgumentType {
    INTEGER,
    STRING,
};
struct Argument {
    ArgumentType type;
    string value;
    ~Argument() {};

    size_t size() {
        return value.size();
    }

    operator string() const {
        return value;
    }

    operator int() {
        return util::to_digit(value);
    }
};

// Command
enum CommandType {
    INSERT,         // I-TYPE   e.g. i(1,10,hello)
    DELETE,         // I-TYPE   e.g. d(2,10)
    SEARCH,         // S-TYPE   e.g. s(hello)
    REPLACE,        // S-TYPE   e.g. r(hello,bye)
    TERMINATE,      // No args  e.g. t
    NEXT_PAGE,      // No args  e.g. n
    PREVIOUS_PAGE,  // No args  e.g. p
    UNDEFINED,      // ..
};

#endif