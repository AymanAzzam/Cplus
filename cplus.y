%{
#include <stdio.h>

int yylex(void);
void yyerror(const char *);
%}

%union {
    int i;
    char c;
    char* s;
    float f;
    double d;
    bool b;
}

%token <i> INTEGER SNGL_OPR
%token <f> FLOAT
%token <c> CHAR
%token <b> BOOL
%token <s> ARTH_OPR IDENTIFIER
%token TYPE_INT TYPE_FLOAT TYPE_DOUBLE TYPE_CHAR TYPE_BOOL

%right "=" "+=" "-=" "*=" "/=" "%%=" //"<<=" ">>=" "&="" "^=" "|="
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
%right PRE_SNGL "+" "-" //unary+-, prefix inc/dec  xd
%left POST_SNGL          //         postfix inc/dec xddd

%%

program: program stmt
        |
        ;

stmt: variable_declaration
        | expr ';'
        ;

expr: single_opr_expr
    ;

 /* variables & constants */
variable_declaration: data_type IDENTIFIER ';'              {printf("\t~~~~~~~~~declaration(%s)\n", $2);}
                    ;

 /* data types */
data_type: TYPE_INT
         | TYPE_FLOAT
         | TYPE_DOUBLE
         | TYPE_CHAR
         | TYPE_BOOL
         ;


 /* arithmetic operators */


 /* single operators */
single_opr_expr: SNGL_OPR IDENTIFIER %prec PRE_SNGL          {printf("\t~~~~~~~~~pre-(%d)\n", $1);}
                | IDENTIFIER SNGL_OPR %prec POST_SNGL        {printf("\t~~~~~~~~~post-(%d)\n", $2);}
                ;

%%

// const_init: "const" data_type IDENTIFIER '=' expr ';'       {printf("constant initialized with vlaue\n")} /*{addSymValue($3, $2, $5, true);}*/
                    // ;

// variable_init: data_type IDENTIFIER '=' expr ';'            {printf("\t~~~~~~~~~initialization(%s→)\n", $2);}
//                     ;
    

void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}

int main(void) {
    yyparse();
    return 0;
}
