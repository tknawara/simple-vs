/*
 * File: main.c
 * Description: entry point of the parser
 * Created at: 2018-4-1
 */

#include <stdio.h>

#include "parser.h"
#include "command.h"
#include "lexer.h"

extern int yyparse(yyscan_t scanner);
void parse(char *filename);

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage %s <filename>\n", argv[0]);
    return 1;
  }
  init();
  puts("begin parsing");
  parse(argv[1]);
  puts("finished parsing");
  increment_pass();
  puts("begin parsing, pass two");
  parse(argv[1]);
  puts("finished parsing, pass two");
  destroy_command();
  return 0;
}

void parse(char *filename) {
  yyscan_t scanner;
 
  if (yylex_init(&scanner)) {
    puts("flex error while initializing");
    return;
  }
  FILE *f = fopen(filename, "r");
  yyset_in(f, scanner);
 
  if (yyparse(scanner)) {
    puts("Error while initializing bison parser");
    return;
  } 
  yylex_destroy(scanner);
}
