/*
 * File: main.cpp
 * Description: Application entry point
 * Created at: 2018-3-31
 */

#include <iostream>
#include <fstream>
#include <vector>

#include "stack-vm.hpp"

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s <filename>\n", argv[0]);
    exit(1);
  }
  std::ifstream infile(argv[1], std::ios::binary);
  int32_t i;
  std::vector<i32> prog;
  while (infile.read((char *) &i, sizeof(i))) {
    prog.push_back(i);
  }
  StackVM vm;
  vm.loadProgram(prog);
  vm.run();
  return 0;
}
