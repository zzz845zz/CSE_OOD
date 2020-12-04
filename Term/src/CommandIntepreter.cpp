#include <CommandIntepreter.hpp>
#include <iostream>
#include <vector>
#include <Util.hpp>

using namespace std;

Command* CommandIntepreter::interptret_input(string input) {
    Command* cmd = get_command_ptr(input.at(0));

    vector<Argument> args = parseArguments(input.substr(1, input.size()));
    fill_cargs(cmd, args);
    return cmd;
};

CommandIntepreter* CommandIntepreter::s_instance = 0;