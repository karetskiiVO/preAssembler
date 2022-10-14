#ifndef CONSTANTS
#define CONSTANTS

#define DEF_CMD(_name, _num, _arg, ...) CMD_##_name = (_num),

enum CMDLIST {
    #include "comands.h"
};

#undef DEF_CMD

enum REGISTER {
    RAX = 1,
    RBX = 2,
    RCX = 3,
    RDX = 4
};

enum SPECIAL_BYTES {
    MEM_BIT = 10,
    REG_BIT = 9,
    INU_BIT = 8
};

#endif