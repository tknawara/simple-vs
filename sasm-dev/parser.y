%{
  /*
   * File: parser.y
   * Description: holder for the grammar of the assmebler
   * Created at: 2018-4-3
   */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "command.h"

  %}

%code requires {

#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
  typedef void* yyscan_t;
#endif

 }
 
%output  "parser.c"
%defines "parser.h"
%define api.pure
%lex-param   { yyscan_t scanner }
%parse-param { yyscan_t scanner }

%union {
  int value;
  char label[100];
}

%token TOKEN_POS_SIGN
%token TOKEN_NEG_SIGN
%token TOKEN_ADD
%token TOKEN_SUB
%token TOKEN_MUL
%token TOKEN_DIV
%token TOKEN_HALT
%token TOKEN_PUSH
%token TOKEN_NEW_LINE
%token TOKEN_POP
%token TOKEN_GOTO
%token TOKEN_LT
%token TOKEN_GT
%token TOKEN_EQ
%token TOKEN_LTE
%token TOKEN_GTE
%token TOKEN_COLON
%token <label> TOKEN_LABEL
%token <value> TOKEN_NUMBER
%token <value> TOKEN_NEG_NUMBER

%type <label> sign
%%
 
program
: statements
;

statements
: statement statements
| statement
;

sign
: TOKEN_NEG_SIGN { strcpy($$, "-"); }
| TOKEN_POS_SIGN { strcpy($$, "+"); }
| %empty

statement
: TOKEN_PUSH sign TOKEN_NUMBER TOKEN_NEW_LINE
{
  if (pass_two()) {
    int value = $3;
    if (strcmp($2, "-") == 0) {
      value *= -1;
    }
    encode_push(value);
  }
  increment_loc();
}
| TOKEN_GOTO TOKEN_LABEL  TOKEN_NEW_LINE
{
  if (pass_two()) {
    encode_goto($2);
  }
  increment_loc();
}
| TOKEN_LABEL TOKEN_COLON
{
  if (!pass_two()) {
    add_label($1);
  } else {
    encode_label();
  }
  increment_loc();
}
| TOKEN_POP  TOKEN_NEW_LINE { if (pass_two()) encode_pop();  increment_loc();  }
| TOKEN_ADD  TOKEN_NEW_LINE { if (pass_two()) encode_add();  increment_loc();  }
| TOKEN_SUB  TOKEN_NEW_LINE { if (pass_two()) encode_sub();  increment_loc();  }
| TOKEN_MUL  TOKEN_NEW_LINE { if (pass_two()) encode_mul();  increment_loc();  }
| TOKEN_DIV  TOKEN_NEW_LINE { if (pass_two()) encode_div();  increment_loc();  }
| TOKEN_HALT TOKEN_NEW_LINE { if (pass_two()) encode_halt(); increment_loc();  }
| TOKEN_LT   TOKEN_NEW_LINE { if (pass_two()) encode_lt();   increment_loc();  }
| TOKEN_GT   TOKEN_NEW_LINE { if (pass_two()) encode_gt();   increment_loc();  }
| TOKEN_EQ   TOKEN_NEW_LINE { if (pass_two()) encode_eq();   increment_loc();  }
| TOKEN_GTE  TOKEN_NEW_LINE { if (pass_two()) encode_gte();  increment_loc();  }
| TOKEN_LTE  TOKEN_NEW_LINE { if (pass_two()) encode_lte();  increment_loc();  }
| TOKEN_NEW_LINE
;

%%
