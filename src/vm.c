#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <sys/types.h>
#include "vm.h"
#include "vmop.h"
#include "utils.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// Function prototypes
void vm_init(VM *vm)
{
    vm->pc = 0;
    vm->sp = 0;
    for (int i = 0; i < 8; i++) {
        vm->r[i] = 0;
    }
    for (int i = 0; i < 256; i++) {
        vm->mem[i] = 0;
    }
    for (int i = 0; i < 256; i++) {
        vm->labels[i] = 0;
    }
}

void vm_print_registers(VM *vm)
{
    printf("PC: %d SP: %d\n", vm->pc, vm->sp);
    for (int i = 0; i < 8; i++) {
        printf("R%d: %d\n", i, vm->r[i]);
    }
}

void vm_print_stack(VM *vm)
{
    printf("SP: %d\n", vm->sp);
    for (int i = 0; i < vm->sp; i++) {
        printf("%d ", vm->r[i]);
    }
    printf("\n");
}
void vm_print_memory(VM *vm)
{
    for (int i = 0; i < 256; i++) {
        printf("%d ", vm->mem[i]);
    }
    printf("\n");
}
void vm_print_labels(VM *vm)
{
    for (int i = 0; i < 256; i++) {
        printf("%d ", vm->labels[i]);
    }
    printf("\n");
}
void vm_print_opcode(VM *vm, int opcode)
{
    switch (opcode) {
        case VMOP_NOP:
            printf("NOP\n");
            break;
        case VMOP_HALT:
            printf("HALT\n");
            break;
        case VMOP_PUSH:
            printf("PUSH\n");
            break;
        case VMOP_POP:
            printf("POP\n");
            break;
        case VMOP_ADD:
            printf("ADD\n");
            break;
        case VMOP_SUB:
            printf("SUB\n");
            break;
        case VMOP_MUL:
            printf("MUL\n");
            break;
        case VMOP_DIV:
            printf("DIV\n");
            break;
        case VMOP_MOD:
            printf("MOD\n");
            break;
        case VMOP_CMP:
            printf("CMP\n");
            break;
        case VMOP_JMP:
            printf("JMP\n");
            break;
        case VMOP_JE:
            printf("JE\n");
            break;
        case VMOP_JNE:
            printf("JNE\n");
            break;
        case VMOP_JL:
            printf("JL\n");
            break;
        case VMOP_JLE:
            printf("JLE\n");
            break;
        case VMOP_JG:
            printf("JG\n");
            break;
        case VMOP_JGE:
            printf("JGE\n");
            break;
        case VMOP_CALL:
            printf("CALL\n");
            break;
        case VMOP_RET:
            printf("RET\n");
            break;
        case VMOP_PRINT:
            printf("PRINT\n");
            break;
        case VMOP_READ:
            printf("READ\n");
            break;
        case VMOP_LABEL:
            printf("LABEL\n");
            break;
        default:
            printf("Unknown opcode: %d\n", opcode);
            break;
    }
}
// Create a vm_parse function that takes a string and returns a VM struct
// with the correct opcodes and data.
VM *vm_parse(char *str)
{
    VM *vm = malloc(sizeof(VM));
    vm->pc = 0;
    vm->sp = 0;
    for (int i = 0; i < 8; i++) {
        vm->r[i] = 0;
    }
    for (int i = 0; i < 256; i++) {
        vm->mem[i] = 0;
    }
    for (int i = 0; i < 256; i++) {
        vm->labels[i] = 0;
    }
    char *token = strtok(str, " ");
    while (token != NULL) {
        if (strcmp(token, "NOP") == 0) {
            vm->mem[vm->pc] = VMOP_NOP;
            vm->pc++;
        } else if (strcmp(token, "HALT") == 0) {
            vm->mem[vm->pc] = VMOP_HALT;
            vm->pc++;
        } else if (strcmp(token, "PUSH") == 0) {
            vm->mem[vm->pc] = VMOP_PUSH;
            vm->pc++;
        } else if (strcmp(token, "POP") == 0) {
            vm->mem[vm->pc] = VMOP_POP;
            vm->pc++;
        } else if (strcmp(token, "ADD") == 0) {
            vm->mem[vm->pc] = VMOP_ADD;
            vm->pc++;
        } else if (strcmp(token, "SUB") == 0) {
            vm->mem[vm->pc] = VMOP_SUB;
            vm->pc++;
        } else if (strcmp(token, "MUL") == 0) {
            vm->mem[vm->pc] = VMOP_MUL;
            vm->pc++;
        } else if (strcmp(token, "DIV") == 0) {
            vm->mem[vm->pc] = VMOP_DIV;
            vm->pc++;
        } else if (strcmp(token, "MOD") == 0) {
            vm->mem[vm->pc] = VMOP_MOD;
            vm->pc++;
        } else if (strcmp(token, "CMP") == 0) {
            vm->mem[vm->pc] = VMOP_CMP;
            vm->pc++;
        } else if (strcmp(token, "JMP") == 0) {
            vm->mem[vm->pc] = VMOP_JMP;
            vm->pc++;
        } else if (strcmp(token, "JE") == 0) {
            vm->mem[vm->pc] = VMOP_JE;
            vm->pc++;
        } else if (strcmp(token, "JNE") == 0) {
            vm->mem[vm->pc] = VMOP_JNE;
            vm->pc++;
        } else if (strcmp(token, "JL") == 0) {
            vm->mem[vm->pc] = VMOP_JL;
            vm->pc++;
        } else if (strcmp(token, "JLE") == 0) {
            vm->mem[vm->pc] = VMOP_JLE;
            vm->pc++;
        } else if (strcmp(token, "JG") == 0) {
            vm->mem[vm->pc] = VMOP_JG;
            vm->pc++;
        } else if (strcmp(token, "JGE") == 0) {
            vm->mem[vm->pc] = VMOP_JGE;
            vm->pc++;
        } else if (strcmp(token, "CALL") == 0) {
            vm->mem[vm->pc] = VMOP_CALL;
            vm->pc++;
        } else if (strcmp(token, "RET") == 0) {
            vm->mem[vm->pc] = VMOP_RET;
            vm->pc++;
        } else if (strcmp(token, "PRINT") == 0) {
            vm->mem[vm->pc] = VMOP_PRINT;
            vm->pc++;
        } else if (strcmp(token, "READ") == 0) {
            vm->mem[vm->pc] = VMOP_READ;
            vm->pc++;
        } else if (strcmp(token, "LABEL") == 0) {
            vm->mem[vm->pc] = VMOP_LABEL;
            vm->pc++;
        } else if (strcmp(token, ":") == 0) {
            token = strtok(NULL, " ");
            vm->labels[vm->pc] = token;
        } else {
            vm->mem[vm->pc] = atoi(token);
            vm->pc++;
        }
        token = strtok(NULL, " ");
    }
    return vm;
}

