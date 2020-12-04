#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <string.h>
#include <memory>
#include <cassert>

#include <Line.hpp>
#include <Editor.hpp>
#include <UserInterface.hpp>
#include <CommandIntepreter.hpp>

using namespace std;

const string TARGET_FILE = "/home/seungminjeon/Desktop/study/CSE_OOD/Term/data/test.txt";


bool execute_command(Command* cmd, Editor& e) {
    size_t num0, num1;
    string word0, word1;

    // Extract argument
    switch(cmd->cargtype) 
    {
        case I_TYPE:
            num0 = cmd->cargs->args_itype.i0;           // arg0
            num1 = cmd->cargs->args_itype.i1;           // arg1
            word0 = cmd->cargs->args_itype.s2_option;   // arg2 (dummy string if it doesn't use option)
            break;
        case S_TYPE:
            word0 = cmd->cargs->args_stype.s0;         // arg0
            word1 = cmd->cargs->args_stype.s1_option;  // arg1 (dummy string if it doesn't use option)
            break;
        case N_TYPE:
            break;
    }

    // Execute
    switch(cmd->ctype)
    {
        case INSERT:   // I-TYPE   e.g. i(1,10,hello)
            return e.insert(num0, num1, word0);
        case DELETE:   // I-TYPE   e.g. d(2,10)
            return e.delete_word(num0, num1);
        case SEARCH:   // S-TYPE   e.g. s(hello)
            return e.search(word0);
        case REPLACE:   // S-TYPE   e.g. r(hello,bye)
            return e.replace(word0, word1);
        case TERMINATE:    // No args  e.g. t
            return e.terminate();
        case NEXT_PAGE:    // No args  e.g. n
            return e.move_to_next_page();
        case PREVIOUS_PAGE:// No args  e.g. p
            return e.move_to_previous_page();
        case CHANGE_VIEW:  // I-TYPE   e.g. v(20, 30): Change view property to width 20, height 30
        case CHANGE_FILE:
        case UNDEFINED:
            // TODO 3 state above
            break;
    }
    return false;
}

int main() {
    try {
        // Load text file
        Editor t(TARGET_FILE);
        
        string input;
        string console_msg = "Hi!";
        while (true) {
            try {
                UI::printInterface(t, console_msg);

                input = UI::input();
                Command* cmd = CommandIntepreter::instance()->interptret_input(input);

                if (execute_command(cmd, t)) {
                    console_msg = input +" success";
                    if (cmd->ctype == TERMINATE) {
                        cout << "Terminated!" << endl;
                        break;
                    }
                } else {
                    console_msg = input +" failed";
                }

            }
            catch (invalid_argument& e) {
                // cout << "Exception: " << e.what() << endl;
                console_msg = "Invalid input: "+input + "    <--- err msg: "+ e.what();
            }
        }
    }
    catch (std::exception& e) {
        cout << "Exception: " << e.what() << endl;
    }

    // cout << "Finish" << endl;
    delete(CommandIntepreter::instance());
	return 0;
}