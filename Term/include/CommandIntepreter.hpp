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
            if (!info->check_args_available(args)) {
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