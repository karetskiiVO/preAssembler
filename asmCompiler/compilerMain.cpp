#include "code.h"

int main () {
    formalLanguage::myasmCode test;
    test.loadFromSource("./test.asm");
    test.parse();
    test.print();

    return 0;
}

