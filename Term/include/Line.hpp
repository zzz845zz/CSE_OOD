#ifndef LINE_H
#define LINE_H

#include <stdio.h>
#include <string>
#include <vector>
#include <string.h>
#include <memory>

using namespace std;

const size_t LINE_LIMIT_PER_PAGE = 20; 
const size_t LEFT = 4;
const size_t BYTE_LIMIT_PER_LINE = 75;
const size_t BYTE_LIMIT_PER_LINETEXT = BYTE_LIMIT_PER_LINE - LEFT;

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
        Line(string str);

        bool isFresh();

        // return: appended size
        size_t append(string str);

        void insert(size_t index, string word);

        // Flush remained overflowed string
        string flush();

        // Fill buffer with the overflowed string
        void alignSelf();
        void alignWith(Line otherLine);

        string clear();
        string getStr();

        size_t size();
};

#endif