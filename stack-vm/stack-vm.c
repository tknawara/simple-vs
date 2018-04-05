/*
 * File: stack-vm.cpp
 * Description: holder for vm logic implementation
 * Created at: 2018-3-31
 */

#include "stack-vm.h"

#define OPCODE_SHIFT 26
#define DATA_MASK 0x01ffffff

static int32_t pc = 100;
static int32_t sp = 0;
static uint32_t memory[VM_MEMORY_SIZE];
static int32_t running = TRUE;

/*
 * Extract the opcode from the instruction.
 */
static uint32_t get_opcode(uint32_t instruction)
{
  uint32_t opcode = instruction >> OPCODE_SHIFT;
  printf("[stack-vm]  opcode=%d\n", opcode);
  return opcode;
}

/*
 * Extract data from the instruction.
 */
static uint32_t get_data(uint32_t instruction)
{
  int sign = (instruction >> (OPCODE_SHIFT - 1)) & 1;
  uint32_t data = (instruction & DATA_MASK);
  if (sign) {
    data *= -1;
  }
  printf("[stack-vm]  data=%d\n", data);
  return data;
}

/*
 * Fetch the next instruction.
 */
static void fetch() { ++pc; }

/*
 * Execute the halt instruction.
 */
static void execute_halt()
{
  puts("halt");
  running = FALSE;
}

/*
 * Execute the push instruction.
 */
static void execute_push(uint32_t data)
{
  printf("[stack-vm]  pushing value=%d, on top of stack\n", data);
  ++sp;
  memory[sp] = data;
}

/*
 * Execute the pop instruction.
 */
static void execute_pop(void)
{
  printf("[stack-vm]  pop value=%d, on top of the stack\n", memory[sp]);
  --sp;
}

/*
 * Execute the goto instruction.
 */
static void execute_goto(uint32_t data)
{
  printf("[stack-vm] goto displacement=%d\n", data);
  pc += data;
}

/*
 * Execute the add instruction.
 */
static void execute_add(void)
{
  printf("[stack-vm] adding, %d %d\n", memory[sp - 1], memory[sp]);
  memory[sp - 1] += memory[sp];
  --sp;
}

/*
 * Execute the sub instruction.
 */
static void execute_sub(void)
{
  printf("[stack-vm] subtracting, %d %d\n", memory[sp - 1], memory[sp]);
  memory[sp - 1] -= memory[sp];
  --sp;
}

/*
 * Execute the multiplication instruction.
 */
static void execute_mul(void)
{
  printf("[stack-vm] multiplying, %d %d\n", memory[sp - 1], memory[sp]);
  memory[sp - 1] *= memory[sp];
  --sp;
}

/*
 * Execute the division instruction.
 */
static void execute_div(void)
{
  printf("[stack-vm] dividing, %d %d\n", memory[sp - 1], memory[sp]);
  memory[sp - 1] /= memory[sp];
  --sp;
}

/*
 * Execute the greater than instruction.
 */
static void execute_gt(void)
{
  printf("[stack-vm] GT comparing, %d %d\n", memory[sp - 1], memory[sp]);
  if (memory[sp] <= memory[sp - 1]) {
    ++pc;
  }
}

/*
 * Execute the greater than or equal instruction.
 */
static void execute_gte(void)
{
  printf("[stack-vm] GT comparing, %d %d\n", memory[sp - 1], memory[sp]);
  if (memory[sp] < memory[sp - 1]) {
    ++pc;
  }
}

/*
 * Execute the less than instruction.
 */
static void execute_lt(void)
{
  printf("[stack-vm] LT comparing, %d %d\n", memory[sp - 1], memory[sp]);
  if (memory[sp] >= memory[sp - 1]) {
    ++pc;
  }
}

/*
 * Execute the less than or equal instruction.
 */
static void execute_lte(void)
{
  printf("[stack-vm] LTE comparing, %d %d\n", memory[sp - 1], memory[sp]);
  if (memory[sp] > memory[sp - 1]) {
    ++pc;
  }
}

/*
 * Execute the equals instruction.
 */
static void execute_eq(void)
{
  printf("[stack-vm] EQ comparing, %d %d\n", memory[sp - 1], memory[sp]);
  if (memory[sp] != memory[sp - 1]) {
    ++pc;
  }
}

/*
 * Handle label instruction.
 */
static void execute_label(void)
{
  printf("[stack-vm] label found\n");
}

/*
 * Executing any instruction supported
 * by the vm.
 */
static void execute_instruction(void)
{
  printf("[stack-vm]  instruction=%d\n", memory[pc]);
  uint32_t opcode = get_opcode(memory[pc]);
  int32_t data = get_data(memory[pc]);
  switch (opcode) {
  case HALT:
    execute_halt();
    break;
  case PUSH:
    execute_push(data);
    break;
  case POP:
    execute_pop();
    break;
  case GOTO:
    execute_goto(data);
    break;
  case ADD:
    execute_add();
    break;
  case SUB:
    execute_sub();
    break;
  case MUL:
    execute_mul();
    break;
  case DIV:
    execute_div();
    break;
  case GT:
    execute_gt();
    break;
  case LT:
    execute_lt();
    break;
  case EQ:
    execute_eq();
    break;
  case GTE:
    execute_gte();
    break;
  case LTE:
    execute_lte();
    break;
  case LABEL:
    execute_label();
    break;
  default:
    puts("Unsupported operation");
  }
}

void run(void)
{
  --pc;
  while (running) {
    fetch();
    execute_instruction();
    printf("tos: %d\n", memory[sp]);
  }
}

void load_program(GArray *prog)
{
  for (size_t i = 0; i < prog->len; ++i) {
    memory[pc + i] = g_array_index(prog, uint32_t, i);
  }
}

