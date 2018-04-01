/*
 * File: lexer.hpp
 * Description: interface for our lexer
 * Created at: 2018-3-31
 */

#ifndef LEXER_HPP
#define LEXER_HPP

#include <iostream>
#include <string>
#include <vector>

enum State : uint8_t { START, READ_CHAR, READ_BLOCK, SKIP, DUMP, COMMENT, END };

class Lexer {
 public:
  std::vector<std::string> lex(std::string &s);

 private:
  void handleStart(std::string &s, char *lexem, State &state, size_t &i,
                   size_t &j);
  void handleReadChar(std::string &s, char *lexem, State &state, size_t &i,
                      size_t &j);
  void handleReadBlock(std::string &s, char *lexem, State &state, size_t &i,
                       size_t &j, int &balance);
  void handleSkip(std::string &s, char *lexem, State &state, size_t &i,
                  size_t &j);
  void handleDump(std::vector<std::string> &tokens, std::string &s, char *lexem,
                  State &state, size_t &i, size_t &j);
  void handleComment(std::string &s, char *lexem, State &state, size_t &i,
                     size_t &j);
  void handleEnd(std::string &s, char *lexem, State &state, size_t &i,
                 size_t &j);

  bool my_isspace(char c);
  bool isspecial(char c);
  bool isgroup(char c);
  char beginChar;
  char endChar;
};

#endif
