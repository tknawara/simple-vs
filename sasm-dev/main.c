#include <stdio.h>

#include "parser.h"
#include "lexer.h"

#define IN_FILE "test.sasm"

extern int yyparse(yyscan_t scanner);
void parse(void);

int main(void) {
  puts("begin parsing");
  parse();
  puts("finished parsing");
  return 0;
}

void parse(void) {
  yyscan_t scanner;
  YY_BUFFER_STATE state;
 
  if (yylex_init(&scanner)) {
    puts("flex error while initializing");
    return;
  }
  FILE *f = fopen(IN_FILE, "r");
  yyset_in(f, scanner);
 
  if (yyparse(scanner)) {
    puts("Error while initializing bison parser");
    return;
  }
 
  //  yy_delete_buffer(scanner); 
  yylex_destroy(scanner);
}
