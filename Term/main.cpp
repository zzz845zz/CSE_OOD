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


string execute_command(Command cmd, Editor& e) {
    size_t num0, num1;
    string word0, word1;
    switch(cmd.ctype)
    {
        case INSERT:   // I-TYPE   e.g. i(1,10,hello)
            num0 = cmd.args.args_itype.i0;          // index of line
            num1 = cmd.args.args_itype.i1;          // index of word
            word0 = cmd.args.args_itype.s2_option;  // new word to insert
            e.insert(num0, num1, word0);
            break;

        case DELETE:   // I-TYPE   e.g. d(2,10)
            num0 = cmd.args.args_itype.i0;          // index of line
            num1 = cmd.args.args_itype.i1;          // index of word
            e.delete_word(num0, num1);
            break;
            
        case SEARCH:   // S-TYPE   e.g. s(hello)
            word0 = cmd.args.args_stype.s0;         // word to search
            e.search(word0);
            break;

        case REPLACE:   // S-TYPE   e.g. r(hello,bye)
            word0 = cmd.args.args_stype.s0;         // src
            word1 = cmd.args.args_stype.s1_option;  // dest
            e.replace(word0, word1);
            break;

        case TERMINATE:    // No args  e.g. t
            e.terminate();
            return "Terminate";

        case NEXT_PAGE:    // No args  e.g. n
            e.move_to_next_page();
            break;
        case PREVIOUS_PAGE:// No args  e.g. p
            e.move_to_previous_page();
            break;

        case CHANGE_VIEW:  // I-TYPE   e.g. v(20, 30): Change view property to width 20, height 30
        case CHANGE_FILE:
        case UNDEFINED:
            // TODO 3 state above
            break;
    }
    
    //  TODO: console message
    return "Success execution!";
}

int main() {
    try {
        // Load text file
        Editor t(TARGET_FILE);
        // cout << "show pages!" << endl;
        // t.showPage();

        // Start
        string input;
        string console_msg = "Hi!";
        while (true) {
            try {
                UI::printInterface(t, console_msg);

                input = UI::input();
                Command cmd = interpretInput(input);
                console_msg = execute_command(cmd, t);

                if (console_msg.compare("Terminate")==0) {
                    break;
                }
            }
            catch (invalid_argument& e) {
                // cout << "Exception: " << e.what() << endl;
                console_msg = "Invalid input: "+input;
            }
        }
    }
    catch (std::exception& e) {
        cout << "Exception: " << e.what() << endl;
    }

    // cout << "Finish" << endl;
	return 0;
}