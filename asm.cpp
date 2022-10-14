#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <math.h>
#include <string.h>

#include "asm.h"
#include "constants.h"

#define error(_line, _mess, _type) printf("%s ERROR in line %ld: %s\n", _type, _line, _mess)

#define CMD_LEN    50
#define LABLE_SIZE 50
#define LABLE_NUM  50

typedef struct {
    long pos;
    char name[LABLE_SIZE];
} lable;
int lablecnt = 0;
lable Lables[LABLE_NUM] = {0};

long findLable (const char* name) {
    for (int i = 0; i < lablecnt; i++) {
        if (strcmp(Lables[i].name, name)) {
            return Lables[i].pos;
        }
    }
    return -1;
}
void addLable  (long pos, const char* name) {
    bool isExist = false;

    for (int i = 0; i < lablecnt; i++) {
        if (strcmp(Lables[i].name, name)) {
            if (pos != Lables[i].pos) {
                error(0, "double defenitive lable", name);
            }
            return;
        }
    }

    strcpy(Lables[lablecnt].name, name);
    Lables[lablecnt].pos = pos;
    lablecnt++;
}

void ReadCode (const char* readfile, String** code, size_t* strcnt) {
    *strcnt = 1;
    static char* text = ""; //this array will be exist

    FILE* file = fopen(readfile, "r");
    assert(file != NULL && "file must exist");

    struct stat out = {0};
    assert((fstat(fileno(file), &out) != -1) && "Error in file");
    int textlen = round(out.st_size / sizeof(char));

    text = (char*)calloc(textlen, sizeof(char));

    fread(text, sizeof(char), textlen, file);
    fclose(file);
    
    for (int i = 0; i < strlen(text); i++) {
        if (text[i] == '\0' || text[i] == '\n') {
            text[i] = '\n';
            (*strcnt)++;
        }
    }

    *code = (String*)calloc(*strcnt, sizeof(String*));
    for (size_t i = 0; i < *strcnt; i++) {
        (*code)[i] = strtok((i == 0) ? text : NULL, "\n");
    }

    for (int i = 0; i < textlen; i++) {
        if (text[i] == ';' || text[i] == '\n') {
            text[i] = '\0';
        }
    }
}

void getArgs (char** ip, char* pos) {
    char* ipbuf = *ip;

    char reg[20];
    char lablech[LABLE_SIZE];
    char numreg = -1;
    double numbuf; ////change this

    char* buf1 = 0;
    char* buf2 = 0;
    buf1 = strchr(pos, '[');
    if (buf1) {
        buf2 = strchr(buf1, ']');
        if (!buf2) error(0, "incorrect argument", "SYNTAX");

        *buf1 = ' ';
        if (buf2) *buf2 = ' ';
        *((short*)*ip - 1) |= (1 << MEM_BIT);
    }
    
    if (sscanf(pos, "%lf+ %s", &numbuf, reg) == 2) {
        if (!strcmp(reg, "RAX")) numreg = RAX;
        if (!strcmp(reg, "RBX")) numreg = RBX;
        if (!strcmp(reg, "RCX")) numreg = RCX;
        if (!strcmp(reg, "RDX")) numreg = RDX;

        if (numreg == -1) error(0, "this is not a register", "SYNTAX");

        *((short*)*ip - 1) |= (1 << REG_BIT);
        *((short*)*ip - 1) |= (1 << INU_BIT);
        
        *(char*)ipbuf = numreg;
        ipbuf += sizeof(char);

        *(double*)ipbuf = numbuf;
        ipbuf += sizeof(double);
    }
    else if (sscanf(pos, " %s+ %s", lablech, reg) == 2) {
        numbuf = (double)findLable(lablech);

        if (!strcmp(reg, "RAX")) numreg = RAX;
        if (!strcmp(reg, "RBX")) numreg = RBX;
        if (!strcmp(reg, "RCX")) numreg = RCX;
        if (!strcmp(reg, "RDX")) numreg = RDX;

        if (numreg == -1) error(0, "this is not a register", "SYNTAX");

        *((short*)*ip - 1) |= (1 << REG_BIT);
        *((short*)*ip - 1) |= (1 << INU_BIT);
        
        *(char*)ipbuf = numreg;
        ipbuf += sizeof(char);

        *(double*)ipbuf = numbuf;
        ipbuf += sizeof(double);
    }
    else if (sscanf(pos, "%lf", &numbuf)) {
        *((short*)*ip - 1) |= (1 << INU_BIT);

        *(double*)ipbuf = numbuf;
        ipbuf += sizeof(double);
    } 
    else if (sscanf(pos, " %s"), lablech) {
        strcpy(reg, lablech);

        if (!strcmp(reg, "RAX")) numreg = RAX;
        if (!strcmp(reg, "RBX")) numreg = RBX;
        if (!strcmp(reg, "RCX")) numreg = RCX;
        if (!strcmp(reg, "RDX")) numreg = RDX;
        
        if (numreg != -1) {
            *((short*)(*ip) - 1) |= (1 << REG_BIT);
        
            *(char*)ipbuf = numreg;
            ipbuf += sizeof(char);
        } else {
            numbuf = (double)findLable(lablech);
            *((short*)(*ip) - 1) |= (1 << INU_BIT);

            *(double*)ipbuf = numbuf;
            ipbuf += sizeof(double);
        }
    } else {
        error(0, "incorrect argument", "SYNTAX");
    }
    
    *ip = ipbuf;

    if (buf1) *buf1 = '[';
    if (buf2) *buf2 = ']';
}

#define DEF_CMD(_name, _num, _arg, ...) \
else if (strcmp(cmd, #_name) == 0) {                            \
    *(short*)ip = _num;                                         \
    ip += sizeof(short);                                        \
    if (_arg) getArgs(&ip, strstr(code[i], cmd) + strlen(cmd));               \
}

void Compile (String* code, size_t strcnt, char* bincode) {
    char* ip = bincode;
    char* ipbuf = ip;

    for (size_t i = 0; i < strcnt; i++) { //////// make i global
        if (!code[i]) continue;

        char cmd[CMD_LEN] = "";
        sscanf(code[i], "%s", cmd);

        //printf("%d/%d\t%s\n", i + 1, strcnt, cmd);

        if (cmd[strlen(cmd) - 1] == ':') {
            char cmdbuf[CMD_LEN] = "";
            strncpy(cmdbuf, cmd, strlen(cmd) - 1);
            addLable(ip - bincode, cmd);
        }
        #include "comands.h"
        else {
            error(i, "no such command", "SYNTAX");
        }
        printf("%p\n", ip);
    }

    //printf("COMPILATION COMPLICATED\n");
}

#undef DEF_CMD










