#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <string.h>
#include <memory>
#include <cassert>

#include <Line.hpp>
#include <Util.hpp>

using namespace std;

Line::Line(string str) {
    append_back(str);
}

/** 
 * Function description
 * 
 * @param p p description
 * @return appended size
 * @invariant
 *          #buf_fresh => #buf_fresh (validated)
 * */
size_t Line::append_back(string str) {
    size_t size_original = _buf.size();

    _buf.append(str);
    this->fill_buf();

    size_t size_result = _buf.size();
    return size_result - size_original;
}

/** 
 * Function description
 * 
 * @param p p description
 * @return appended size
 * @invariant
 *          #buf_fresh => #buf_fresh (validated)
 * */
size_t Line::append_front(string str) {
    size_t size_original = _buf.size();

    string origin = this->clear();
    _buf.append(str);       // str first
    _buf.append(origin);    // origin back
    this->fill_buf();

    size_t size_result = _buf.size();
    return size_result - size_original;
}

/** 
 * Function description
 * 
 * @param p p description
 * @return x description
 * @invariant
 *          #buf_fresh => #buf_fresh (validated)
 * */
void Line::insert(size_t word_num, string word) {
    size_t found = -1;
    for(int i=0; i<word_num; ++i) { 
        found = _buf.find(WORD_DELIMITER, found+1); 
    }
    if (found == string::npos) { 
        throw std::out_of_range("'n'th word does not exist!"); 
    }

    this->_buf.insert(found+1, word + WORD_DELIMITER);
    this->fill_buf();
}

/** 
 * Function description
 * 
 * @param index index of word that will be deleted
 * @return return value description
 * @example
 *           before      buf:_____  ,  of:~
 *           after       buf:_____  ,  of:~
 * @invariant
 *          #buf_fresh => #buf_fresh (validated)
 * */
string Line::delete_word(size_t word_num) {
    size_t found = -1;
    for(int i=0; i<word_num; ++i) { 
        found = _buf.find(WORD_DELIMITER, found+1); 
    }
    if (found == string::npos) { 
        throw std::out_of_range("'n'th word does not exist!"); 
    }
    size_t delete_start = found;
    size_t delete_end = min(_buf.find(WORD_DELIMITER, delete_start+1), _buf.size());  // `min()`: For the case that the target is last word
    
    string deleted = this->_buf.erase(delete_start, delete_end-delete_start);
    this->fill_buf();
    return deleted;
}

/** 
 * Function description
 * 
 * @param p p description
 * @return x description
 * @invariant
 *          _ => #buf_fresh (validated)
 * */
void Line::replace(string from, string to) {
    _buf = util::replace_all(_buf, from, to);
    _overflowed = util::replace_all(_overflowed, from, to);
    this->align_self();
}

/** 
 * Checking if target exists in the Line
 * 
 * @param target
 * @return True if there is in the Line
 * @invariant
 *          #buf_fresh => #buf_fresh (validated)
 * */
bool Line::contains(string target) {
    return _buf.find(target) != string::npos;
}

/** 
 * Flush remained overflowed string and make `_overflowed` empty
 * 
 * @param p p description
 * @return return value description
 * @invariant
 *          _           => #overflowed_fresh (validated)
 *          #buf_fresh  => #Line_fresh (validated)
 * */
string Line::flush() {
    string debris = _overflowed;
    _overflowed = "";
    return debris;
}

/** 
 * Align with other Line.  
 * It can destroy [otherLine]'s invariant condition
 * 
 * @param p p description
 * @return return value description
 * @example
 *          before      self: <buf:abc___, of:dh>,      other: <buf:ghf___, of:wow>
 *          after       self: <buf:abcdhg, of:>,        other: <buf:hfwow_, of:>
 *  
 *          before      self: <buf:abc___, of:abcdefgh>,other: <buf:ghf___, of:wow>
 *          after       self: <buf:abcabc, of:>,        other: <buf:defghg, of:hfwow>
 * @invariant
 *          _ => #Line_fresh (validated)
 * */
void Line::align_with(Line& otherLine) {
    this->align_self(); // _ => buf_fresh

    string str_otherLine = otherLine.clear();
    this->append_back(str_otherLine); // #buf_fresh => #buf_fresh

    string overflowed = this->flush(); // #buf_fresh  => #Line_fresh
    otherLine.append_front(overflowed);
}

/** 
 * Return all texts in the line( `_buf` + `_overflowed` ) and Make it empty 
 * 
 * @param p p description
 * @return return value description
 * @invariant
 *          _ => #Line_fresh
 * */
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

/// Check @Line_fresh: Check if [Line] is not longer than limit and there is no overflowed text.
bool Line::isFresh() {
    return _buf.size() <= BYTE_LIMIT_PER_LINETEXT && _overflowed.size() == 0;
}