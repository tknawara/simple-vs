/*
 * File: command.c
 * Description: holder for the logic of interpreting
                assembler instructions.
 * Created at: 2018-4-3
 */

#include <stdio.h>
#include <ctype.h>
#include <math.h>

#include "command.h"
#include "data/list.h"

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

#define HALT  0x00000000
#define PUSH  0x04000000
#define POP   0x08000000
#define GOTO  0x0c000000
#define ADD   0x10000000
#define SUB   0x14000000
#define MUL   0x18000000
#define DIV   0x1c000000
#define GT    0x20000000
#define LT    0x24000000
#define EQ    0x28000000
#define GTE   0x2c000000
#define LTE   0x30000000
#define LABEL 0x34000000

#define VALUE_LEN 25
#define VALUE_MASK 0x01ffffff

static FILE *f;
static int loc;
static int num_of_passes;
static struct l_node *list = NULL;

static void initialize_label_record(struct label_record **record, char *label) {
  *record = malloc(sizeof(struct label_record));
  strcpy((*record)->label, label);
  (*record)->loc = loc;
}

static int get_label_loc(char *label) {
  for (int i = 0; i < size(list); ++i) {
    struct label_record *label_record_ptr = (struct label_record *) get(list, i);
    if (strcmp(label, label_record_ptr->label) == 0) {
      return label_record_ptr->loc;
    }
  }
  printf("[interpreter]  error couldn't find location of label=%s\n", label);
  return -1;
}

void init(void) {
  f = fopen("out.bin", "w");
  loc = 0;
  num_of_passes = 0;
}

void destroy_command(void) {
  destroy_list(list);
}

int pass_two(void) {
  return num_of_passes > 0;
}

void increment_loc(void) {
  ++loc;
}

void increment_pass(void) {
  puts("[interpreter]  printing all the labels.");
  for (int i = 0; i < size(list); ++i) {
    struct label_record *label_record_ptr = (struct label_record *) get(list, i);
    printf("label=%s, loc=%d\n", label_record_ptr->label, label_record_ptr->loc);
  }
  puts("");
  ++num_of_passes;
  loc = 0;
}

void add_label(char *label) {
  printf("[interpreter]  adding_label=%s\n", label);
  struct label_record *label_record_ptr = NULL;
  initialize_label_record(&label_record_ptr, label);
  add(&list, label_record_ptr, sizeof(struct label_record));
}

static unsigned int encode_instruction_data(int value, int opcode) {
  int sign = value < 0 ? 1 : 0;
  value = abs(value);
  unsigned int instruction = VALUE_MASK & value;
  if (sign) {
    instruction = instruction | (1 << VALUE_LEN);
  }
  instruction = instruction | opcode;
  return instruction;
}

void encode_push(int value) {
  printf("[interpreter]  encoding push command with value=%d\n", value);
  int instruction = encode_instruction_data(value, PUSH);
  fprintf(f, "%u\n", instruction);
}

void encode_pop(void) {
  puts("[interpreter]  encoding pop");
  fprintf(f, "%u\n", POP);
}

void encode_goto(char *label) {
  for (int i = 0; label[i]; ++i) {
    label[i] = tolower(label[i]);
  }
  printf("[interpreter]  encoding goto with label=%s\n", label);
  int label_loc = get_label_loc(label);
  int disp = label_loc - loc;
  int instruction = encode_instruction_data(disp, GOTO);
  fprintf(f, "%u\n", instruction);
}

void encode_mul(void) {
  puts("[interpreter]  encoding multiply");
  fprintf(f, "%u\n", MUL);
}

void encode_add(void) {
  puts("[interpreter]  encoding add");
  fprintf(f, "%u\n", ADD);
}

void encode_label(void) {
  puts("[interpreter] encoding label");
  fprintf(f, "%u\n", LABEL);
}

void encode_div(void) {
  puts("[interpreter]  encoding division");
  fprintf(f, "%u\n", DIV);
}

void encode_sub(void) {
  puts("[interpreter]  encoding subtraction");
  fprintf(f, "%u\n", SUB);
}

void encode_halt(void) {
  puts("[interpreter]  encoding halt");
  fprintf(f, "%u\n", HALT);
}

void encode_lt(void) {
  puts("[interpreter]  encoding LT");
  fprintf(f, "%u\n", LT);
}

void encode_lte(void) {
  puts("[interpreter]  encoding LTE");
  fprintf(f, "%u\n", LTE);
}

void encode_gt(void) {
  puts("[interpreter]  encoding GT");
  fprintf(f, "%u\n", GT);
}

void encode_gte(void) {
  puts("[interpreter]  encoding GTE");
  fprintf(f, "%u\n", GTE);
}

void encode_eq(void) {
  puts("[interpreter]  encoding EQ");
  fprintf(f, "%u\n", EQ);
}
