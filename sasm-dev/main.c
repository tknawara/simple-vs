#include <stdio.h>

#include "parser.h"
#include "lexer.h"

extern int yyparse(yyscan_t scanner);
void parse(char *filename);

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage %s <filename>\n", argv[0]);
    return 1;
  }
  puts("begin parsing");
  parse(argv[1]);
  puts("finished parsing");
  return 0;
}

void parse(char *filename) {
  yyscan_t scanner;
  YY_BUFFER_STATE state;
 
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
 
  //  yy_delete_buffer(scanner); 
  yylex_destroy(scanner);
}
