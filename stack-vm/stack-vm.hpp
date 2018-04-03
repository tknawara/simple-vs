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
  void load_program(const std::vector<int32_t> prog);

 private:
  int32_t pc = 100;
  int32_t sp = 0;
  std::vector<int32_t> memory;
  bool running = true;
  void fetch();
  void execute();
  void execute_halt();
  void execute_push(int32_t data);
  void execute_pop();
  void execute_goto(int32_t data);
  void execute_add();
  void execute_sub();
  void execute_mul();
  void execute_div();
  void execute_lt();
  void execute_lte();
  void execute_gt();
  void execute_gte();
  void execute_eq();
  void execute_label();
  uint32_t get_opcode(int32_t instruction);
  int32_t get_data(int32_t instruction);
  
};

#endif
