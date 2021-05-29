%{
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#include "cplus.tab.h"

void yyerror(const char *);
%}

 // terminals

    // literals
digit       [0-9]
integer     [-+]?{digit}+
identifier  [a-zA-Z_][a-zA-Z_0-9]*
float       [-+]?(({digit}*\.{digit}+)|({digit}+\.{digit}*))(([eE]{integer})?)

    // operators
arth_opr    "+"|"-"|"*"|"/"|"%"
sngl_opr    "++"|"--"
asgn_opr    "="|"+="|"-="|"*="|"/="|"%="
 //"<<=" ">>=" "&="" "^=" "|="
cmpr_opr    "=="|"!="|">"|"<"|">="|"<="
logic_opr   "&&"|"||"|"!"
bit_opr     "&"|"|"|"^"|"~"|"<<"|">>"

%%

    /* data types */
"int"           return TYPE_INT;
"float"         return TYPE_FLOAT;
"char"          return TYPE_CHAR;
"bool"          return TYPE_BOOL;

    /* operators */
{arth_opr}      {yylval.s=strdup(yytext); return ARTH_OPR;}
"++"            {return INC_OPR;}
"--"            {return DEC_OPR;}

    /* unfinished */ 
{asgn_opr}|{cmpr_opr}|{logic_opr}|{bit_opr}

    /* ignore whitespace */
[ \t]+          ;
\n              ;
;               return *yytext;


    /* matched literals */
"true"|"false"  {yylval.b=strcmp(yytext, "false"); return BOOL;}
{float}         {yylval.f=atof(yytext); return FLOAT;}
{integer}       {yylval.i=atoi(yytext); return INTEGER;}
{identifier}    {yylval.s=strdup(yytext); return IDENTIFIER;}
\'.\'           {yylval.c=yytext[1]; return CHAR;}
%%

int yywrap() {
    return 1;
}

