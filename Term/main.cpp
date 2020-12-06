#include <memory>

#include <Line.hpp>
#include <Editor.hpp>
#include <UserInterface.hpp>
#include <CommandIntepreter.hpp>

using namespace std;

const string FILE_READ = "/home/seungminjeon/Desktop/study/CSE_OOD/Term/data/test.txt";
const string FILE_WRITE = "/home/seungminjeon/Desktop/study/CSE_OOD/Term/data/test_write.txt";


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
            e.write(FILE_WRITE);
            return e.terminate();
        case NEXT_PAGE:    // No args  e.g. n
            return e.move_to_next_page();
        case PREVIOUS_PAGE:// No args  e.g. p
            return e.move_to_previous_page();
        case UNDEFINED:
            break;
    }
    return false;
}

int main() {
    try {
        // Load text file
        Editor editor(FILE_READ);
        
        string input;
        string console_msg = "Hi!";
        while (true) {
            try {
                UI::printInterface(editor, console_msg);

                input = UI::input();
                Command* cmd = CommandIntepreter::instance()->interptret_input(input);

                if (execute_command(cmd, editor)) {
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
                console_msg = "Invalid input: "+input + "    <--- err msg: "+ e.what();
            }
            catch (out_of_range& e) {
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