#include "code.h"
#include "data.h"

using namespace formalLanguage;
using namespace machinVariables;

void myasmCode::compile () {
    for (size_t i = 0; i < parsedText.size(); i++) {
        compileLine(parsedText[i], i);
    }
}

static const size_t searchLexem (const lexem& lex, const std::vector<std::string>& container) {
    for (size_t i = 0; i < container.size(); i++) {
        if (lex == container[i]) return i;
    }

    return npos;
}

size_t myasmCode::tryGetSize (std::vector<lexem>& line, size_t& pos) {
    if (pos >= line.size()) return;
    
    auto lexp = searchLexem(line[pos], comandSizeNames);
    if (lexp == npos) return 8;
    
    pos++;
    switch (lexp) {
        case comandSize::Byte:  return 1;
        case comandSize::Word:  return 2;
        case comandSize::Dword: return 4;
        case comandSize::Qword: return 8;
    }
}

void myasmCode::getLexem (std::vector<lexem>& line, size_t& pos, std::string& lex) {
    if (pos >= line.size()) throw compilerError(line, "Expected: " + lex, pos);
    if (line[pos] != lex)   throw compilerError(line, "Expected: " + lex, pos);
    
    pos++;
}

void myasmCode::getArgument (std::vector<lexem>& line, size_t& pos) {
    // stops here
}

void myasmCode::getComand (std::vector<lexem>& line, size_t& pos) {
    if (pos >= line.size()) return;
    auto lexp = searchLexem(line[pos], comandNames);

    if (lexp == npos) return;
    pos++;

    size_t comSize = 8;

    switch (lexp) {
        case comands::add:
        case comands::sub:
        case comands::div:
        case comands::mul:
            comSize = tryGetSize(line, pos);

            break;
        case comands::fadd:
        case comands::fmul:
        case comands::fdiv:
        case comands::fsub:
        

            break;
        case comands::cmp:
            comSize = tryGetSize(line, pos);

            break;
        case comands::call:
        case comands::jmp:
        case comands::je:
        case comands::jg:
        case comands::jge:
        case comands::jl:
        case comands::jle:
        case comands::jne:
        case comands::loop:
        case comands::push:

        
        case comands::pop:


        case comands::hlt:
        case comands::ret:
        case comands::syscall:

    }
}

void myasmCode::compileLine (std::vector<lexem>& line, size_t& pos) {
    getComand(line, pos);
    //getDirective(line, pos);
}
