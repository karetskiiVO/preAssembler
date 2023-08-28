#ifndef CODE_H_
#define CODE_H_

#include <deque>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <exception>

namespace formalLanguage {
const size_t npos = (size_t)(-1);

struct lexem : public std::string {
    size_t linePos;
    lexem (const std::string& content, const size_t pos);
};

struct compilerError {
    size_t pos;
    size_t lineNo;
    std::string errorMsg;
    const std::string* line;

    static const size_t undefLineNo = (size_t)-1;

    compilerError (const std::string& errorMsg = "Something went wrong", size_t pos = 0,
                   size_t lineNo = undefLineNo, std::string* line = nullptr) {
        this->pos      = pos;
        this->line     = line;
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
    std::vector<size_t> code;
    size_t carriagePos;

public:
    binary ();

    void setCarrigePos ();
    void setCarrigePos (size_t newPos);
    size_t getCarrigePos ();

    size_t& operator[] (size_t idx);

    void addMCell (size_t cell);
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
    struct lable : std::string {
        size_t addres;
        std::vector<size_t> lableAddress;
    };

public:
    void compile ();
    void print ();
private:
    std::vector<lable> lableTable;

    void getCommand   (std::vector<lexem>& line, size_t& pos);
    void compileLine  (std::vector<lexem>& line, size_t& pos);
    //void getDirective (std::vector<lexem>& line, size_t& pos);
    void tryGetMemory (std::vector<lexem>& line, size_t& pos, size_t& command);
    void tryGetReg    (std::vector<lexem>& line, size_t& pos, size_t& command);
    void trtGetCnst   (std::vector<lexem>& line, size_t& pos, size_t& command);
    void tryGetLable  (std::vector<lexem>& line, size_t& pos, size_t& command);
    void tryGetRegFac (std::vector<lexem>& line, size_t& pos, size_t& command);

    void tryGetSize   (std::vector<lexem>& line, size_t& pos, size_t& command);
    void getArgument  (std::vector<lexem>& line, size_t& pos, size_t& command);
    void getLexem     (std::vector<lexem>& line, size_t& pos, const std::string& lex);    
};
}

#endif // code.h