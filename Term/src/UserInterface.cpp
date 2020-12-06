#include <UserInterface.hpp>

namespace UI {
    // Private function
    namespace {
        inline void printSeparator() {
            cout << "----------------------------------" << endl;
        }
        void printText(Editor& e) {
            e.show_current_page();
        };
        inline void printMenu() {
            cout << "(n)ext page, (p)revious page, "
                "(i)nsert word, (d)elete word, (r)eplace words, (s)earch word, "
                "(t)erminate after save. "
                << endl;
        };
        inline void printConsole(string msg) {
            cout << "[Console] " << msg << endl;
        };
        inline void printInputPrompt() {
            cout << "Input: ";
        }
    }

    void printInterface(Editor& e, string console_msg) {
        printSeparator();
        printText(e);

        printSeparator();
        printMenu();

        printSeparator();
        printConsole(console_msg);
        
        printSeparator();
        printInputPrompt();
    }
}