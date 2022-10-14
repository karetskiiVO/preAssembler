#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "asm.h"

int main (int argc, char* argv[]) {
    if (argc != 3) {
        printf("ERROR, no file\n");
    }

    String* code  = NULL;
    char* bincode = NULL;
    size_t strcnt = 0;
    readCode(argv[1], &code, &strcnt);

    bincode = (char*)calloc(strcnt, sizeof(short) + sizeof(char) + sizeof(double));
    Compile(code, strcnt, bincode, false);
    Compile(code, strcnt, bincode, true);

    printCode(argv[2], bincode, strcnt);
    return 0;
}

