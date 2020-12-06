#include <CommandIntepreter.hpp>

using namespace std;

CommandIntepreter::CommandIntepreter() {
    // [cargs] in [Command] is empty at the first time.
    // It will be filled in `fill_cargs()` 
    vector<Command*> vec;
    vec.push_back(new CommandInsert());
    vec.push_back(new CommandDelete());
    vec.push_back(new CommandSearch());
    vec.push_back(new CommandReplace());
    vec.push_back(new CommandTerminate());
    vec.push_back(new CommandNextPage());
    vec.push_back(new CommandPreviousPage());

    for (auto it = vec.begin(); it!=vec.end(); ++it) {
        cmd_map[(*it)->symbol] = *it;
    }
}

CommandIntepreter::~CommandIntepreter() {
    // Deallocate all [Command] allocated in constructor
    for(auto it = cmd_map.begin(); it!=cmd_map.end(); ++it) {
        delete(it->second); // delete value
    }
}

Command* CommandIntepreter::interptret_input(string input) {
    Command* cmd = get_command_ptr(input.at(0));

    vector<Argument> args = parseArguments(input.substr(1, input.size()));
    fill_cargs(cmd, args);
    return cmd;
};

CommandIntepreter* CommandIntepreter::s_instance = 0;