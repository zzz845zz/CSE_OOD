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

        Command interpretCommand(string input) {
            string arguments = input.substr(1, input.size());
            switch(input.at(0)) 
            {
                case 'i': // INSERT
                    break;
                case 'd': // DELETE
                    break;
                case 's': // SEARCH
                    break;
                case 'c': // CHANGE
                    break;
                case 't': // TERMINATE
                    ;
                case 'n': // NEXT_PAGE
                    break;
                case 'p': // PREVIOUS_PAGE
                    break;
                default:
                    return UNDEFINED;
            }
        }
        void executeCommand(Command command) {

        }

    public:
        void printEditor();

        string inputCommand();
};

#endif