#include "cpu.h"
#include "constants.h"

#include <stdio.h>
#include <math.h>

#define mask (((short)1 << (sizeof(char) * 8)) - 1)
const size_t RAM_SIZE = 256;

double regist[5] = {0};
double RAM[256];

#define DEF_CMD(_name, _num, _arg, ...) \
    case (_num):                        \
        __VA_ARGS__                     \
        break;

int main (int argc, char* argv[]) {
    if (argc != 2) {
        printf("ERROR, no file\n");
    }

    CPU_START;
    char* programm  = NULL;
    size_t progsize = 0;
    Upload(&programm, &progsize, argv[1]);

    for (size_t ip = 0; ip < progsize;) {
        switch (*(short*)(programm + ip) & mask) {
            #include "comands.h"
            default:
                printf("incorrect work\n");
                return -1;
            break;
        }
    }

    return 0;
}

#undef DEF_CMD
