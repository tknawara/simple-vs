/*
 * File: stack-vm.hpp
 * Description: holder for interface of the vm
 * Created at: 2018-3-31
 */

#ifndef STACK_VM_HPP
#define STACK_VM_HPP

#include <iostream>
#include <vector>

typedef int32_t i32;

class StackVM {
 public:
  StackVM();
  void run();
  void loadProgram(const std::vector<i32> prog);

 private:
  i32 pc = 100;  // program counter
  i32 sp = 0;    // stack pointer
  std::vector<i32> memory;
  i32 typ = 0;
  i32 dat = 0;
  bool running = true;
  i32 getType(i32 instruction);
  i32 getData(i32 instruction);
  void fetch();
  void decode();
  void execute();
  void doPrimitive();
};

#endif
