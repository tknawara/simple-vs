/*
 * File: main.cpp
 * Description: Application entry point
 * Created at: 2018-3-31
 */

#include <fstream>
#include <iostream>
#include <vector>

#include "stack-vm.hpp"

std::vector<int32_t> read_prog_bin(char *filename);
std::vector<int32_t> read_prog(char *filename);

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s <filename>\n", argv[0]);
    exit(1);
  }
  auto prog = read_prog(argv[1]);
  StackVM vm;
  vm.load_program(prog);
  vm.run();
  return 0;
}

std::vector<int32_t> read_prog_bin(char *filename) {
  std::ifstream infile(filename, std::ios::binary);
  int32_t i;
  std::vector<int32_t> prog;
  while (infile.read((char *)&i, sizeof(i))) {
    prog.push_back(i);
  }
  return prog;
}

std::vector<int32_t> read_prog(char *filename) {
  std::ifstream infile(filename);
  int32_t i;
  std::vector<int32_t> prog;
  while (infile >> i) {
    prog.push_back(i);
  }
  return prog;
}
