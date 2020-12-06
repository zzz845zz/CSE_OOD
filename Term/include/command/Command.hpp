#ifndef COMMAND_H
#define COMMAND_H

#include <command/Type.hpp>

class Command {
    public:
        char symbol;
        CommandType ctype;
        CommandArgsTYPE cargtype;
        CommandArgs* cargs;

        Command() {};
        virtual ~Command() { 
            delete(cargs); 
        };

        virtual bool check_args_available(vector<Argument> args) = 0;
};


class CommandInsert: public Command {
    public:
        CommandInsert() {
            symbol = 'i';
            ctype = INSERT;
            cargtype = I_TYPE;
            cargs = new CommandArgs;
        };

        virtual bool check_args_available(vector<Argument> args) override {
            size_t size = args.size();
            return size==3 && is_itype_cargs(args, size) && args[2].value.size() <= BYTE_LIMIT_PER_LINE;
        };
};

class CommandDelete: public Command {
    public:
        CommandDelete() {
            symbol = 'd';
            ctype = DELETE;
            cargtype = I_TYPE;
            cargs = new CommandArgs;
        };

        virtual bool check_args_available(vector<Argument> args) override {
            size_t size = args.size();
            return size==2 && is_itype_cargs(args, size);
        }
};

// e.g. s(hello)
class CommandSearch: public Command {
    public:
        CommandSearch() {
            symbol = 's';
            ctype = SEARCH;
            cargtype = S_TYPE;
            cargs = new CommandArgs;
        };

        virtual bool check_args_available(vector<Argument> args) override {
            size_t size = args.size();
            return size==1 && is_stype_cargs(args, size);
        }
};

// e.g. r(hello,bye)
class CommandReplace: public Command {
    public:
        CommandReplace() {
            symbol = 'r';
            ctype = REPLACE;
            cargtype = S_TYPE;
            cargs = new CommandArgs;
        };
        virtual bool check_args_available(vector<Argument> args) override {
            size_t size = args.size();
            return size==2 && is_stype_cargs(args, size); 
        }
};

// No argument
class CommandTerminate: public Command {
    public:
        CommandTerminate() {
            symbol = 't';
            ctype = TERMINATE;
            cargtype = N_TYPE;
            cargs = new CommandArgs;
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
            cargtype = N_TYPE;
            cargs = new CommandArgs;
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
            cargtype = N_TYPE;
            cargs = new CommandArgs;
        };

        virtual bool check_args_available(vector<Argument> args) override {
            size_t size = args.size();
            return size==0; 
        }
};

#endif



















// class Builder {
// public:
// 	virtual char buildSymbol() = 0;
// 	virtual CommandType buildCommandType() = 0;
// 	virtual CommandArgsTYPE buildCommandArgsTYPE() = 0;
// 	virtual CommandArgs buildCommandArgs() = 0;
// };
