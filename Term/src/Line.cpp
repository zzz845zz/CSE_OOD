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
    append_back(str);
}

// return: appended size
size_t Line::append_back(string str) {
    size_t size_original = _buf.size();

    _buf.append(str);
    this->fill_buf();

    size_t size_result = _buf.size();
    return size_result - size_original;
}

size_t Line::append_front(string str) {
    size_t size_original = _buf.size();

    string origin = this->clear();
    _buf.append(str);       // str first
    _buf.append(origin);    // origin back
    this->fill_buf();

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

    this->fill_buf();
}

/// Flush remained overflowed string and make `_overflowed` empty
string Line::flush() {
    string debris = _overflowed;
    _overflowed = "";
    return debris;
}

/** Align itself. Fill own buffer using own overflowed string
 * 
 *  e.g.  
 *      before      buf:abc___ , of:dheee
 *      after       buf:abcdhe , of:ee
 * */
void Line::align_self() {
    // string overflowed = this->flush();     
    // this->append(overflowed);
    fill_buf();
}

/** Align with other Line.
 * 
 *  e.g.
 *      before      self: <buf:abc___, of:dh>,      other: <buf:ghf___, of:wow>
 *      after       self: <buf:abcdhg, of:>,        other: <buf:hfwow_, of:>
 * 
 *      before      self: <buf:abc___, of:abcdefgh>,other: <buf:ghf___, of:wow>
 *      after       self: <buf:abcabc, of:>,        other: <buf:defghg, of:hfwow>
 * */
void Line::align_with(Line otherLine) {
    this->align_self();

    string str_otherLine = otherLine.clear();
    this->append_back(str_otherLine);

    string overflowed = this->flush();
    otherLine.append_front(overflowed);
}

/// Return all texts in the line( `_buf` + `_overflowed` ) and Make it empty 
string Line::clear() {
    string ret = this->_buf + this->_overflowed;
    this->_buf = "";
    this->_overflowed = "";
    return ret;
}

/// Get texts in _buf
string Line::get_text() {
    return this->_buf;
}

/// Get size of text in _buf
size_t Line::get_size() {
    return this->_buf.size();
}

/// Check if [Line] is not longer than limit and there is no overflowed text.
bool Line::isFresh() {
    return _buf.size() <= BYTE_LIMIT_PER_LINETEXT && _overflowed.size() == 0;
}