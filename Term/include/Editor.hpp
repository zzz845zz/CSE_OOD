#ifndef EDITOR_H
#define EDITOR_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <string.h>
#include <memory>
#include <cassert>

#include <Line.hpp>
// #include <Util.hpp>
// #include <MyUtil.hpp>

using namespace std;

class Editor {
    private:
        fstream target;
        vector<Line> lines;   // TODO: How about just vector<string> instead of vector<Line>?
        size_t lineIndexFrom; // First line index that shown by editor 
        size_t lineIndexTo;   // Last line index that shown by editor

        /// Check if all lines is not longer than limit and there is no overflowed text.
        /// But there may be internal fragment.
        bool isFresh() {
            for(vector<Line>::iterator it = lines.begin();  it != lines.end(); ++it) {
                if(!(*it).isFresh()) {
                    return false;
                }
            }
            return true;
        }

        /** Append texts to the back.
         * 
         *  - Covert from string to Line and append. 
         * */ 
        size_t addNewLine(string texts) {
            assert(this->isFresh());
            size_t num_new_lines = 0;

            // Loop until there is no overflowed text
            string buffer = texts;
            while (buffer != "") {
                Line newLine(buffer);
                lines.push_back(newLine);
                buffer = newLine.flush();

                ++num_new_lines;
            }
            return num_new_lines;
        }

        /// Align all lines with each next line
        void refresh(int from=0) {
            assert(from < lines.size());

            vector<Line>::iterator it = lines.begin()+from;
            vector<Line>::iterator end = lines.end()-1;

            while (it != end) {
                (*it).align_with(*(it+1));
                ++it;
            }

            string overflowed = (*it).flush();
            this->addNewLine(overflowed);
        }

        void move_page(size_t target_start_line) {
            if (target_start_line < 0 || target_start_line >= lines.size()) {
                throw out_of_range(" can't move to page that start with line number " + target_start_line);
            }
            lineIndexFrom = target_start_line;
            lineIndexTo = min(lineIndexFrom+20, lines.size());
        }

    public:
        Editor();
        Editor(string filepath);
        ~Editor();

        // Push the word to the next line recursively.
        bool insert(size_t line_num, size_t word_num, string word);
        // Pull the word to the previous line recursively.
        bool delete_word(size_t line_num, size_t word_num);
        // Change `lineIndexFrom`, `lineIndexTo`
        bool search(string targetStr);
        // Pushed or Pull the word recursively.
        bool replace(string src, string dest);
        // Save file and terminate.
        bool terminate();

        // If editor can display 'last subset of current page + next page' at once, then do so. 
        bool move_to_next_page();
        bool move_to_previous_page();
        bool show_current_page();
};

#endif