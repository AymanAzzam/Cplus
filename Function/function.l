%{
   /* Definition section */
  #include<stdio.h>
  #include "y.tab.h"
  void yyerror(char *);
  extern int yylval;
%}
  
/* Rule Section */
%%
[(),]                                         return *yytext;

return                                        return RETURN;

'void'|'char'|'int'|'float'|'double'|'bool'   return FUNC_TYPE;

%%
  
int yywrap()
{
 return 1;
}
