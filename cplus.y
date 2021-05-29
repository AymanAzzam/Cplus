%{
#include "stdio.h"

int yylex(void);
void yyerror(char *);

bool addSym(char* id, char* dtype, bool constant=false);    // add new symbol to symbol table (uninitialized)
template<class T> bool addSymValue(char* id, char* dtype, T value, bool constant=false);    // add new symbol (initialized)
template<class T> bool updateSym(char* id, T value);     // update an existing symbol
template<class T> T sym(char* id);  // return the value of an existing symbol
%}

%token IDENTIFIER INTEGER FLOAT BOOL
%token TYPE_INT TYPE_FLOAT TYPE_DOUBLE TYPE_CHAR TYPE_BOOL

%right "=" "+=" "-=" "*=" "/=" "%=" //"<<=" ">>=" "&="" "^=" "|="
%left "||"
%left "&&"
%left "|"
%left "&"
%left "^"
%left "==" "!="
%left "<" ">" "<=" ">="
%left "<<" ">>"
%left '+' '-'
%left '*' '/' '%'
%right "++" "--" "+" "-" //unary+-, prefix inc/dec  xd
%left "++" "--"          //         postfix inc/dec xddd

%%

 // data types
data_type: TYPE_INT
         | TYPE_FLOAT
         | TYPE_DOUBLE
         | TYPE_CHAR
         | TYPE_BOOL
//       | .+           {/*error*/;}
         ;

 // variables & constants
variable_declaration: data_type IDENTIFIER ';'      {addSym($2, $1); /*add to symbol table*/} 
                    ;

variable_definition: data_type IDENTIFIER '=' expr ';'      {addSymValue($2, $1, $4)}
                    ;

const_definition: "const" data_type IDENTIFIER '=' expr ';'      {addSymValue($3, $2, $5, true); /*add to symbol table*/}
                    ;

 // arithmetic operators


 // single operators

%%

void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}

int main(void) {
    yyparse();
    return 0;
}
