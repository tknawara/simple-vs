/**
 * File: stack-vm.h
 * Description: holder for interface of the vm
 * Created at: 2018-3-31
 */

#ifndef _HOME_TAREK_WORKSPACE_CPP_SIMPLE_VS_STACK_VM_STACK_VM_H
#define _HOME_TAREK_WORKSPACE_CPP_SIMPLE_VS_STACK_VM_STACK_VM_H

#include <glib.h>

enum instructions {
    HALT,  /* Halt execution*/
    PUSH,  /* Push on top of stack */
    POP,   /* Pop of the stack */
    GOTO,  /* Goto label */
    ADD,   /* Add two elements on top of stack */
    SUB,   /* Sub two elements on top of stack */
    MUL,   /* Mul two elements on top of stack */
    DIV,   /* Div two elements on top of stack */
    GT,    /* Check if element on top of stack is greater */
    LT,    /* Check if element on top of stack is smaller */
    EQ,    /* Check if element on top of stack is equal */
    GTE,   /* Check if element on top of stack is greater or equal */
    LTE,   /* Check if element on top of stack is less or equal */
    LABEL, /* Label found in the instructions */
};

/*
 * Run the loaded program.
 */
void run(void);

/*
 * Load the given program into vm memory.
 */
void load_program(GArray *prog);

#endif  // _HOME_TAREK_WORKSPACE_CPP_SIMPLE_VS_STACK_VM_STACK_VM_H
