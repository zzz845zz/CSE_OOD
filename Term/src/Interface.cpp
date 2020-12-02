#include <Interface.hpp>

void UserInterface::printEditor() {
    printText();
    printMenu();
    printConsole();
    printInputPrompt();
}

string UserInterface::inputCommand() {
    string input;
    cout << "입력: ";
    cin >> input;
    return input;
}