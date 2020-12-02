
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
        lines.push_back(newLine);

        buffer = newLine.flush();
    }
    lineIndexFrom = 0;
    lineIndexTo = 20;
}

Editor::~Editor() {
    target.close();
}

// Push the word to the next line recursively.
void Editor::insert(size_t lineNumber, size_t wordNumber, string word) {
    lines[lineNumber].insert(wordNumber, word);
    refresh(lineNumber);
};

// Pull the word to the previous line recursively.
void Editor::deleteWord(uint_fast32_t lineNumber, uint_fast8_t wordNumber) {
}

// Change `lineIndexFrom`, `lineIndexTo`
void Editor::search(string targetStr) {
}

// Pushed or Pull the word recursively.
void Editor::change(string src, string dest) {

}

// Save file and terminate.
void Editor::terminate() {
}

// If editor can display 'last subset of current page + next page' at once, then do so. 
void Editor::nextPage() {
}

void Editor::previousPage() {
}

void Editor::showPage() {
    cout << "len: " << lines.size() << endl;
    vector<Line>::iterator it = lines.begin() + lineIndexFrom;
    vector<Line>::iterator end = lines.begin() + min(lines.size(), lineIndexTo);

    size_t line_num = 1;
    while (it != end) {
        printf("%2d| %s --- len: %d\n", line_num++, (*it).getStr().c_str(), (*it).size());
        ++it;
    }
}