#include "disasm.h"
#include "cstack.h"

#include <assert.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void Upload (char** chbuf, size_t* size, const char* filename) {
    FILE* file = fopen(filename, "r"); ////// may be some problems
    assert(file != NULL && "file must exist");

    struct stat out = {0};
    assert((fstat(fileno(file), &out) != -1) && "Error in file");
    *size = round(out.st_size / sizeof(char)) + sizeof(double);
    
    *chbuf = (char*)calloc(*size, sizeof(char));

    fread(*chbuf, sizeof(char), *size, file);
    fclose(file);
}