/*
 * File: sasm.cpp
 * Description: holder for the assembler logic
 * Created at: 2018-3-31
 */

#include <fstream>
#include <iostream>
#include <map>

#include "lexer.hpp"

typedef int32_t i32;
const std::string OUT_FILE = "out.bin";
std::map<std::string, i32> opcode{
  {"+", 0x40000001}, {"-", 0x40000002}, {"*", 0x40000003}, {"/", 0x40000004}, {"halt", 0x40000000}};

std::vector<i32> compileToInstructions(std::vector<std::string> &tokens);
bool isInteger(std::string &token);
bool isPrimitive(std::string &token);
i32 mapToNumber(std::string &token);

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " sasm.filename" << '\n';
    exit(1);
  }

  std::ifstream infile;
  infile.open(argv[1]);
  if (!infile.is_open()) {
    std::cout << "Error: couldn't open [" << argv[1] << "]\n";
    exit(1);
  }
  std::string line;
  std::string contents;
  while (std::getline(infile, line)) {
    contents += line;
    contents += "\n";
  }
  infile.close();
  Lexer lexer;
  auto tokens = lexer.lex(contents);
  auto instructions = compileToInstructions(tokens);

  std::ofstream outfile;
  outfile.open(OUT_FILE, std::ios::binary);
  for (auto &i : instructions) {
    outfile.write(reinterpret_cast<char *>(&i), sizeof(i32));
  }
  outfile.close();
  return 0;
}

std::vector<i32> compileToInstructions(std::vector<std::string> &tokens) {
  std::vector<i32> instructions;
  for (auto &i : tokens) {
    if (isInteger(i)) {
      instructions.push_back(std::stoi(i));
    } else {
      auto instruction = mapToNumber(i);
      if (instruction != -1) {
        instructions.push_back(instruction);
      } else {
        std::cout << "Error: Invalid instruction !" << i << '\n';
      }
    }
  }
  instructions.push_back(opcode["halt"]);
  return instructions;
}

bool isInteger(std::string &token) {
  for (auto i : token) {
    if (!isdigit(i)) {
      return false;
    }
  }
  return true;
}

bool isPrimitive(std::string &token) { return false; }

i32 mapToNumber(std::string &token) {
  if (opcode.find(token) == opcode.end()) {
    return -1;
  }
  return opcode[token];
}
