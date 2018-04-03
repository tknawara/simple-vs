/*
 * File: command.c
 * Description: holder for the logic of interpreting
                assembler instructions.
 * Created at: 2018-4-3
 */

#include <stdio.h>
#include "command.h"

/*
  Instruction format
  opcode: 6 bits
  data:   26 bits

  instruction opcode :
  0 -> halt
  1 -> push <data>
  2 -> pop
  3 -> goto <disp>
  4 -> add
  5 -> sub
  6 -> mul
  7 -> div

 */

#define HALT 0x00000000
#define PUSH 0x04000000
#define POP  0x08000000
#define GOTO 0x0c000000
#define ADD  0x10000000
#define SUB  0x14000000
#define MUL  0x18000000
#define DIV  0x1c000000

#define VALUE_LEN 26
#define VALUE_MASK 0x01ffffff

static FILE *f;

void init(void) {
  f = fopen("out.bin", "w");
}

void encode_push(const int value) {
  printf("[interpreter]  encoding push command with value=%d\n", value);
  int sign = value < 0 ? 1 : 0;
  int instruction = VALUE_MASK & value;
  if (sign) {
    instruction = instruction | (1 << VALUE_LEN);
  }
  instruction = instruction | PUSH;
  fprintf(f, "%d\n", instruction);
}

void encode_pop(void) {
  puts("[interpreter]  encoding pop");
  fprintf(f, "%d\n", POP);
}

void encode_goto(const char *label) {
  printf("[interpreter]  encoding goto with label=%s\n", label);
  // TODO support two passes
  fprintf(f, "%d\n", GOTO);
}

void encode_mul(void) {
  puts("[interpreter]  encoding multiply");
  fprintf(f, "%d\n", MUL);
}

void encode_add(void) {
  puts("[interpreter]  encoding add");
  fprintf(f, "%d\n", ADD);
}


void encode_div(void) {
  puts("[interpreter]  encoding division");
  fprintf(f, "%d\n", DIV);
}

void encode_sub(void) {
  puts("[interpreter]  encoding subtraction");
  fprintf(f, "%d\n", SUB);
}

void encode_halt(void) {
  puts("[interpreter]  encoding halt");
  fprintf(f, "%d\n", HALT);
}
