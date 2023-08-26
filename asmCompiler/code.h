#ifndef CODE_H_
#define CODE_H_

#include <deque>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <exception>

typedef long long memoryCell;

namespace formalLanguage {
const size_t npos = (size_t)(-1);

struct lexem : public std::string {
    size_t linePos;
    lexem (const std::string& content, const size_t pos);
};

class compilerError {
    std::vector<lexem>* line;
    std::string errorMsg;
    size_t pos;
    size_t lineNo;

public:
    static const size_t undefLineNo = (size_t)-1;

    compilerError (std::vector<lexem>& line, const std::string& errorMsg = "Something went wrong",
                   size_t pos = 0, size_t lineNo = undefLineNo) {
        this->pos      = pos;
        this->line     = &line;
        this->lineNo   = lineNo;
        this->errorMsg = errorMsg;
    }
};

class postProcessedText : public std::deque<std::vector<lexem>> {
    size_t lineNum;
    size_t lexemNum;
public:
    postProcessedText ();

    bool isEnd ();
    const lexem* getNextLexem ();
};

class binary {
    std::vector<memoryCell> code;
    size_t carriagePos;

public:
    binary ();

    void setCarrigePos ();
    void addMCell (memoryCell cell);
    void setCarrigePos (size_t newPos);
    memoryCell& operator[] (size_t idx);
};

class code {
protected:
    std::vector<std::string> text;
    postProcessedText parsedText;

    binary binaryCode;
public:
    std::string empty = " \n\r\t";
    std::string commentTerminator = ";";
    std::vector<std::string> technicalLexems = { // they must be in right order, example: "<=", "<"
        "\"", ",", "+", ";", "[", "]", "(", ")", ":" 
    };

    ~code () {}

    void virtual compile () = 0;
    void parse ();
    void loadFromSource (const std::string& srcFileName);
private:
    bool isEmpty (const char ch);
    void lineToLexems (std::string& line, std::vector<lexem>& lexContainer);
    //void genereByteCodeFromLine (const std::string& line, assembly::binaryCode& binary);
    void getQuote (std::string& str, size_t& pos, std::vector<lexem>& currLexems);
    bool searchFromTechnical (std::string& str, size_t& pos, std::vector<lexem>& currLexems);
};

class myasmCode : public code {
public:
    void compile ();
    void print ();
private:
    size_t tryGetSize  (std::vector<lexem>& line, size_t& pos);
    void  getArgument  (std::vector<lexem>& line, size_t& pos);
    void  getComand    (std::vector<lexem>& line, size_t& pos);
    void  compileLine  (std::vector<lexem>& line, size_t& pos);
    void  getDirective (std::vector<lexem>& line, size_t& pos);
    void  getLexem     (std::vector<lexem>& line, size_t& pos, std::string& lex);
};
}

#endif // code.h