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
using namespace interpret;

const string TARGET_FILE = "/home/seungminjeon/Desktop/study/CSE_OOD/Term/data/test.txt";


bool execute_command(Command& cmd, Editor& e) {
    size_t num0, num1;
    string word0, word1;
    switch(cmd.ctype)
    {
        case INSERT:   // I-TYPE   e.g. i(1,10,hello)
            num0 = cmd.args->args_itype.i0;          // index of line
            num1 = cmd.args->args_itype.i1;          // index of word
            word0 = cmd.args->args_itype.s2_option;  // new word to insert
            return e.insert(num0, num1, word0);

        case DELETE:   // I-TYPE   e.g. d(2,10)
            num0 = cmd.args->args_itype.i0;          // index of line
            num1 = cmd.args->args_itype.i1;          // index of word
            return e.delete_word(num0, num1);
            
        case SEARCH:   // S-TYPE   e.g. s(hello)
            word0 = cmd.args->args_stype.s0;         // word to search
            return e.search(word0);

        case REPLACE:   // S-TYPE   e.g. r(hello,bye)
            word0 = cmd.args->args_stype.s0;         // src
            word1 = cmd.args->args_stype.s1_option;  // dest
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
    
    //  TODO: console message
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
                Command cmd = interpretInput(input);

                if (execute_command(cmd, t)) {
                    console_msg = input +" success";
                } else {
                    console_msg = input +" failed";
                }

                if (cmd.ctype == TERMINATE) {
                    cout << "Terminated!" << endl;
                    break;
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
	return 0;
}