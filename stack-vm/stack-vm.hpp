/*
 * File: stack-vm.hpp
 * Description: holder for interface of the vm
 * Created at: 2018-3-31
 */

#ifndef STACK_VM_HPP
#define STACK_VM_HPP

#include <iostream>
#include <vector>

class StackVM {
 public:
  StackVM();
  void run();
  void loadProgram(const std::vector<int32_t> prog);

 private:
  int32_t pc = 100;
  int32_t sp = 0;
  std::vector<int32_t> memory;
  int32_t instructionType = 0;
  int32_t instructionData = 0;
  bool running = true;
  int32_t getType(int32_t instruction);
  int32_t getData(int32_t instruction);
  void fetch();
  void decode();
  void execute();
  void doPrimitive();
};

#endif
