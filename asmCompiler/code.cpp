#include "code.h"
#include "../data.h"

#include <cmath>
#include <string>
#include <memory>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace formalLanguage;

binary::binary () {
    carriagePos = 0;
}

void binary::setCarrigePos () {
    carriagePos = code.size();
}

void binary::setCarrigePos (size_t newPos) {
    carriagePos = newPos;
}

size_t& binary::operator[] (size_t idx) {
    return code[idx];
}

size_t binary::getCarrigePos () {
    return carriagePos;
}

void binary::addMCell (size_t cell) {
    if (carriagePos > code.size()) code.resize(carriagePos);

    if (carriagePos == code.size()) {
        code.push_back(cell);
    } else {
        code[carriagePos] = cell;
    }
    carriagePos++;
}

lexem::lexem (const std::string& content, const size_t pos) : std::string (content) {
    this->linePos = pos;
}

void code::loadFromSource (const std::string& srcFileName) {
    using namespace std;

    ifstream file;
    file.open(srcFileName);

    while (!file.eof()) {
        string bufLine;
        getline(file, bufLine);

        text.push_back(bufLine);
        // here
    }
    

    file.close();
}

bool code::isEmpty (const char ch) {
    return std::string::npos != empty.find(ch);
}

static bool isPrefix (const std::string& prefix, const std::string& base, const size_t baseStart = 0) {
    if (baseStart + prefix.length() > base.length()) return false;

    for (auto i = 0uLL; i < prefix.length(); i++) {
        if (prefix[i] == base[baseStart + i]) continue;
        return false;
    }

    return true;
}

bool code::searchFromTechnical (std::string& str, size_t& pos, std::vector<lexem>& currLexems) {
    for (auto i = 0uLL; i < technicalLexems.size(); i++) {
        if (isPrefix(technicalLexems[i], str, pos)) {
            currLexems.push_back(lexem(technicalLexems[i], pos));
            pos += technicalLexems[i].length() - 1;
            return true;
        }
    }

    return false;
}

void code::getQuote (std::string& str, size_t& pos, std::vector<lexem>& currLexems) {
    bool backSlashMode = false;
    currLexems.push_back(lexem("", pos));

    pos++;
    for (; pos < str.length(); pos++) {
        if (backSlashMode) {
            switch (str[pos]) {
                case '\\':
                    currLexems.back().push_back('\\');
                    break;
                case '"':
                    currLexems.back().push_back('"');
                    break;
                case 'n':
                    currLexems.back().push_back('\n');
                    break;
                case 't':
                    currLexems.back().push_back('\t');
                    break;
                case 'b':
                    currLexems.back().push_back('\b');
                    break;
                case 'a':
                    currLexems.back().push_back('\a');
                    break;
                case '0':
                    currLexems.back().push_back('0');
                    break;
                default:
                    currLexems.back().push_back(str[pos]);
                    break;
            }

            backSlashMode = false;
            continue;
        }

        if (str[pos] == '\\') {
            backSlashMode = true;
            continue;
        }
        if (str[pos] == '"') {
            currLexems.push_back(lexem("\"", pos));
            return;
        }

        currLexems.back().push_back(str[pos]);
    }
}

void code::lineToLexems (std::string& line, std::vector<lexem>& lexContainer) {
    bool writeToLexem = false;

    for (size_t i = 0; i < line.length(); i++) {
        if (isEmpty(line[i])) {
            writeToLexem = false;
            continue;
        }

        if (searchFromTechnical(line, i, lexContainer)) {
            if (lexContainer.back() == "\"") {
                getQuote(line, i, lexContainer);
            }

            writeToLexem = false;
            continue;
        }

        if (!writeToLexem) {
            writeToLexem = true;
            lexContainer.push_back(lexem("", i));
        }

        lexContainer.back().push_back(line[i]);
    }
}

void code::parse () {
    parsedText.resize(text.size());

    for (auto i = 0uLL; i < text.size(); i++) {
        lineToLexems(text[i], parsedText[i]);
    }
}

void myasmCode::print () {
    using namespace std;
    for (auto i = 0uLL; i < parsedText.size(); i++) {
        for (auto j = 0uLL; j < parsedText[i].size(); j++) {
            cout << "str: " << i + 1 << "\t\tpos: " << parsedText[i][j].linePos << "\t\tlexem: " << parsedText[i][j] << endl;
        }
    }
}

postProcessedText::postProcessedText () {
    lineNum  = 0;
    lexemNum = 0;
}

bool postProcessedText::isEnd () {
    return lineNum >= this->size() && lexemNum >= (*this)[lineNum].size();
}

const lexem* postProcessedText::getNextLexem () {
    if (isEnd()) return nullptr;

    lexem* res = &((*this)[lineNum][lexemNum]);
    lexemNum++;
    if (lexemNum >= (*this)[lineNum].size()) {
        lexemNum = 0;
        lineNum++;
    }

    return res;
}

