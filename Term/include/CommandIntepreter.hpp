#ifndef COMMAND_INTEPRETER_H
#define COMMAND_INTEPRETER_H

#include <stdio.h>
#include <iostream>
#include <memory.h>

using namespace std;

const char ARG_DELIMITER = ','; 

// Argument
enum ArgumentType {
    INTEGER,
    STRING,
};
struct Argument {
    ArgumentType type;
    string value;
    ~Argument() {};
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

    ///// custom
    CHANGE_VIEW,    // I-TYPE   e.g. v(20, 30): Change view property to width 20, height 30
    CHANGE_FILE,    // S-TYPE   e.g. f(test2.txt)
};

struct CommandArgs_ITYPE {
    size_t i0;
    size_t i1;
    string s2_option;
    ~CommandArgs_ITYPE() {};
};
struct CommandArgs_STYPE {
    string s0;
    string s1_option;
    ~CommandArgs_STYPE() {};
};
union CommandArgs {
    CommandArgs_ITYPE args_itype;
    CommandArgs_STYPE args_stype;

    CommandArgs() { memset( this, 0, sizeof( CommandArgs )); };
    ~CommandArgs() {};
};

struct Command {
    CommandType ctype;
    CommandArgs* args;

    ~Command() { delete(args); };
};

// Interpret
namespace interpret {
    // Invalid user input throws `invalid_argument`
    Command interpretInput(string input);
}

#endif