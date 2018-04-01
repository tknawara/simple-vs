/*
 * File: lexer.cpp
 * Description: holder for the lexer implementation
 * Created at: 2018-3-31
 */

#include "lexer.hpp"

constexpr int LEXEM_SIZE = 256;

std::vector<std::string> Lexer::lex(std::string &s) {
  std::vector<std::string> tokens;
  char lexem[LEXEM_SIZE];
  State state = State::START;
  int balance = 0;
  size_t i = 0;
  size_t j = 0;

  while (i < s.length()) {
    switch (state) {
      case START:
        handleStart(s, lexem, state, i, j);
        break;
      case READ_CHAR:
        handleReadChar(s, lexem, state, i, j);
        break;
      case READ_BLOCK:
        handleReadBlock(s, lexem, state, i, j, balance);
        break;
      case SKIP:
        handleSkip(s, lexem, state, i, j);
        break;
      case DUMP:
        handleDump(tokens, s, lexem, state, i, j);
        break;
      case COMMENT:
        handleComment(s, lexem, state, i, j);
        break;
      case END:
        handleEnd(s, lexem, state, i, j);
        break;
    }
  }

  if (j > 0) {
    lexem[j] = '\0';
    tokens.push_back(lexem);
  }
  return tokens;
}

void Lexer::handleStart(std::string &s, char *lexem, State &state, size_t &i,
                        size_t &j) {
  if (my_isspace(s[i])) {
    state = SKIP;
  } else if (isgroup(s[i])) {
    if (s[i] == '"') {
      lexem[j++] = s[i++];
    }
    state = READ_BLOCK;
  } else if (s[i] == '/' && s[i + 1] == '/') {
    i += 2;
    state = COMMENT;
  } else {
    state = READ_CHAR;
  }
}

void Lexer::handleReadChar(std::string &s, char *lexem, State &state, size_t &i,
                           size_t &j) {
  if (my_isspace(s[i])) {
    state = DUMP;
  } else if (s[i] == '\\') {
    i += 2;
  } else if (isgroup(s[i])) {
    if (s[i] == '"') {
      lexem[j++] = s[i++];
    }
    state = READ_BLOCK;
  } else if (isspecial(s[i])) {
    if (j == 0) {
      lexem[j++] = s[i++];
    }
    state = DUMP;
  } else if (s[i] == '/' && s[i + 1] == '/') {
    i += 2;
    state = COMMENT;
  } else {
    lexem[j++] = s[i++];
  }
}

void Lexer::handleReadBlock(std::string &s, char *lexem, State &state,
                            size_t &i, size_t &j, int &balance) {
  if (s[i] == beginChar && s[i] != '"') {
    ++balance;
    lexem[j++] = s[i++];
  } else if (s[i] == endChar) {
    --balance;
    lexem[j++] = s[i++];
    if (balance <= 0) {
      state = DUMP;
    }
  } else if (endChar == '"' && s[i] == '\\') {
    i += 2;
  } else {
    lexem[j++] = s[i++];
  }
}

void Lexer::handleSkip(std::string &s, char *lexem, State &state, size_t &i,
                       size_t &j) {
  if (my_isspace(s[i])) {
    ++i;
  } else {
    state = READ_CHAR;
  }
}

void Lexer::handleDump(std::vector<std::string> &tokens, std::string &s,
                       char *lexem, State &state, size_t &i, size_t &j) {
  if (j > 0) { // TODO: check this in a test
    lexem[j] = '\0';
    tokens.push_back(lexem);
    j = 0;
  }
  state = START;
}

void Lexer::handleComment(std::string &s, char *lexem, State &state, size_t &i,
                          size_t &j) {
  if (s[i] != '\n') {
    ++i;
  } else {
    state = READ_CHAR;
  }
}

void Lexer::handleEnd(std::string &s, char *lexem, State &state, size_t &i,
                      size_t &j) {
  i = s.length();
}

bool Lexer::my_isspace(char c) {
  switch (c) {
    case '\n':
    case '\r':
    case '\t':
    case '\v':
    case ' ':
    case '\f':
      return true;
    default:
      return false;
  }
}

bool Lexer::isspecial(char c) {
  switch (c) {
    case '[':
    case ']':
      return true;
    default:
      return false;
  }
}

bool Lexer::isgroup(char c) {
  beginChar = c;
  switch (c) {
    case '"':
      endChar = '"';
      return true;
    case '(':
      endChar = ')';
      return true;
    case ')':
      return true;
    default:
      return false;
  }
}
