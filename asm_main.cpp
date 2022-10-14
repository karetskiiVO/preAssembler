#include <stdio.h>
#include <stdlib.h>

#include "asm.h"

int main () {
    String* code;
    char* bincode;
    size_t strcnt = 0;
    ReadCode("test.code", &code, &strcnt);
    printf("%d\n", strcnt);
    bincode = (char*)calloc(strcnt, sizeof(short) + sizeof(char) + sizeof(double));
    Compile(code, strcnt, bincode);
    Compile(code, strcnt, bincode);

    printf("%p\n", bincode);

    FILE* fout = fopen("hexprog.txt", "w");
    fwrite(bincode, sizeof(short) + sizeof(char) + sizeof(double), strcnt, fout);
    fclose(fout);
    return 0;
}

