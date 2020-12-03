#ifndef LINE_H
#define LINE_H

#include <stdio.h>
#include <string>
#include <vector>
#include <string.h>
#include <memory>

using namespace std;

const size_t LINE_LIMIT_PER_PAGE = 20; 
const size_t LINE_HEADER_SIZE = 4;
const size_t BYTE_LIMIT_PER_LINE = 75;
const size_t BYTE_LIMIT_PER_LINETEXT = BYTE_LIMIT_PER_LINE - LINE_HEADER_SIZE;

const char WORD_DELIMITER = ' '; 

// Conditions for validate
//  #Line_fresh          : #buf_fresh && #overflowed_flush
//  #buf_fresh           : Length of [_buf] is not longer than [BYTE_LIMIT_PER_LINETEXT]
//  #overflowed_fresh    : Length of [_overflowed] is 0  
class Line {
    private:
        string _buf;
        string _overflowed;

        /** 
         * Fill own buffer using own overflowed string
         * @return return value description
         * @example
         *           before      buf:abc___       ,   of:dheee
         *           after       buf:abcdhe       ,  of:ee
         * @invariant
         *           #Line_fresh =>  #Line_fresh
         *           #buf_fresh  =>  #buf_fresh
         * */
        bool fill_buf() {
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

        /** 
         * Align itself. Fill own buffer using own overflowed string
         * 
         * @param p p description
         * @return return value description
         * @example
         *          before      buf:abc___ , of:dheee
         *          after       buf:abcdhe , of:ee
         * 
         *          before      buf:abcdhe(fff) , of:
         *          after       buf:abcdhe      , of:fff
         * @invariant
         *          _   => #buf_fresh (validated)
         * */
        void align_self() {
            string all = this->clear();     
            this->append_back(all);
        }

    public:
        Line(string str);

        bool isFresh();

        // return: appended size
        size_t append_back(string str);
        size_t append_front(string str);

        void insert(size_t word_num, string word);
        string delete_word(size_t word_num);
        bool contains(string target);
        void replace(string from, string to);

        // Flush remained overflowed string
        string flush();

        // Fill buffer with the overflowed string
        void align_with(Line& otherLine);

        string clear();
        string get_text();
        size_t get_size();
};

#endif