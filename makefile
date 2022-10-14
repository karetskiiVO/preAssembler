#the compiler
CC := g++
 
#flags:
CFLAGS  := -g -Wall
 
#sources of input
SOURCES_ASM := asm_main.cpp  asm.cpp
SOURCES_CPU := cpu_main.cpp  cpu.cpp  cstack.cpp

#sources of output
EXECUTABLE_ASM := asm
EXECUTABLE_CPU := cpu

all:
	$(CC) $(SOURCES_ASM) $(CFLAGS) -MD -o $(EXECUTABLE_ASM) -lm
	$(CC) $(SOURCES_CPU) $(CFLAGS) -MD -o $(EXECUTABLE_CPU) -lm