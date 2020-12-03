#include <CommandIntepreter.hpp>
#include <iostream>
#include <vector>
#include <Util.hpp>

using namespace std;

namespace interpret {

    // Private function
    namespace {
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

                if (util::isDigit(token)) {
                    args.push_back(Argument{INTEGER, token});
                } else {
                    args.push_back(Argument{STRING, token});
                }
                input_args.erase(0, pos + 1);        // "arg1,arg2,..." -> "arg2,...""
            } while ( pos != string::npos);

            return args;
        }

        bool isItypeCargs(vector<Argument> args, size_t size) {
            // s2 can be both integer and string (both "543" and "hi" is ok)
            // e.g. i(1,10,543) will insert "543"
            //      i(1,10,hi)  will insert "hi" 
            if (size==2 || size ==3) {
                return args.at(0).type==INTEGER && args.at(1).type==INTEGER;
            } 
            return false;
        }

        bool isStypeCargs(vector<Argument> args, size_t size) {
            // s0, s1 can be both integer and string (both "543" and "hi" is ok)
            // e.g. r(1,5) will replace "1" with "5"
            //      r(hi,3) will replaced "hi" with "3"
            return size==1 || size==2;
        }

        bool isValidCargs(CommandType ctype, vector<Argument> args) {
            size_t size = args.size();
            bool valid = false;
            switch(ctype)
            {
                case CommandType::INSERT:   // I-TYPE   e.g. i(1,10,hello)
                    return size==3 && isItypeCargs(args, size);
                case CommandType::DELETE:   // I-TYPE   e.g. d(2,10)
                    return size==2 && isItypeCargs(args, size); 
                case CommandType::SEARCH:   // S-TYPE   e.g. s(hello)
                    return size==1 && isStypeCargs(args, size); 
                case CommandType::REPLACE:   // S-TYPE   e.g. r(hello,bye)
                    return size==2 && isStypeCargs(args, size); 
                case CommandType::TERMINATE:    // No args  e.g. t
                    return size==0; 
                case CommandType::NEXT_PAGE:    // No args  e.g. n
                    return size==0;
                case CommandType::PREVIOUS_PAGE:// No args  e.g. p
                    return size==0;
                case CommandType::UNDEFINED:
                    return false;
                case CommandType::CHANGE_VIEW:  // I-TYPE   e.g. v(20, 30): Change view property to width 20, height 30
                    return size==2 && isItypeCargs(args, size); 
                case CommandType::CHANGE_FILE:
                    return size==1 && isStypeCargs(args, size);
            }
        }

        union CommandArgs* extractCargs(CommandType ctype, vector<Argument> args) {

            if (!isValidCargs(ctype, args)) {
                throw invalid_argument("Arguments doesn't matched for its command type");
            }

            // union CommandArgs cargs = { 0 };
            union CommandArgs* cargs = new CommandArgs;

            switch(ctype)
            {
                case CommandType::INSERT:       // I-TYPE   e.g. i(1,10,hello)
                    // struct CommandArgs_ITYPE *a = new CommandArgs_ITYPE;
                    cargs->args_itype.s2_option = args[2].value;
                case CommandType::DELETE:       // I-TYPE   e.g. d(2,10)
                case CommandType::CHANGE_VIEW:  // I-TYPE   e.g. v(20, 30): Change view property to width 20, height 30
                    cargs->args_itype.i0 = util::toDigit(args[0].value);
                    cargs->args_itype.i1 = util::toDigit(args[1].value);
                    return cargs;
                case CommandType::REPLACE:      // S-TYPE   e.g. r(hello,bye)
                    cargs->args_stype.s1_option = args[1].value;
                case CommandType::SEARCH:       // S-TYPE   e.g. s(hello)
                case CommandType::CHANGE_FILE:
                    cargs->args_stype.s0 = args[0].value;
                    return cargs;
                default:
                    return cargs;
            }
        }

        CommandType extractCommand(char command) {
            switch(command) 
            {
                case 'i': // INSERT
                    return CommandType::INSERT;
                case 'd': // DELETE
                    return CommandType::DELETE;
                case 's': // SEARCH
                    return CommandType::SEARCH;
                case 'r': // REPLACE
                    return CommandType::REPLACE;
                case 't': // TERMINATE
                    return CommandType::TERMINATE;
                case 'n': // NEXT_PAGE
                    return CommandType::NEXT_PAGE;
                case 'p': // PREVIOUS_PAGE
                    return CommandType::PREVIOUS_PAGE;
                case 'v':
                    return CommandType::CHANGE_VIEW;
                case 'f':
                    return CommandType::CHANGE_FILE;
                default:
                    throw invalid_argument("Invalid command type");
            }
        } 
    }

    Command interpretInput(string input) {
        // TODO: fix error that occurs when input is single character
        CommandType ctype = extractCommand(input.at(0));
        vector<Argument> args = parseArguments(input.substr(1, input.size()));
        CommandArgs* cargs = extractCargs(ctype, args);

        Command cmd = {ctype, cargs};
        return cmd;
    }
}
