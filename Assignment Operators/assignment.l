%{
   /* Definition section */
  #include<stdio.h>
  #include "y.tab.h"
  void yyerror(char *);
  extern int yylval;
%}
  
/* Rule Section */
%%

[+-/*%]?=                                {printf(yytext);return *yytext;};

%%
  
int yywrap()
{
 return 1;
}
