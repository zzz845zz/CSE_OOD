#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <string.h>
#include <memory>
#include <cassert>

#include <Line.hpp>

using namespace std;


Line::Line(string str) {
    append(str);
}

// return: appended size
size_t Line::append(string str) {
    size_t size_original = _buf.size();

    _buf.append(str);
    this->fillBuf();

    size_t size_result = _buf.size();
    return size_result - size_original;
}

void Line::insert(size_t index, string word) {
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
string Line::flush() {
    string debris = _overflowed;
    _overflowed = "";
    return debris;
}

// Fill buffer with the overflowed string
void Line::alignSelf() {
    string overflowed = this->flush();     
    this->append(overflowed);
}

void Line::alignWith(Line otherLine) {
    this->alignSelf();

    string str_otherLine = otherLine.clear();
    this->append(str_otherLine);

    string overflowed = this->flush();
    otherLine.append(overflowed);
}

string Line::clear() {
    string ret = this->_buf + this->_overflowed;
    this->_buf = "";
    this->_overflowed = "";
    return ret;
}

string Line::getStr() {
    return this->_buf;
}

size_t Line::size() {
    return this->_buf.size();
}

bool Line::isFresh() {
    if (_buf.size() > BYTE_LIMIT_PER_LINETEXT || _overflowed.size() != 0) {
        return false;
    }
    return true;
}

// class Line {
//     private:
//         string _buf;
//         string _overflowed;

//         bool fillBuf() {
//             if (_buf.size() <= BYTE_LIMIT_PER_LINETEXT) {
//                 return false;
//             }
            
//             size_t found = _buf.rfind(" ");
//             if (found == string::npos) {
//                 throw std::out_of_range("Each word must be smaller than {} bytes!");
//             }

//             while (found > BYTE_LIMIT_PER_LINETEXT) { found = _buf.rfind(" ", found-1); }

//             string overflowed = _buf.substr(found);
//             _buf.erase(found);
//             _overflowed.append(overflowed);
//             return true;
//         }

//     public:
//         // Line(string str) {
//         //     append(str);
//         // }

//         // bool isFresh() {
//         //     if (_buf.size() > BYTE_LIMIT_PER_LINETEXT || _overflowed.size() != 0) {
//         //         return false;
//         //     }
//         //     return true;
//         // }

//         // // return: appended size
//         // size_t append(string str) {
//         //     size_t size_original = _buf.size();

//         //     _buf.append(str);
//         //     this->fillBuf();

//         //     size_t size_result = _buf.size();
//         //     return size_result - size_original;
//         // }

//         // void insert(size_t index, string word) {
//         //     size_t size_original = _buf.size();

//         //     size_t found = -1;
//         //     for(int i=0; i<index; ++i) { 
//         //         found = _buf.find(" ", found+1); 
//         //     }
            
//         //     if (found == string::npos) { throw std::out_of_range("'n'th word does not exist!"); }
//         //     this->_buf.insert(found, word+" ");

//         //     this->fillBuf();
//         // }

//         // // Flush remained overflowed string
//         // string flush() {
//         //     string debris = _overflowed;
//         //     _overflowed = "";
//         //     return debris;
//         // }

//         // // Fill buffer with the overflowed string
//         // void alignSelf() {
//         //     string overflowed = this->flush();     
//         //     this->append(overflowed);
//         // }

//         // void alignWith(Line otherLine) {
//         //     this->alignSelf();

//         //     string str_otherLine = otherLine.clear();
//         //     this->append(str_otherLine);

//         //     string overflowed = this->flush();
//         //     otherLine.append(overflowed);
//         // }

//         // string clear() {
//         //     string ret = this->_buf + this->_overflowed;
//         //     this->_buf = "";
//         //     this->_overflowed = "";
//         //     return ret;
//         // }

//         // string getStr() {
//         //     return this->_buf;
//         // }

//         // size_t size() {
//         //     return this->_buf.size();
//         // }
// };