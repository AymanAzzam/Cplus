%{
/* Definition section */
#include<stdio.h>
%}

/* Rule Section */
%%

// ------------------------------------------------------------
//
// Expression Rules (depends on value, id, func_call)
//

expression:         assignment                              { }
    |               other                                   { }
    ;

assignment:         expression "=" expression               { }
	|				expression "+=" expression              { }
	|				expression "-=" expression              { }
	|				expression "*=" expression              { }
	|				expression "/=" expression              { }
	|				expression "%%=" expression             { }
    ;

other:             '(' expression ')'                       { }

    |               value                                   { }
    |               id                                      { }
    |               func_call                               { }
    ;


%%

void yyerror(char* s){
	printf("\nError in %s\n\n", s);
}


int main(){
	yyparse();
	return 0;
}