void vm_execute(VM *vm)
{
    while (vm->mem[vm->pc] != VMOP_HALT) {
        vm_print_opcode(vm->mem[vm->pc], vm);
        switch (vm->mem[vm->pc]) {
            case VMOP_NOP:
                vm->pc++;
                break;
            case VMOP_HALT:
                break;
            case VMOP_PUSH:
                vm->sp++;
                vm->r[vm->sp] = vm->mem[vm->pc + 1];
                vm->pc += 2;
                break;
            case VMOP_POP:
                vm->r[vm->sp] = 0;
                vm->sp--;
                vm->pc++;
                break;
            case VMOP_ADD:
                vm->r[vm->sp - 1] += vm->r[vm->sp];
                vm->sp--;
                vm->pc++;
                break;
            case VMOP_SUB:
                vm->r[vm->sp - 1] -= vm->r[vm->sp];
                vm->sp--;
                vm->pc++;
                break;
            case VMOP_MUL:
                vm->r[vm->sp - 1] *= vm->r[vm->sp];
                vm->sp--;
                vm->pc++;
                break;
            case VMOP_DIV:
                vm->r[vm->sp - 1] /= vm->r[vm->sp];
                vm->sp--;
                vm->pc++;
                break;
            case VMOP_MOD:
                vm->r[vm->sp - 1] %= vm->r[vm->sp];
                vm->sp--;
                vm->pc++;
                break;
            case VMOP_CMP:
                if (vm->r[vm->sp - 1] == vm->r[vm->sp]) {
                    vm->r[vm->sp - 1] = 1;
                } else {
                    vm->r[vm->sp - 1] = 0;
                }
                vm->sp--;
                vm->pc++;
                break;
            case VMOP_JMP:
                vm->pc = vm->mem[vm->pc + 1];
                break;
            case VMOP_JE:
                if (vm->r[vm->sp - 1] == 1) {
                    vm->pc = vm->mem[vm->pc + 1];
                } else {
                    vm->pc += 2;
                }
                vm->sp--;
                break;
            case VMOP_JNE:
                if (vm->r[vm->sp - 1] == 0) {
                    vm->pc = vm->mem[vm->pc + 1];
                } else {
                    vm->pc += 2;
                }
                vm->sp--;
                break;
            case VMOP_JL:
                if (vm->r[vm->sp - 1] < vm->r[vm->sp]) {
                    vm->pc = vm->mem[vm->pc + 1];
                } else {
                    vm->pc += 2;
                }
                vm->sp--;
                break;
            case VMOP_JLE:
                if (vm->r[vm->sp - 1] <= vm->r[vm->sp]) {
                    vm->pc = vm->mem[vm->pc + 1];
                } else {
                    vm->pc += 2;
                }
                vm->sp--;
                break;
            case VMOP_JG:
                if (vm->r[vm->sp - 1] > vm->r[vm->sp]) {
                    vm->pc = vm->mem[vm->pc + 1];
                } else {
                    vm->pc += 2;
                }
                vm->sp--;
                break;
            case VMOP_JGE:
                if (vm->r[vm->sp - 1] >= vm->r[vm->sp]) {
                    vm->pc = vm->mem[vm->pc + 1];
                } else {
                    vm->pc += 2;
                }
                vm->sp--;
                break;
            case VMOP_CALL:
                vm->r[vm->sp + 1] = vm->pc + 2;
                vm->sp++;
                vm->pc = vm->mem[vm->pc + 1];
                break;
            case VMOP_RET:
                vm->pc = vm->r[vm->sp];
                vm->sp--;
                break;
            case VMOP_PRINT:
                printf("%d\n", vm->r[vm->sp]);
                vm->sp--;
                vm->pc++;
                break;
            case VMOP_READ:
                scanf("%d", &vm->r[vm->sp]);
                vm->sp++;
                vm->pc++;
                break;
            case VMOP_LABEL:
                vm->pc++;
                break;
            default:
                vm->r[vm->sp] = vm->mem[vm->pc];
                vm->sp++;
                vm->pc++;
                break;
        }
    }
}

