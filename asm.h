#ifndef ASM
#define ASM

typedef char* String;

void Compile (String* code, size_t strcnt, char* bincode);

void ReadCode (const char* readfile, String** code, size_t* strcnt);

#endif