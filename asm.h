#ifndef ASM
#define ASM

#include <stdbool.h>

typedef char* String;

void Compile (String* code, size_t strcnt, char* bincode, bool findErrors);

void readCode (const char* readfile, String** code, size_t* strcnt);

void printCode (const char* printFile, char* bincode, size_t ipcnt);

#endif