DEF_CMD(HLT, 0, 0, {
    return 0;
})

DEF_CMD(PUSH, 1, 1, {
    short _com = *(short*)(programm + ip);
    double _arg = 0;
    ip += sizeof(short);

    if (_com & (1 << REG_BIT)) {
        _arg += *(char*)(programm + ip);
        ip += sizeof(char);
    }
    if (_com & (1 << INU_BIT)) {
        _arg += *(double*)(programm + ip);
        ip  += sizeof(double); 
    } 
    if (_com & (1 << MEM_BIT)) {
        _arg = RAM[(int)round(_arg)]; /// !!!!!!!!!!!
    }

    PUSH(_arg);
})

DEF_CMD(POP, 2, 1, {
    short _com = *(short*)(programm + ip);
    ip += sizeof(short);

    if (_com & (1 << INU_BIT)) {
        printf("Segmentation fault\n");
        return 0;
    }
    if (_com & (1 << MEM_BIT)) {
        double _arg = 0;
        if (_com & (1 << REG_BIT)) {
            _arg += *(char*)(programm + ip);
            ip += sizeof(char);
        }
        if (_com & (1 << INU_BIT)) {
            _arg += *(double*)(programm + ip);
            ip  += sizeof(double); 
        }
        RAM[(int)round(_arg)] = POP;
    } else if (_com & (1 << REG_BIT)) {
        char _arg = -1;
        _arg += *(char*)(programm + ip);
        ip += sizeof(char);

        regist[_arg] = POP;
    }
})

DEF_CMD(JMP, 3, 1, {
    short _com = *(short*)(programm + ip);
    double _arg = 0;
    ip += sizeof(short);

    if (_com & (1 << REG_BIT)) {
        _arg += *(char*)(programm + ip);
        ip += sizeof(char);
    }
    if (_com & (1 << INU_BIT)) {
        _arg += *(double*)(programm + ip);
        ip  += sizeof(double); 
    } 
    if (_com & (1 << MEM_BIT)) {
        _arg = RAM[(int)round(_arg)];
    }

    ip = (int)round(_arg);
})

DEF_CMD(JB, 4, 1, {       
    short _com = *(short*)(programm + ip);
    double _arg = 0;
    ip += sizeof(short);

    if (_com & (1 << REG_BIT)) {
        _arg += *(char*)(programm + ip);
        ip += sizeof(char);
    }
    if (_com & (1 << INU_BIT)) {
        _arg += *(double*)(programm + ip);
        ip  += sizeof(double); 
    } 
    if (_com & (1 << MEM_BIT)) {
        _arg = RAM[(int)round(_arg)];
    }

    if (-POP + POP < -(1e-9)) ip = (int)round(_arg);
})

DEF_CMD(JBE, 5, 1, {       
    short _com = *(short*)(programm + ip);
    double _arg = 0;
    ip += sizeof(short);

    if (_com & (1 << REG_BIT)) {
        _arg += *(char*)(programm + ip);
        ip += sizeof(char);
    }
    if (_com & (1 << INU_BIT)) {
        _arg += *(double*)(programm + ip);
        ip  += sizeof(double); 
    } 
    if (_com & (1 << MEM_BIT)) {
        _arg = RAM[(int)round(_arg)];
    }

    if (-POP + POP < (1e-9)) ip = (int)round(_arg);
})

DEF_CMD(JA, 6, 1, {       
    short _com = *(short*)(programm + ip);
    double _arg = 0;
    ip += sizeof(short);

    if (_com & (1 << REG_BIT)) {
        _arg += *(char*)(programm + ip);
        ip += sizeof(char);
    }
    if (_com & (1 << INU_BIT)) {
        _arg += *(double*)(programm + ip);
        ip  += sizeof(double); 
    } 
    if (_com & (1 << MEM_BIT)) {
        _arg = RAM[(int)round(_arg)];
    }

    if (-POP + POP > (1e-9)) ip = (int)round(_arg);
})

