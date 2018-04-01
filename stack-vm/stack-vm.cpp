/*
 * File: stack-vm.cpp
 * Description: holder for vm logic implementation
 * Created at: 2018-3-31
 */

#include "stack-vm.hpp"

/*
  Instruction format
  header: 2 bits
  data:   30 bits

  header format:
  0 -> positive integer
  1 -> primitive instruction
  2 -> negative integer
  3 -> undefined

  instructions:
  0 -> halt
  1 -> add two elements of the stack
  2 -> subtract two elements of the stack
  3 -> multiply two elements of the stack
  4 -> divide two elements of the stack
 */

constexpr int VM_MEMORY_SIZE = 1000000;
constexpr int TYPE_MASK = 0xc0000000;
constexpr int DATA_MASK = 0x3fffffff;

StackVM::StackVM() { memory.reserve(VM_MEMORY_SIZE); }

int32_t StackVM::getType(int32_t instruction) {
  int32_t type = TYPE_MASK;
  type = (type & instruction) >> 30;
  return type;
}

int32_t StackVM::getData(int32_t instruction) {
  int32_t data = DATA_MASK;
  data = data & instruction;
  return data;
}

void StackVM::fetch() { ++pc; }

void StackVM::decode() {
  this->instructionType = getType(memory[pc]);
  this->instructionData = getData(memory[pc]);
}

void StackVM::execute() {
  if (instructionType == 0 || instructionData == 2) {
    ++sp;
    memory[sp] = instructionData;
  } else {
    doPrimitive();
  }
}

void StackVM::doPrimitive() {
  switch (instructionData) {
    case 0:
      puts("halt");
      this->running = false;
      break;
    case 1:
      printf("adding, %d %d\n", memory[sp - 1], memory[sp]);
      memory[sp - 1] += memory[sp];
      --sp;
      break;
    case 2:
      printf("subtracting, %d %d\n", memory[sp - 1], memory[sp]);
      memory[sp - 1] -= memory[sp];
      --sp;
      break;
    case 3:
      printf("multiplying, %d %d\n", memory[sp - 1], memory[sp]);
      memory[sp - 1] *= memory[sp];
      --sp;
      break;
    case 4:
      printf("dividing, %d %d\n", memory[sp - 1], memory[sp]);
      memory[sp - 1] /= memory[sp];
      --sp;
      break;
    default:
      puts("Unsupported operation");
  }
}

void StackVM::run() {
  --pc;
  while (running) {
    fetch();
    decode();
    execute();
    printf("tos: %d\n", memory[sp]);
  }
}

void StackVM::loadProgram(const std::vector<int32_t> prog) {
  for (size_t i = 0; i < prog.size(); ++i) {
    memory[pc + i] = prog[i];
  }
}
