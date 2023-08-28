#include "code.h"
#include "data.h"

#include <fstream>
#include <iostream>

using namespace formalLanguage;
using namespace machinVariables;

std::ostream& operator<< (std::ostream& stream, compilerError& error) {
    stream << error.lineNo << "\t|\t"<< *(error.line) << "\n\t \t";
    for (int i = 0; i < error.pos - 1; i++) stream << "~";
    stream << "^\n";
    for (int i = 0; i < error.pos - 1; i++) stream << " ";
    stream << "Error: " << error.errorMsg << "\n";
    return stream;
}

void myasmCode::compile () {
    for (size_t i = 0; i < parsedText.size(); i++) {
        try {
            compileLine(parsedText[i], i);
        } catch (compilerError& err) {
            err.lineNo = i;
            if (err.line == nullptr) err.line = &text[i];

            std::cout << err;
        }
    }
}

static const size_t searchLexem (const lexem& lex, const std::vector<std::string>& container) {
    for (size_t i = 0; i < container.size(); i++) {
        if (lex == container[i]) return i;
    }

    return npos;
}

void myasmCode::tryGetSize (std::vector<lexem>& line, size_t& pos, size_t& command) {
    if (pos >= line.size()) return;
    
    auto lexp = searchLexem(line[pos], commandSizeNames);
    if (lexp == npos) {
        setCommandSize(command, 8);
        return;
    }
    
    pos++;
    switch (lexp) {
        case commandSize::Byte:
            setCommandSize(command, 1);
            return;
        case commandSize::Word:
            setCommandSize(command, 2);
            return;
        case commandSize::Dword:
            setCommandSize(command, 4);
            return;
        case commandSize::Qword:
            setCommandSize(command, 8);
            return;
    }
}

void myasmCode::getLexem (std::vector<lexem>& line, size_t& pos, const std::string& lex) {
    if (pos >= line.size()) throw compilerError("Expected: " + lex, pos);
    if (line[pos] != lex)   throw compilerError("Expected: " + lex, pos);
    
    pos++;
}

void myasmCode::tryGetMemory (std::vector<lexem>& line, size_t& pos, size_t& command) {
    try {
        getLexem(line, pos, "[");
    } catch (compilerError& err) {
        return;
    }

    while (true) {
        //getNm
        //tryGetReg
        //tryGetLable

        try {
            getLexem(line, pos, "+");
        } catch (compilerError& err) {
            break;
        }

    }

    getLexem(line, pos, "]");
}
//void tryGetRegstr (std::vector<lexem>& line, size_t& pos, size_t& command);
//void tryGetCnst   (std::vector<lexem>& line, size_t& pos, size_t& command);

void myasmCode::getArgument (std::vector<lexem>& line, size_t& pos, size_t& command) {
    //tryGetMemory
}

void myasmCode::getCommand (std::vector<lexem>& line, size_t& pos) {
    if (pos >= line.size()) return;
    auto lexp = searchLexem(line[pos], commandNames);

    if (lexp == npos) return;
    pos++;

    size_t commandPos = binaryCode.getCarrigePos();
    binaryCode.addMCell(lexp);

    switch (lexp) {
        case commands::add:
        case commands::sub:
        case commands::div:
        case commands::mul:
            tryGetSize(line, pos, binaryCode[commandPos]);

            break;
        case commands::fadd:
        case commands::fmul:
        case commands::fdiv:
        case commands::fsub:
        

            break;
        case commands::cmp:
            tryGetSize(line, pos, binaryCode[commandPos]);

            break;
        case commands::call:
        case commands::jmp:
        case commands::je:
        case commands::jg:
        case commands::jge:
        case commands::jl:
        case commands::jle:
        case commands::jne:
        case commands::loop:
        case commands::push:

        
        case commands::pop:


        case commands::hlt:
        case commands::ret:
        case commands::syscall:

    }
}

void myasmCode::compileLine (std::vector<lexem>& line, size_t& pos) {
    getCommand(line, pos);
    //getDirective(line, pos);
}