DEF_CMD(JAE, 7, 1, {       
    short _com = *(short*)(programm + ip);
    double _arg = 0;
    ip += sizeof(short);

    if (_com & (1 << REG_BIT)) {
        _arg += *(char*)(programm + ip);
        ip += sizeof(char);
    }
    if (_com & (1 << INU_BIT)) {
        _arg += *(double*)(programm + ip);
        ip  += sizeof(double); 
    } 
    if (_com & (1 << MEM_BIT)) {
        _arg = RAM[(int)round(_arg)];
    }

    if (-POP + POP > -(1e-9)) ip = (int)round(_arg);
})

DEF_CMD(JE, 8, 1, {       
    short _com = *(short*)(programm + ip);
    double _arg = 0;
    ip += sizeof(short);

    if (_com & (1 << REG_BIT)) {
        _arg += *(char*)(programm + ip);
        ip += sizeof(char);
    }
    if (_com & (1 << INU_BIT)) {
        _arg += *(double*)(programm + ip);
        ip  += sizeof(double); 
    } 
    if (_com & (1 << MEM_BIT)) {
        _arg = RAM[(int)round(_arg)];
    }

    if (fabs(-POP + POP) < (1e-9)) ip = (int)round(_arg);
})

DEF_CMD(JNE, 9, 1, {       
    short _com = *(short*)(programm + ip);
    double _arg = 0;
    ip += sizeof(short);

    if (_com & (1 << REG_BIT)) {
        _arg += *(char*)(programm + ip);
        ip += sizeof(char);
    }
    if (_com & (1 << INU_BIT)) {
        _arg += *(double*)(programm + ip);
        ip  += sizeof(double); 
    } 
    if (_com & (1 << MEM_BIT)) {
        _arg = RAM[(int)round(_arg)];
    }

    if (fabs(-POP + POP) > (1e-9)) ip = (int)round(_arg);
})

DEF_CMD(CALL, 10, 1, { 
    short _com = *(short*)(programm + ip);
    double _arg = 0;
    ip += sizeof(short);

    if (_com & (1 << MEM_BIT)) {
        printf("Seg fault in CALL\n");
    }
    if (_com & (1 << REG_BIT)) {
        printf("Seg fault in CALL\n");
    }

    if (_com & (1 << INU_BIT)) {
        _arg += *(double*)(programm + ip);
        ip += sizeof(double);
    }

    Push(&callstack, ip);
    stackDump(callstack);
    ip = (int)round(_arg);
})

DEF_CMD(RET, 12, 0, {
    ip = round(Pop(&callstack));
})

DEF_CMD(DMP, 13, 0, {
    ip += sizeof(short);
    DMP;
})

DEF_CMD(IN, 14, 0, {
    ip += sizeof(short);
    double _buf;
    scanf("%lg", &_buf);
    PUSH(_buf);
})

DEF_CMD(OUT, 15, 0, {
    ip += sizeof(short);
    printf("%lg\n", POP);
})

DEF_CMD(ADD, 16, 0, {
    ip += sizeof(short);
    PUSH(POP + POP);
})

DEF_CMD(MUL, 17, 0, {
    ip += sizeof(short);
    PUSH(POP * POP);
})

DEF_CMD(DIV, 18, 0, {
    ip += sizeof(short);
    double a_ = POP;
    double b_ = POP;
    if (fabs(a_) < 1e-8) { /// change this
        printf("ERROR div 0\n");
        return 0;
    }             
    PUSH(b_ / a_);
})

DEF_CMD(SUB, 19, 0, {
    ip += sizeof(short);          
    PUSH(- POP + POP);
})

DEF_CMD(DUP, 20, 0, {   
    ip += sizeof(short);       
    double _buf = POP;
    PUSH(_buf);
    PUSH(_buf);
})

DEF_CMD(SQRT, 21, 0, {    
    ip += sizeof(short);      
    double _buf = POP;
    if (_buf < 0) {
        printf("sqrt below 0\n");
        return 0;
    }
    PUSH(sqrt(_buf));
})
