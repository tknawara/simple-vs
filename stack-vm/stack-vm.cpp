/*
 * File: stack-vm.cpp
 * Description: holder for vm logic implementation
 * Created at: 2018-3-31
 */

#include "stack-vm.hpp"

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

constexpr int VM_MEMORY_SIZE = 1000000;
constexpr int DATA_MASK = 0x01ffffff;

StackVM::StackVM() { memory.reserve(VM_MEMORY_SIZE); }

void StackVM::fetch() { ++pc; }

void StackVM::execute() {
  printf("[stack-vm]  instruction=%d\n", memory[pc]);
  uint32_t opcode = get_opcode(memory[pc]);
  int32_t data = get_data(memory[pc]);
  switch (opcode) {
  case 0:
    execute_halt();
    break;
  case 1:
    execute_push(data);
    break;
  case 2:
    execute_pop();
    break;
  case 3:
    execute_goto(data);
    break;
  case 4:
    execute_add();
    break;
  case 5:
    execute_sub();
    break;
  case 6:
    execute_mul();
    break;
  case 7:
    execute_div();
    break;
  default:
    puts("Unsupported operation");
  }
}

void StackVM::execute_halt() {
  puts("halt");
  this->running = false;
}

void StackVM::execute_push(int32_t data) {
  printf("[stack-vm]  pushing value=%d, on top of stack\n", data);
  ++sp;
  memory[sp] = data;
}

void StackVM::execute_pop() {
  printf("[stack-vm]  pop value=%d, on top of the stack\n", memory[sp]);
  --sp;
}

void StackVM::execute_goto(int32_t data) {
  printf("[stack-vm] goto displacement=%d\n", data);
  pc += data;
}

void StackVM::execute_add() {
  printf("[stack-vm] adding, %d %d\n", memory[sp - 1], memory[sp]);
  memory[sp - 1] += memory[sp];
  --sp;
}

void StackVM::execute_sub() {
  printf("[stack-vm] subtracting, %d %d\n", memory[sp - 1], memory[sp]);
  memory[sp - 1] -= memory[sp];
  --sp;
}

void StackVM::execute_mul() {
  printf("[stack-vm] multiplying, %d %d\n", memory[sp - 1], memory[sp]);
  memory[sp - 1] *= memory[sp];
  --sp;
}

void StackVM::execute_div() {
  printf("[stack-vm] dividing, %d %d\n", memory[sp - 1], memory[sp]);
  memory[sp - 1] /= memory[sp];
  --sp;
}

uint32_t StackVM::get_opcode(int32_t instruction) {
  uint32_t opcode = instruction >> 26;
  printf("[stack-vm]  opcode=%d\n", opcode);
  return opcode;
}

int32_t StackVM::get_data(int32_t instruction) {
  int sign = (instruction >> 25) & 1;
  int32_t data = (instruction & DATA_MASK);
  if (sign) {
    data *= -1;
  }
  printf("[stack-vm]  data=%d\n", data);
  return data;
}

void StackVM::run() {
  --pc;
  while (running) {
    fetch();
    execute();
    printf("tos: %d\n", memory[sp]);
  }
}

void StackVM::load_program(const std::vector<int32_t> prog) {
  for (size_t i = 0; i < prog.size(); ++i) {
    memory[pc + i] = prog[i];
  }
}
