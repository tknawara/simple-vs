%{
  /*
   * File: Lexer.lex
   * Description: Lexer definitions
   * Created at: 2018-4-1
   */
  
#include <stdio.h>
#include <string.h>
#include "parser.h"
 
%}

%option warn nodefault
%option caseless
%option reentrant noyywrap never-interactive nounistd
%option bison-bridge
 
ADD         "ADD"
SUB         "SUB"
MUL         "MUL"
DIV         "DIV"
SIMI_COLON  ";"
PUSH        "PUSH"
POP         "POP"
GOTO        "GOTO"
NUMBER      [0-9]+
LABEL       [a-zA-Z][a-zA-Z0-9]*
WS          [ \r\n\t]*
 
%%
 
{WS}           { /* Skip blanks. */ }
{NUMBER}       { sscanf(yytext, "%d", &yylval->value); return TOKEN_NUMBER; }

{PUSH}         { return TOKEN_PUSH; }
{POP}          { return TOKEN_POP; }
{GOTO}         { return TOKEN_GOTO; }
{MUL}          { return TOKEN_MUL; }
{ADD}          { return TOKEN_ADD; }
{DIV}          { return TOKEN_DIV; }
{SUB}          { return TOKEN_SUB; }
{SIMI_COLON}   { return TOKEN_SIMI_COLON; }

{LABEL}        { yylval->value = yytext; return TOKEN_LABEL; }

.              {  }

%%
 
int yyerror(const char *msg) {
  fprintf(stderr,"Error:%s\n",msg); return 0;
}
