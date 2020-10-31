#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <string.h>
#include <memory>
#include <cassert>

using namespace std;

const string TARGET_FILE = "C:/Users/MDCL/Desktop/SeungminJeon/CSE_OOD/Term/test.txt";

const size_t LINE_LIMIT_PER_PAGE = 20; 

const size_t LEFT = 4;
const size_t BYTE_LIMIT_PER_LINE = 75;
const size_t BYTE_LIMIT_PER_LINETEXT = BYTE_LIMIT_PER_LINE - LEFT;

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

class Line {
    private:
        string _buf;
        string _overflowed;

        bool fillBuf() {
            if (_buf.size() <= BYTE_LIMIT_PER_LINETEXT) {
                return false;
            }
            
            size_t found = _buf.rfind(" ");
            if (found == string::npos) {
                throw std::out_of_range("Each word must be smaller than {} bytes!");
            }

            while (found > BYTE_LIMIT_PER_LINETEXT) { found = _buf.rfind(" ", found-1); }

            string overflowed = _buf.substr(found);
            _buf.erase(found);
            _overflowed.append(overflowed);
            return true;
        }

    public:
        Line(string str) {
            append(str);
        }

        bool isFresh() {
            if (_buf.size() > BYTE_LIMIT_PER_LINETEXT || _overflowed.size() != 0) {
                return false;
            }
            return true;
        }

        // return: appended size
        size_t append(string str) {
            size_t size_original = _buf.size();

            _buf.append(str);
            this->fillBuf();

            size_t size_result = _buf.size();
            return size_result - size_original;
        }

        void insert(size_t index, string word) {
            size_t size_original = _buf.size();

            size_t found = -1;
            for(int i=0; i<index; ++i) { 
                found = _buf.find(" ", found+1); 
            }
            
            if (found == string::npos) { throw std::out_of_range("'n'th word does not exist!"); }
            this->_buf.insert(found, word+" ");

            this->fillBuf();
        }

        // Flush remained overflowed string
        string flush() {
            string debris = _overflowed;
            _overflowed = "";
            return debris;
        }

        // Fill buffer with the overflowed string
        void alignSelf() {
            string overflowed = this->flush();     
            this->append(overflowed);
        }

        void alignWith(Line otherLine) {
            this->alignSelf();

            string str_otherLine = otherLine.clear();
            this->append(str_otherLine);

            string overflowed = this->flush();
            otherLine.append(overflowed);
        }

        string clear() {
            string ret = this->_buf + this->_overflowed;
            this->_buf = "";
            this->_overflowed = "";
            return ret;
        }

        string getStr() {
            return this->_buf;
        }

        size_t size() {
            return this->_buf.size();
        }
};

class TextEditor {
    private:
        fstream target;
        vector<Line> lines;   // TODO: How about just vector<string> instead of vector<Line>?
        size_t lineIndexFrom; // First line index that shown by editor 
        size_t lineIndexTo;   // Last line index that shown by editor

        bool isFresh() {
            for(vector<Line>::iterator it = lines.begin();  it != lines.end(); ++it) {
                if(!(*it).isFresh()) {
                    return false;
                }
            }
            return true;
        }

        size_t addNewLine(string texts) {
            assert(this->isFresh());
            size_t aa = 0;
            string buffer = texts;
            while (buffer != "") {
                Line newLine(buffer);
                lines.push_back(newLine);
                buffer = newLine.flush();

                ++aa;
            }
            return aa;
        }

        void refresh(int from=0) {
            assert(from < lines.size());

            vector<Line>::iterator it = lines.begin()+from;
            vector<Line>::iterator end = lines.end()-1;

            while (it != end) {
                (*it).alignWith(*(it+1));
                ++it;
            }

            string overflowed = (*it).flush();
            this->addNewLine(overflowed);
        }

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
                // std::cout << " Generate line " << i++ << std::endl;

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
        void insert(size_t lineNumber, size_t wordNumber, string word) {
            lines[lineNumber].insert(wordNumber, word);
            refresh(lineNumber);
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
                printf("%2d| %s --- len: %d\n", line_num++, (*it).getStr().c_str(), (*it).size());
                ++it;
            }
        }
};


class UserInterface {
        void printText() {

        }
        void printMenu() {

        }
        void printConsole() {

        }
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
        void printEditor() {
            printText();
            printMenu();
            printConsole();
            printInputPrompt();
        }

        string inputCommand() {
            string input;
            cout << "입력: ";
            cin >> input;
            return input;
        }


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
    cout << "Finish" << endl;
	return 0;
}