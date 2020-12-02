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
#include <Interface.hpp>

using namespace std;

const string TARGET_FILE = "/home/seungminjeon/Desktop/study/CSE_OOD/Term/data/test.txt";

int main() {
    try {

        Editor t(TARGET_FILE);
        cout << "show pages!" << endl;
        t.showPage();
    }
    catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    cout << "Finish" << endl;
	return 0;
}