#include "cpu.h"
#include <stdio.h>
#include <math.h>

#define mask (((short)1 << (sizeof(char) * 8)) - 1)

#define DEF_CMD(_name, _num, _arg, ...) \
    case (_num):                        \
        __VA_ARGS__                     \
        break;

int main () {
    CPU_START;
    char* programm;
    size_t progsize = 0;
    Upload(&programm, &progsize, "hexprog.txt");

    for (size_t ip = 0; ip < progsize;) {
        switch (*(short*)(programm + ip) & mask) {
            #include "comands.h"
            default:
                printf("incorrect work\n");
                return -1;
            break;
        }
        //stackDump(mainstack);
    }

    return 0;
}

#undef DEF_CMD
