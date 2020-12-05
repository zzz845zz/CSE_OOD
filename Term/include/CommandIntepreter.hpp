#ifndef COMMAND_INTEPRETER_H
#define COMMAND_INTEPRETER_H

#include <vector>
#include <memory.h>
#include <unordered_map>

#include <Util.hpp>
#include <Config.hpp>

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

    ///// custom
    CHANGE_VIEW,    // I-TYPE   e.g. v(20, 30): Change view property to width 20, height 30
    CHANGE_FILE,    // S-TYPE   e.g. f(test2.txt)
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
struct Command {
    char symbol;
    CommandType ctype;
    CommandArgsTYPE cargtype;
    CommandArgs* cargs;

    Command() {};
    Command(char _symbol, CommandType _ctype, CommandArgsTYPE _cargtype): symbol(_symbol), ctype(_ctype), cargtype(_cargtype)
    {
        cargs = new CommandArgs; 
    }

    ~Command() { 
        delete(cargs); 
    };
};
class CommandIntepreter {
    private:
        static CommandIntepreter* s_instance;
        unordered_map<char, Command*> cmd_map;

        vector<Argument> parseArguments(string input_args) {
            vector<Argument> args;
            size_t size = input_args.size();

            // No arguments
            if (size == 0) {
                return args;
            }

            //  It should be formatted like "(arg,arg,...)"
            if (size < 2 || input_args.front() != '(' || input_args.back() != ')') {
                throw invalid_argument("Invalid argument: " + input_args);
            }

            // (arg,arg,...) -> arg,arg,...
            input_args = input_args.substr(1, size-2);

            // Split and extract arguments
            size_t pos = 0;
            string token;
            do {
                pos = input_args.find(ARG_DELIMITER);
                token = input_args.substr(0, pos);   // "arg1" from "arg1,arg2,..."

                if (util::is_digit(token)) {
                    args.push_back(Argument{INTEGER, token});
                } else {
                    args.push_back(Argument{STRING, token});
                }
                input_args.erase(0, pos + 1);        // "arg1,arg2,..." -> "arg2,...""
            } while ( pos != string::npos);

            return args;
        }

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

        bool is_valid_cargs(CommandType ctype, vector<Argument> args) {
            size_t size = args.size();
            bool valid = false;
            switch(ctype)
            {
                case CommandType::INSERT:   // I-TYPE   e.g. i(1,10,hello)
                    return size==3 && is_itype_cargs(args, size) && args[2].value.size() <= BYTE_LIMIT_PER_LINE;
                case CommandType::DELETE:   // I-TYPE   e.g. d(2,10)
                    return size==2 && is_itype_cargs(args, size); 
                case CommandType::SEARCH:   // S-TYPE   e.g. s(hello)
                    return size==1 && is_stype_cargs(args, size); 
                case CommandType::REPLACE:   // S-TYPE   e.g. r(hello,bye)
                    return size==2 && is_stype_cargs(args, size); 
                case CommandType::TERMINATE:    // No args  e.g. t
                    return size==0; 
                case CommandType::NEXT_PAGE:    // No args  e.g. n
                    return size==0;
                case CommandType::PREVIOUS_PAGE:// No args  e.g. p
                    return size==0;
                case CommandType::UNDEFINED:
                    return false;
                case CommandType::CHANGE_VIEW:  // I-TYPE   e.g. v(20, 30): Change view property to width 20, height 30
                    return size==2 && is_itype_cargs(args, size); 
                case CommandType::CHANGE_FILE:
                    return size==1 && is_stype_cargs(args, size);
            }
        }

        // Fill dummy to option value
        void fill_dummy_to_option(vector<Argument>& args, CommandArgsTYPE cargtype) {
            size_t size = args.size();
            size_t aligned_size = 0;
            if (cargtype == I_TYPE) aligned_size = 3;
            else if(cargtype == S_TYPE) aligned_size = 2;
            else if(cargtype == N_TYPE) aligned_size = 0;

            for(size_t i=0; i<aligned_size; ++i) {
                Argument dummy = Argument { INTEGER, "0" };
                args.push_back(dummy);
            }
        }

        void fill_cargs(Command* info, vector<Argument> args) {

            if (!is_valid_cargs(info->ctype, args)) {
                throw invalid_argument("Arguments doesn't matched for its command type");
            }

            fill_dummy_to_option(args, info->cargtype);    
            switch(info->cargtype)
            {
                case I_TYPE:
                    info->cargs->args_itype.i0 = util::to_digit(args[0].value);
                    info->cargs->args_itype.i1 = util::to_digit(args[1].value);
                    info->cargs->args_itype.s2_option = args[2].value;
                    return;
                case S_TYPE:
                    info->cargs->args_stype.s0 = args[0].value;
                    info->cargs->args_stype.s1_option = args[1].value;
                    return;
                case N_TYPE:
                    return;
            };
        }

        Command* get_command_ptr(char symbol) {
            Command* ptr = cmd_map[symbol];
            if (ptr==nullptr)
                throw invalid_argument("There is no command with that symbol");
            return ptr;
        }

    public:
        CommandIntepreter() {
            // [cargs] in [Command] is empty at the first time.
            // It will be filled in `fill_cargs()` 
            cmd_map['i'] = new Command ('i', INSERT, I_TYPE);
            cmd_map['d'] = new Command ('d', DELETE, I_TYPE);
            cmd_map['s'] = new Command ('s', SEARCH, S_TYPE);
            cmd_map['r'] = new Command ('r', REPLACE, S_TYPE);
            cmd_map['t'] = new Command ('t', TERMINATE, N_TYPE);
            cmd_map['n'] = new Command ('n', NEXT_PAGE, N_TYPE);
            cmd_map['p'] = new Command ('p', PREVIOUS_PAGE, N_TYPE);
            cmd_map['v'] = new Command ('v', CHANGE_VIEW, I_TYPE);
            cmd_map['f'] = new Command ('f', CHANGE_FILE, S_TYPE);

            // To make new command x,
            // 1. Define command type   : at [CommandType]
            // 2. Define verification   : at [is_valid_cargs()]
            // 2. Add to command map    : to [cmd_map] with arguments type (e.g. I_TYPE)
            // 4. Define action         : at [execute_command()]
        }
        ~CommandIntepreter() {
            // Deallocate all [Command] allocated in constructor
            for(auto it = cmd_map.begin(); it!=cmd_map.end(); ++it) {
                delete(it->second);
            }
        }

        // Get single global instance
        static CommandIntepreter* instance() {
            if(!s_instance)
                s_instance = new CommandIntepreter;
            return s_instance;
        }
        
        // Invalid user input throws [invalid_argument]
        Command* interptret_input(string input);
};

#endif