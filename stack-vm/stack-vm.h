/*
 * File: stack-vm.h
 * Description: holder for interface of the vm
 * Created at: 2018-3-31
 */

#ifndef STACK_VM_H
#define STACK_VM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <glib.h>

#define VM_MEMORY_SIZE 1000000

enum instructions {
  HALT,           /* Halt execution*/
  PUSH,           /* Push on top of stack */
  POP,            /* Pop of the stack */
  GOTO,           /* Goto label */
  ADD,            /* Add two elements on top of stack */
  SUB,            /* Sub two elements on top of stack */
  MUL,            /* Mul two elements on top of stack */
  DIV,            /* Div two elements on top of stack */
  GT,             /* Check if element on top of stack is greater */
  LT,             /* Check if element on top of stack is smaller */
  EQ,             /* Check if element on top of stack is equal */
  GTE,            /* Check if element on top of stack is greater or equal */
  LTE,            /* Check if element on top of stack is less or equal */
  LABEL,          /* Label found in the instructions */
};

/*
 * Run the loaded program.
 */
void run(void);

/*
 * Load the given program into vm memory.
 */
void load_program(GArray *prog);

#endif // STACK_VM_H
