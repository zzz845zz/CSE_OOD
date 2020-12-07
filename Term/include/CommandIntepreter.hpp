#ifndef COMMAND_INTEPRETER_H
#define COMMAND_INTEPRETER_H

#include <vector>
#include <memory.h>
#include <unordered_map>

#include <Util.hpp>
#include <Config.hpp>
#include <command/Command.hpp>

using namespace std;

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

    public:
        CommandIntepreter();
        ~CommandIntepreter();

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