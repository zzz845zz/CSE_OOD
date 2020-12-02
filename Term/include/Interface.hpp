#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>
#include <iostream>

using namespace std;

enum Command {
    INSERT,
    DELETE,
    SEARCH,
    CHANGE,
    TERMINATE,
    NEXT_PAGE,
    PREVIOUS_PAGE,
    UNDEFINED,
};

class UserInterface {
    private:
        void printText() {

        };
        void printMenu() {

        };
        void printConsole() {

        };
        void printInputPrompt() {
            
        }
        void executeCommand(Command command) {

        }

    public:
        void printEditor();

        string inputCommand();
};

#endif