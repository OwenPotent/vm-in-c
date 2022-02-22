#ifndef VM_H
#define VM_H

// Include header files used to make a vm
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


// Define the VM struct
typedef struct {
    int pc;
    int sp;
    int r[8];
    int mem[256];
    int labels[256];
} VM;


// Function prototypes
void vm_init(VM *vm);
void vm_execute(VM *vm);
void vm_print_registers(VM *vm);
void vm_print_stack(VM *vm);
void vm_print_memory(VM *vm);
void vm_print_labels(VM *vm);
void vm_print_opcode(VM *vm, int opcode);

#endif
