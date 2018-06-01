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

%option outfile="lexer.c" header-file="lexer.h"
%option warn nodefault
%option caseless
%option reentrant noyywrap never-interactive nounistd
%option bison-bridge
 
ADD         "ADD"
SUB         "SUB"
MUL         "MUL"
DIV         "DIV"
PUSH        "PUSH"
POP         "POP"
GOTO        "GOTO"
HALT        "HALT"
LT          "LT"
GT          "GT"
EQ          "EQ"
LTE         "LTE"
GTE         "GTE"
COLON       ":"
NEG_SIGN    "-"
POS_SIGN    "+"
NEW_LINE    "\n"
NUMBER      [0-9]+
LABEL       [a-zA-Z][a-zA-Z0-9]*
WS          [ \r\t]*
 
%%
 
{WS}           { /* Skip blanks. */ }
{NEW_LINE}     { return TOKEN_NEW_LINE; }
{NUMBER}       {sscanf(yytext, "%d", &yylval->value); return TOKEN_NUMBER; }

{NEG_SIGN}     { return TOKEN_NEG_SIGN ;}
{POS_SIGN}     { return TOKEN_POS_SIGN; }
{PUSH}         { return TOKEN_PUSH; }
{POP}          { return TOKEN_POP; }
{GOTO}         { return TOKEN_GOTO; }
{MUL}          { return TOKEN_MUL; }
{ADD}          { return TOKEN_ADD; }
{DIV}          { return TOKEN_DIV; }
{SUB}          { return TOKEN_SUB; }
{HALT}         { return TOKEN_HALT; }
{LT}           { return TOKEN_LT; }
{GT}           { return TOKEN_GT; }
{EQ}           { return TOKEN_EQ; }
{LTE}          { return TOKEN_LTE; }
{GTE}          { return TOKEN_GTE; }
{COLON}        { return TOKEN_COLON; }

{LABEL}        { strcpy(yylval->label, yytext); return TOKEN_LABEL; }

.              {  }

%%
 
int yyerror(const char *msg) {
  fprintf(stderr,"Error:%s\n",msg); return 0;
}
