#the compiler
CC := g++
 
#flags:
CFLAGS  := -g -Wall
 
#sources of input
SOURCES_ASM := ./asmCompiler/compilerMain.cpp ./asmCompiler/code.cpp ./asmCompiler/myasmCode.cpp
#SOURCES_CPU := 

#sources of output
EXECUTABLE_ASM := asm
EXECUTABLE_CPU := cpu

all:
	$(CC) $(SOURCES_ASM) $(CFLAGS) -MD -o $(EXECUTABLE_ASM) -lm
#	$(CC) $(SOURCES_CPU) $(CFLAGS) -MD -o $(EXECUTABLE_CPU) -lm