// Create a vm_free function
void vm_free(VM *vm)
{
    free(vm);
}

// Main function
int main(int argc, char *argv[]) {
    // Check arguments
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Check if file extension is .elbavm
    char* extension = strrchr(argv[1], '.');
    if (extension == NULL || strcmp(extension, ".elbavm") != 0) {
        printf("File extension must be .elbavm\n");
        return 1;
    }

    // Read file
    char* buffer = read_file(argv[1]);

    // Parse file
    VM* vm = vm_parse(buffer);

    // Execute file
    vm_execute(vm);

    // Print registers
    vm_print_registers(vm);

    // Print stack
    vm_print_stack(vm);

    // Print memory
    vm_print_memory(vm);

    // Print labels
    vm_print_labels(vm);

    // Free VM
    vm_free(vm);

    // Free buffer
    free(buffer);

    return 0;
}

// How to use
/*
    1. Create a file with the following contents:
        NOP
        HALT
        PUSH 1
        PUSH 2
        ADD
        PRINT
        READ
        JMP LABEL1
        LABEL1:
        PUSH 3
        SUB
        PRINT
        HALT
    2. Run the program with the following command:
        ./vm <filename>
    3. The output should be:
        PC: 0 SP: 0
        R0: 0
        R1: 0
        R2: 0
        R3: 0
        R4: 0
        R5: 0
        R6: 0
        R7: 0
        SP: 2
        1 2 3
        PC: 1 SP: 2
        R0: 0
        R1: 0
        R2: 0
        R3: 0
        R4: 0
        R5: 0
        R6: 0
        R7: 0
        SP: 2
        1 2 3
        PC: 2 SP: 2
        R0: 0
        R1: 0
        R2: 0
        R3: 0
        R4: 0
        R5: 0
        R6: 0
        R7: 0
        SP: 2
        1 2 3
        PC: 3 SP: 2
        R0: 0
        R1: 0
        R2: 0
        R3: 0
        R4: 0
        R5: 0
        R6: 0
        R7: 0
        SP: 2
        1 2 3
        PC: 4 SP: 2
        R0: 0
        R1: 0
        R2: 0
        R3: 0
        R4: 0
        R5: 0
        R6: 0
        R7: 0
        SP: 2
        1 2 3
        PC: 5 SP: 2
        R0: 0
        R1: 0
        R2: 0
        R3: 0
        R4: 0
        R5: 0
        R6: 0
        R7: 0
        SP: 2
        1 2 3
        PC: 6 SP: 2
        R0: 0
        R1: 0
        R2: 0
        R3: 0
        R4: 0
        R5: 0
        R6: 0
        R7: 0
        and so on...
*/