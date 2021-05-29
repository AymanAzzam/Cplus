%{
/* Definition section */
#include<stdio.h>
%}

%token RETURN
%token FUNC_TYPE

/* Rule Section */
%%

// ------------------------------------------------------------
//
// Function Rules (depends on block, id, var_decl, expression)
//

func:           	func_header block          		{ }
    ;

func_header:    	FUNC_TYPE id '(' paramater ')'	{ }
    ;

paramater:          /* epsilon */                 	{ }
    |               var_decl                       	{ }
    |               paramater ',' var_decl         	{ }
    ;

parameter_ext:     	var_decl                      	{ }
    |               parameter_ext ',' var_decl     	{ }
    ;

func_call:      	id '(' args ')'              	{ }
    ;

args:           	/* epsilon */                  	{ }
    |               expression                     	{ }
    |               args_ext ',' expression         { }
    ;

args_ext:       	expression                     	{ }
    |               args_ext ',' expression         { }
    ;

return_stmt:        RETURN expression              	{ }
    |               RETURN                         	{ }
    ;

%%

void yyerror(char* s){
	printf("\nError in %s\n\n", s);
}

int main(){
	yyparse();
	return 0;
}