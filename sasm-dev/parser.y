%{
  /*
   * File: parser.y
   * Description: holder for the grammar of the assmebler
   * Created at: 2018-4-3
   */
#include <stdio.h>
#include "command.h"
#include "parser.h"
#include "lexer.h"

  %}

%code requires {

#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
  typedef void* yyscan_t;
#endif

 }
 
%define api.pure
%lex-param   { yyscan_t scanner }
%parse-param { yyscan_t scanner }

%union {
  int value;
  char label[100];
}

%token TOKEN_ADD
%token TOKEN_SUB
%token TOKEN_MUL
%token TOKEN_DIV
%token TOKEN_HALT
%token TOKEN_PUSH
%token TOKEN_SIMI_COLON
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
 
%%
 
program
: statements
;

statements
: statement statements
| statement
;

statement
: TOKEN_PUSH TOKEN_NUMBER TOKEN_SIMI_COLON
{
  if (pass_two()) {
    encode_push($2);
  } else {
    increment_loc();
  }
}
| TOKEN_GOTO TOKEN_LABEL  TOKEN_SIMI_COLON
{
  if (pass_two()) {
    encode_goto($2);
  } else {
    increment_loc();
  }
}
| TOKEN_LABEL TOKEN_COLON     { if (!pass_two()) { add_label($1); increment_loc(); }  }
| TOKEN_POP  TOKEN_SIMI_COLON { if (pass_two()) encode_pop();  else increment_loc();  }
| TOKEN_ADD  TOKEN_SIMI_COLON { if (pass_two()) encode_add();  else increment_loc();  }
| TOKEN_SUB  TOKEN_SIMI_COLON { if (pass_two()) encode_sub();  else increment_loc();  }
| TOKEN_MUL  TOKEN_SIMI_COLON { if (pass_two()) encode_mul();  else increment_loc();  }
| TOKEN_DIV  TOKEN_SIMI_COLON { if (pass_two()) encode_div();  else increment_loc();  }
| TOKEN_HALT TOKEN_SIMI_COLON { if (pass_two()) encode_halt(); else increment_loc();  }
| TOKEN_LT   TOKEN_SIMI_COLON { if (pass_two()) encode_lt();   else increment_loc();  }
| TOKEN_GT   TOKEN_SIMI_COLON { if (pass_two()) encode_gt();   else increment_loc();  }
| TOKEN_EQ   TOKEN_SIMI_COLON { if (pass_two()) encode_eq();   else increment_loc();  }
| TOKEN_GTE  TOKEN_SIMI_COLON { if (pass_two()) encode_gte();  else increment_loc();  }
| TOKEN_LTE  TOKEN_SIMI_COLON { if (pass_two()) encode_lte();  else increment_loc();  }
;

%%
