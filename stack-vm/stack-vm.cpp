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

StackVM::StackVM() { memory.reserve(VM_MEMORY_SIZE); }

i32 StackVM::getType(i32 instruction) {
  i32 type = 0xc0000000;
  type = (type & instruction) >> 30;
  return type;
}

i32 StackVM::getData(i32 instruction) {
  i32 data = 0x3fffffff;
  data = data & instruction;
  return data;
}

void StackVM::fetch() { ++pc; }

void StackVM::decode() {
  typ = getType(memory[pc]);
  dat = getData(memory[pc]);
}

void StackVM::execute() {
  if (typ == 0 || typ == 2) {
    ++sp;
    memory[sp] = dat;
  } else {
    doPrimitive();
  }
}

void StackVM::doPrimitive() {
  switch (dat) {
    case 0:
      std::cout << "halt" << '\n';
      running = false;
      break;
    case 1:
      std::cout << "adding, " << memory[sp - 1] << " " << memory[sp] << '\n';
      memory[sp - 1] += memory[sp];
      --sp;
      break;
    case 2:
      std::cout << "subtracting, " << memory[sp - 1] << " " << memory[sp]
                << '\n';
      memory[sp - 1] -= memory[sp];
      --sp;
      break;
    case 3:
      std::cout << "multiplying, " << memory[sp - 1] << " " << memory[sp]
                << '\n';
      memory[sp - 1] *= memory[sp];
      --sp;
      break;
    case 4:
      std::cout << "dividing, " << memory[sp - 1] << " " << memory[sp] << '\n';
      memory[sp - 1] /= memory[sp];
      --sp;
      break;
    default:
      std::cout << "unsupported instruction" << '\n';
  }
}

void StackVM::run() {
  --pc;
  while (running == 1) {
    fetch();
    decode();
    execute();
    std::cout << "tos: " << memory[sp] << '\n';
  }
}

void StackVM::loadProgram(const std::vector<i32> prog) {
  for (size_t i = 0; i < prog.size(); ++i) {
    memory[pc + i] = prog[i];
  }
}
