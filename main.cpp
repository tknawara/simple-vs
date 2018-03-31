/*
 * File: main.cpp
 * Description: Application entry point
 * Created at: 2018-3-31
 */

#include <vector>

#include "stack-vm/stack-vm.hpp"

int main() {
  StackVM vm;
  std::vector<i32> prog{3, 4,          0x40000001, 5,          0x40000002,
                        3, 0x40000003, 2,          0x40000004, 0x40000000};
  vm.loadProgram(prog);
  vm.run();
  return 0;
}
