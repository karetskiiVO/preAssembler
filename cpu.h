#ifndef VIRTUAL_CPU
#define VIRTUAL_CPU

#include "cstack.h"

extern Stack mainstack;
extern Stack callstack;

#define CPU_START  \
stackCtor(mainstack, 0);\
stackCtor(callstack, 0);

#define PUSH(_elem) Push(&mainstack, (_elem))
#define POP Pop(&mainstack)
#define DMP stackDump(mainstack);

double Pop (Stack* stk);

void  Push (Stack* stk, Elem_t elem);

void Upload (char** chbuf, size_t* size, const char* filename);

#endif // cpu.h