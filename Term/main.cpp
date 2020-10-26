#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <string.h>

using namespace std;

const string TARGET_FILE = "C:/Users/MDCL/Desktop/SeungminJeon/CSE_OOD/Term/test.txt";

const size_t LINE_LIMIT_PER_PAGE = 20; 

const size_t LEFT = 4;
const size_t BYTE_LIMIT_PER_LINE = 75;
const size_t BYTE_LIMIT_PER_LINETEXT = BYTE_LIMIT_PER_LINE - LEFT;

class Line {
    private:
        string _str;
        string _overflowed;

    public:
        Line(string str) {
            append(str);
        }

        void append(string str) {
            _str.append(str);
            if (_str.size() <= BYTE_LIMIT_PER_LINETEXT) {
                cout << "enough!" << endl;
                return;
            }
            
            size_t found = _str.rfind(" ");
            if (found == string::npos) {
                cout<< "no!!" << endl;
                throw std::out_of_range("Each word must be smaller than 75 bytes!");
            }

            while (found > BYTE_LIMIT_PER_LINETEXT) {
                found = _str.rfind(" ", found-1);
            }

            string overflowed = _str.substr(found);
            _str.erase(found);
            // _str = _str.substr(0, found);
            _overflowed.append(overflowed);

            // if (_str.size() > BYTE_LIMIT_PER_LINETEXT) {
            //     cout << _str.size() << endl;
            //     throw std::out_of_range("Each word must be smaller than 75 bytes!");
            // }
        }

        string flush() {
            string ret = _overflowed;
            _overflowed = "";
            return ret;
        }

        void show() {
            cout << _str << " --> len: " << _str.size() << endl;
        }

};

class TextEditor {
    private:
        fstream target;
        vector<Line> lines;   // TODO: How about just vector<string> instead of vector<Line>?
        size_t lineIndexFrom; // First line index that shown by editor 
        size_t lineIndexTo;   // Last line index that shown by editor

    public:
        TextEditor() {
            
        }

        TextEditor(string filepath) {
            std::cout << "hi!" << std::endl;
            if(target) {
                target.close();
			};

            // fstream t(filepath);
            target = fstream(filepath);

            if (!target.is_open()) {
                std::cout << "unable to open file";
                return;
            } 

            // Read overall text
            string buffer;
            target.seekg(0, std::ios::end); // Changing 'read position' to end of file
            int size = target.tellg();      // Read 'read position' (It means total size of file)
            buffer.resize(size);            // Resize buffer to corrosponding size
            target.seekg(0, std::ios::beg); // Changing 'read position' to start of file
            target.read(&buffer[0], size);  // Read overall and write to buffer

            // Extract Lines
            int i = 0;
            while (buffer != "") {
                std::cout << " Generate line " << i++ << std::endl;

                Line newLine(buffer);
                lines.push_back(newLine);

                buffer = newLine.flush();
            }
            lineIndexFrom = 0;
            lineIndexTo = 20;
        }

        ~TextEditor() {
            target.close();
		}

        // Push the word to the next line recursively.
        void insert(uint_fast32_t lineNumber, uint_fast8_t wordNumber, string str) {
        };

        // Pull the word to the previous line recursively.
        void deleteWord(uint_fast32_t lineNumber, uint_fast8_t wordNumber) {
        }

        // Change `lineIndexFrom`, `lineIndexTo`
        void search(string targetStr) {
        }

        // Pushed or Pull the word recursively.
        void change(string src, string dest) {

        }

        // Save file and terminate.
        void terminate() {
        }

        // If editor can display 'last subset of current page + next page' at once, then do so. 
        void nextPage() {
        }

        void previousPage() {
        }

        void showPage() {
            cout << "len: " << lines.size() << endl;
            vector<Line>::iterator it = lines.begin() + lineIndexFrom;
            vector<Line>::iterator end = lines.begin() + min(lines.size(), lineIndexTo);

            size_t line_num = 1;
            while (it != end) {
                cout << line_num++ << "| ";
                (*it).show();
                ++it;
            }
        }
};


class IO {

};

int main() {
    try {

        TextEditor t(TARGET_FILE);
        cout << "show pages!" << endl;
        t.showPage();
    }
    catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
	return 0;
}