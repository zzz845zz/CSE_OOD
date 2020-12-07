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
    Command* cmd = cmd_map[input.at(0)];
    if (cmd==nullptr)
        throw invalid_argument("There is no command with that symbol");

    vector<Argument> args = parseArguments(input.substr(1, input.size()));
    if (!cmd->check_args_available(args)) {
        throw invalid_argument("Arguments doesn't matched for its command type");
    }

    cmd->args = args;
    return cmd;
};

CommandIntepreter* CommandIntepreter::s_instance = 0;