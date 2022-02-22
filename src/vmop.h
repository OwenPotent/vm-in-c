#ifndef VMOP_H
#define VMOP_H

// Define the VMOP enum
enum VMOP {
    VMOP_NOP,
    VMOP_HALT,
    VMOP_PUSH,
    VMOP_POP,
    VMOP_ADD,
    VMOP_SUB,
    VMOP_MUL,
    VMOP_DIV,
    VMOP_MOD,
    VMOP_CMP,
    VMOP_JMP,
    VMOP_JE,
    VMOP_JNE,
    VMOP_JL,
    VMOP_JLE,
    VMOP_JG,
    VMOP_JGE,
    VMOP_CALL,
    VMOP_RET,
    VMOP_PRINT,
    VMOP_READ,
    VMOP_LABEL,
    VMOP_COUNT
};

#endif