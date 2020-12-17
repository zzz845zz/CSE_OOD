#include <memory>

#include <Line.hpp>
#include <Editor.hpp>
#include <UserInterface.hpp>
#include <CommandIntepreter.hpp>

using namespace std;

const string FILE_READ = "./data/test.txt";
const string FILE_WRITE = "./data/test_write.txt";


bool execute_command(Command* cmd, Editor& e) {
    vector<Argument> args = cmd->args;

    // Execute
    switch(cmd->ctype)
    {
        case INSERT:   // e.g. i(1,10,hello)
            return e.insert(args[0], args[1], args[2]);
        case DELETE:   // e.g. d(2,10)
            return e.delete_word(args[0], args[1]);
        case SEARCH:   // e.g. s(hello)
            return e.search(args[0]);
        case REPLACE:   // e.g. r(hello,bye)
            return e.replace(args[0], args[1]);
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