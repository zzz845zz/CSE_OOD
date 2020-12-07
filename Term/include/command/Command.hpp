#ifndef COMMAND_H
#define COMMAND_H

#include <command/Type.hpp>

class Command {
    public:
        char symbol;
        CommandType ctype;
        vector<Argument> args;

        Command() {};
        virtual ~Command() {};

        virtual bool check_args_available(vector<Argument> args) = 0;
};


class CommandInsert: public Command {
    public:
        CommandInsert() {
            symbol = 'i';
            ctype = INSERT;
        };

        virtual bool check_args_available(vector<Argument> args) override {
            size_t size = args.size();
            return size==3 && args[0].type==INTEGER && args[1].type==INTEGER && args[2].size()<=BYTE_LIMIT_PER_LINE;
        };
};

class CommandDelete: public Command {
    public:
        CommandDelete() {
            symbol = 'd';
            ctype = DELETE;
        };

        virtual bool check_args_available(vector<Argument> args) override {
            size_t size = args.size();
            return size==2 && args[0].type==INTEGER && args[1].type==INTEGER;
        }
};

// e.g. s(hello)
class CommandSearch: public Command {
    public:
        CommandSearch() {
            symbol = 's';
            ctype = SEARCH;
        };

        virtual bool check_args_available(vector<Argument> args) override {
            size_t size = args.size();
            return size==1;
        }
};

// e.g. r(hello,bye)
class CommandReplace: public Command {
    public:
        CommandReplace() {
            symbol = 'r';
            ctype = REPLACE;
        };
        virtual bool check_args_available(vector<Argument> args) override {
            size_t size = args.size();
            return size==2; 
        }
};

// No argument
class CommandTerminate: public Command {
    public:
        CommandTerminate() {
            symbol = 't';
            ctype = TERMINATE;
        };

        virtual bool check_args_available(vector<Argument> args) override {
            size_t size = args.size();
            return size==0; 
        }
};

// No argument
class CommandNextPage: public Command {
    public:
        CommandNextPage() {
            symbol = 'n';
            ctype = NEXT_PAGE;
        };

        virtual bool check_args_available(vector<Argument> args) override {
            size_t size = args.size();
            return size==0; 
        }
};

// No argument
class CommandPreviousPage: public Command {
    public:
        CommandPreviousPage() {
            symbol = 'p';
            ctype = PREVIOUS_PAGE;
        };

        virtual bool check_args_available(vector<Argument> args) override {
            size_t size = args.size();
            return size==0; 
        }
};

#endif