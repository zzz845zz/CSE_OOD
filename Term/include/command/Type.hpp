#ifndef TYPE_H
#define TYPE_H

#include <memory.h>
#include <string>
#include <vector>

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

struct CommandArgsITYPE {
    size_t i0;
    size_t i1;
    string s2_option;
    ~CommandArgsITYPE() {};
};
struct CommandArgsSTYPE {
    string s0;
    string s1_option;
    ~CommandArgsSTYPE() {};
};
union CommandArgs {
    CommandArgsITYPE args_itype;
    CommandArgsSTYPE args_stype;

    CommandArgs() { memset( this, 0, sizeof( CommandArgs )); };
    ~CommandArgs() {};
};
enum CommandArgsTYPE {
    I_TYPE,
    S_TYPE,
    N_TYPE,
};

namespace {
    bool is_itype_cargs(vector<Argument> args, size_t size) {
        // s2 can be both integer and string (both "543" and "hi" is ok)
        // e.g. i(1,10,543) will insert "543"
        //      i(1,10,hi)  will insert "hi" 
        if (size==2 || size ==3) {
            return args.at(0).type==INTEGER && args.at(1).type==INTEGER;
        } 
        return false;
    }

    bool is_stype_cargs(vector<Argument> args, size_t size) {
        // s0, s1 can be both integer and string (both "543" and "hi" is ok)
        // e.g. r(1,5) will replace "1" with "5"
        //      r(hi,3) will replaced "hi" with "3"
        return size==1 || size==2;
    }
}


#endif