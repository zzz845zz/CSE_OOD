
#include <Editor.hpp>

Editor::Editor() { 
}

Editor::Editor(string filepath) {
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
        buffer = newLine.flush();
        lines.push_back(newLine);

    }
    lineIndexFrom = 0;
    lineIndexTo = 20;
}

Editor::~Editor() {
    target.close();
}

/** 
 * Insert word and push the lines.
 * 
 * @param line_num Line number to insert
 * @param word_num The [word] will be inserted right after this 'word_num'th word
 * @param word Word to insert
 * @return success or fail
 * 
 * */
bool Editor::insert(size_t line_num, size_t word_num, string word) {
    // TODO: out of index error (If line_num <= 0)
    lines[line_num-1].insert(word_num, word);
    refresh(line_num-1);
    return true;
};

/** 
 * Delete the word and pull the lines.
 * 
 * @param param1 param1 description
 * @return success or fail
 * 
 * */
bool Editor::delete_word(size_t line_num, size_t word_num) {
    // TODO: out of index error (If line_num <= 0)
    lines[line_num-1].delete_word(word_num);
    refresh(line_num-1);
    return true;
}

/** 
 * Searching the word and indicate it at the first line.
 * 
 * @param param1 param1 description
 * @return success or fail
 * 
 * */
bool Editor::search(string target) {
    size_t ix = 0;
    for(vector<Line>::iterator it= lines.begin(); it!=lines.end(); ++it) {
        if ((*it).contains(target)) {
            this->move_page(ix);
            return true;
        }
        ++ix;
    }
    return false;
}

/** 
 * Replace word
 * 
 * @param param1 param1 description
 * @return success or fail
 * 
 * */
bool Editor::replace(string src, string dest) {
    for(vector<Line>::iterator it= lines.begin(); it!=lines.end(); ++it) {
        (*it).replace(src, dest);
    }
    refresh();
    return true;
}

/** 
 * Save text file and terminate.
 * 
 * @param param1 param1 description
 * @return success or fail
 * 
 * */
bool Editor::terminate() {
    // TODO: Save
    return true;
}

// If editor can display 'last subset of current page + next page' at once, then do so. 
/** 
 * Increase the number of the line that will be displayed to the user
 * 
 * @param param1 param1 description
 * @return success or fail
 * 
 * */
bool Editor::move_to_next_page() {
    lineIndexTo = min(lines.size(), lineIndexTo+20);
    lineIndexFrom = max(0, (int)(lineIndexTo-20));
    return true;
}

/** 
 * Decrease the number of the line that will be displayed to the user
 * 
 * @param param1 param1 description
 * @return success or fail
 * 
 * */
bool Editor::move_to_previous_page() {
    lineIndexFrom = max(0, (int)(lineIndexFrom-20));
    lineIndexTo = min(lines.size(), lineIndexFrom+20);
    return true;
}

/** 
 * Show lines that the editor is pointing to currently
 * 
 * @param param1 param1 description
 * @return success or fail
 * 
 * */
bool Editor::show_current_page() {
    printf("\n\n\n");
    printf("(Line %d~%d / %d)\n", lineIndexFrom, lineIndexTo-1, lines.size()-1);
    vector<Line>::iterator it = lines.begin() + lineIndexFrom;
    vector<Line>::iterator end = lines.begin() + min(lines.size(), lineIndexTo);

    size_t line_num = lineIndexFrom;
    while (it != end) {
        printf("%2d| %-71s --- len: %d\n", line_num++, (*it).get_text().c_str(), (*it).get_size()+LINE_HEADER_SIZE);
        ++it;
    }
    return true;
}