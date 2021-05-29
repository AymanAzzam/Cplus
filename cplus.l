%{
#include <stdlib.h>
#include "y.tab.c"

void yyerror(char *);
%}

 // terminals

    // literals
digit       [0-9]
letter      [a-zA-Z]
integer     [-+]]?{digit}+
identifier  [_{letter}][_{letter}{digit}]*
float       [-+]]?(({digit}*\.{digit}+)|({digit}+\.{digit}*))(([eE]{integer})?)

    // operators
arth_opr    "+"|"-"|"*"|"/"|"%"
sngl_opr    "++"|"--"
asgn_opr    "="|"+="|"-="|"*="|"/="|"%="
 //"<<=" ">>=" "&="" "^=" "|="
cmpr_opr    "=="|"!="|">"|"<"|">="|"<="
logic_opr   "&&"|"||"|"!"
bit_opr     "&"|"|"|"^"|"~"|"<<"|">>"

%%

 // matched literals
{identifier}    return IDENTIFIER;
{integer}       yylval=atoi(yytext); return INTEGER;
{float}         yylval=atof(yytext); return FLOAT
"true"          yylval=true; return BOOL;
"false"         yylval=false; return BOOL;

 // operators
{arth_opr}      return yytext;
{single_opr}    return yytext;

 // data types
"int"           return TYPE_INT;
"float"         return TYPE_FLOAT;
"double"        return TYPE_DOUBLE;
"char"          return TYPE_CHAR;
"bool"          return TYPE_BOOL;

 // 

 // ignore whitespace
[ \t\n]+        ;
. yyerror("Unknown character");
%%

int yywrap() {
    return 1;
}

