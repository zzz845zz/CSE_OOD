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

using namespace std;

class Editor {
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
        Editor();
        Editor(string filepath);
        ~Editor();

        // Push the word to the next line recursively.
        void insert(size_t lineNumber, size_t wordNumber, string word);
        // Pull the word to the previous line recursively.
        void deleteWord(uint_fast32_t lineNumber, uint_fast8_t wordNumber);
        // Change `lineIndexFrom`, `lineIndexTo`
        void search(string targetStr);
        // Pushed or Pull the word recursively.
        void change(string src, string dest);
        // Save file and terminate.
        void terminate();

        // If editor can display 'last subset of current page + next page' at once, then do so. 
        void nextPage();
        void previousPage();
        void showPage();
};

#endif