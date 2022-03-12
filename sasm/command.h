#ifndef _HOME_TAREK_WORKSPACE_CPP_SIMPLE_VS_SASM_COMMAND_H
#define _HOME_TAREK_WORKSPACE_CPP_SIMPLE_VS_SASM_COMMAND_H

/*
 * File: command.h
 * Description: responsible for assembler translation
 * Created at: 2018-4-3
 */

struct label_record {
    char label[100];
    int loc;
} __attribute__((aligned(128)));

enum instruction {
    HALT = 0x00000000, /* Halt execution*/
    PUSH = 0x04000000, /* Push on top of stack */
    POP = 0x08000000,  /* Pop of the stack */
    GOTO = 0x0c000000, /* Goto label */
    ADD = 0x10000000,  /* Add two elements on top of stack */
    SUB = 0x14000000,  /* Sub two elements on top of stack */
    MUL = 0x18000000,  /* Mul two elements on top of stack */
    DIV = 0x1c000000,  /* Div two elements on top of stack */
    GT = 0x20000000,   /* Check if element on top of stack is greater */
    LT = 0x24000000,   /* Check if element on top of stack is smaller */
    EQ = 0x28000000,   /* Check if element on top of stack is equal */
    GTE = 0x2c000000, /* Check if element on top of stack is greater or equal */
    LTE = 0x30000000, /* Check if element on top of stack is less or equal */
    LABEL = 0x34000000, /* Label found in the instructions */
};

/*
 * initialize the output file.
 */
void init(void);

/*
 * clean up all the allocated memory.
 */
void destroy_command(void);

/*
 * return 1 if running in pass two.
 */
int pass_two(void);

/*
 * increment the location of the program.
 */
void increment_loc(void);

/*
 * increment number of passes.
 */
void increment_pass(void);

/*
 * add the label to the list of defined labels.
 */
void add_label(char *label);

/*
 * encode the push instruction.
 */
void encode_push(int value);

/*
 * encode pop instruction
 */
void encode_pop(void);

/*
 * encode goto instruction
 */
void encode_goto(char *label);

/*
 * encode the existence of the label.
 */
void encode_label(void);

/*
 * encode halt instruction.
 */
void encode_halt(void);

/*
 * encode the addition instruction.
 */
void encode_mul(void);

/*
 * encode the subtraction instruction.
 */
void encode_add(void);

/*
 * encode the division instruction.
 */
void encode_div(void);

/*
 * encode the subtraction instruction.
 */
void encode_sub(void);

/*
 * encode less than instruction.
 */
void encode_lt(void);

/*
 * encode less than or equal.
 */
void encode_lte(void);

/*
 * encode greater than instruction.
 */
void encode_gt(void);

/*
 * encode less than or equal.
 */
void encode_gte(void);

/*
 * encode equal instruction.
 */
void encode_eq(void);

#endif
