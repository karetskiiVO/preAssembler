DEF_CMD(HLT, 0, 0, {
    return 0;
})

DEF_CMD(PUSH, 1, 1, {
    ip += 2;                                    //////////change for const
    PUSH(*(double*)(programm + ip));            /////////////may be some shit
    ip += sizeof(double);
})

DEF_CMD(POP, 2, 1, {
    ///
})

DEF_CMD(JMP, 3, 0, {                        ////////////change
    ip += 2;
    //ip = round();
})

DEF_CMD(DMP, 13, 0, {
    ip += 2;
    DMP;
})

DEF_CMD(IN, 14, 0, {
    ip += 2;
    double _buf;
    scanf("%lg", &_buf);
    PUSH(_buf);
})

DEF_CMD(OUT, 15, 0, {
    ip += 2;
    printf("%lg\n", POP);
})

DEF_CMD(ADD, 16, 0, {
    ip += 2;
    PUSH(POP + POP);
})

DEF_CMD(MUL, 17, 0, {
    ip += 2;
    PUSH(POP * POP);
})

DEF_CMD(DIV, 18, 0, {
    ip += 2;
    double a_ = POP;
    double b_ = POP;
    if (fabs(a_) < 1e-8) { /// change this
        printf("ERROR div 0\n");
        return 0;
    }             
    PUSH(b_ / a_);
})

DEF_CMD(SUB, 19, 0, {
    ip += 2;          
    PUSH(- POP + POP);
})

DEF_CMD(DUP, 20, 0, {   
    ip += 2;       
    double _buf = POP;
    PUSH(_buf);
    PUSH(_buf);
})

DEF_CMD(SQRT, 21, 0, {    
    ip += 2;      
    double _buf = POP;
    if (_buf < 0) {
        printf("sqrt below 0\n");
        return 0;
    }
    PUSH(sqrt(_buf));
})









