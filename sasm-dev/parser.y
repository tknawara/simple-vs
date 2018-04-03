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
  char *label;
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
%token <label> TOKEN_LABEL
%token <value> TOKEN_NUMBER
 
%%
 
program
: { init(); } statements
;

statements
: statement TOKEN_SIMI_COLON statements
| statement TOKEN_SIMI_COLON
;

statement
: TOKEN_PUSH TOKEN_NUMBER { encode_push($2); }
| TOKEN_GOTO TOKEN_LABEL  { encode_goto($2); }
| TOKEN_POP  { encode_pop();  }
| TOKEN_ADD  { encode_add();  }
| TOKEN_SUB  { encode_sub();  }
| TOKEN_MUL  { encode_mul();  }
| TOKEN_DIV  { encode_div();  }
| TOKEN_HALT { encode_halt(); }
| TOKEN_LT   { encode_lt();   }
| TOKEN_GT   { encode_gt();   }
| TOKEN_EQ   { encode_eq();   }
| TOKEN_GTE  { encode_gte();  }
| TOKEN_LTE  { encode_lte();  }
;

%%
