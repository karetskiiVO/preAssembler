#ifndef DATA_H_
#define DATA_H_

#include <vector>
#include <string>

namespace machinVariables {
    const std::vector<std::string> registerNames  = {
        "rax", "rbx", "rcx", "rdx", "rsp", "rip", "rsi", "rdi",
         "r8",  "r9", "r10", "r11", "r12", "r13", "r14", "r15",
    };
    const std::vector<std::string> comandNames    = {
        "hlt", "syscall",    "jmp",   "call",    "ret",   "mov",
        "add",     "sub",    "mul",    "div",   "fadd",  "fsub",   "fmul",   "fdiv"
        "push",   "pop",     "cmp",     "je",    "jne",    "jl",    "jle",    "jg",   "jge",
        "loop"
    };

    const std::vector<std::string> directiveNames  = {
        ".org", ".include", ".long", ".float", ".byte", ".int", ".short"
    };

    const std::vector<std::string> comandSizeNames = {
        "byte", "word", "dword", "qword"
    };

    const char* END_MEM_MACROS = "END_MEM";
    const char* TIMES_MACROS   = "times";
    const char* COMMENTS_LEXEM = ";"; 

    const size_t  BYTEMASK = 0xFF;
    const size_t DBYTEMASK = 0xFFFF;

    const inline size_t getShift      (const size_t comand) {
        return (comand >> 56) &  BYTEMASK;
    }
    const inline size_t getFstArg     (const size_t comand) {
        return (comand >> 16) & DBYTEMASK;
    }
    const inline size_t getSndArg     (const size_t comand) {
        return (comand >> 32) & DBYTEMASK;
    }
    const inline size_t getComandSize (const size_t comand) {
        return (comand >>  8) &  BYTEMASK;
    }

    void inline setShift      (size_t& comand, size_t newShift) {
        comand = (comand & ~( BYTEMASK << 56)) | ((newShift & BYTEMASK) << 56);
    }
    void inline setFstArg     (size_t& comand, size_t fstArgType) {
        comand = (comand & ~(DBYTEMASK << 16)) | ((fstArgType & DBYTEMASK) << 16);
    }
    void inline setSndArg     (size_t& comand, size_t sndArgType) {
        comand = (comand & ~(DBYTEMASK << 32)) | ((sndArgType & DBYTEMASK) << 32);
    }
    void inline setComandSize (size_t& comand, size_t size) {
        comand = (comand & ~( BYTEMASK <<  8)) | ((size & BYTEMASK) << 8);
    }

    enum comandSize {
         Byte = 0,
         Word = 1,
        Dword = 2,
        Qword = 3,
    };

    enum argtype {
        mem = 0,
        reg = 1,
        cst = 2,
    };

    enum directives {
            org = 0,
        include = 1,
           Long = 2,
          Float = 3,
           Byte = 4,
            Int = 5,
          Short = 6,
    };

    enum registers {
        rax = 0,
        rbx = 1,
        rcx = 2,
        rdx = 3,
        rsp = 4,
        rip = 5,
        rsi = 6,
        rdi = 7,
         r8 = 8,
         r9 = 9,
        r10 = 10,
        r11 = 11,
        r12 = 12,
        r13 = 13,
        r14 = 14,
        r15 = 15,
    };

    enum comands {
         syscall = 0,
             hlt = 1,
             jmp = 2,
            call = 3,
             ret = 4,
             mov = 5,
             add = 6,
             sub = 7,
             mul = 8,
             div = 9,
            fadd = 10,
            fsub = 11,
            fmul = 12,
            fdiv = 13,
            push = 14,
             pop = 15,
             cmp = 16,
              je = 17,
             jne = 18,
              jl = 19,
             jle = 20,
              jg = 21,
             jge = 22,
            loop = 23,
    };
}

#endif // data.h