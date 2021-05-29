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
%token LOGICAL_AND LOGICAL_OR LOGICAL_NOT
%token BIT_AND BIT_OR BIT_XOR BIT_NOT SHL SHR
%token FOR WHILE DO BREAK CONTINUE

%right "=" "+=" "-=" "*=" "/=" "%%=" //"<<=" ">>=" "&="" "^=" "|="
%left LOGICAL_OR
%left LOGICAL_AND
%left BIT_OR
%left BIT_AND
%left BIT_XOR
%left "==" "!="
%left "<" ">" "<=" ">="
%left SHL SHR
%left '+' '-'
%left '*' '/' '%'
%right BIT_NOT LOGICAL_NOT
%right PRE_SNGL "+" "-" //unary+-, prefix inc/dec  xd
%left POST_SNGL          //         postfix inc/dec xddd

%%

program: program stmt
        |
        ;

stmt: variable_declaration
        | variable_init
        | expr ';'
        ;

// master expression
expr:     '(' expr ')'
        |       single_opr_expr
        |       logic_expr
        |       bit_expr
        |       INTEGER
        |       BOOL
        |       FLOAT
        |       CHAR
        ;    

 /* data types */
data_type: TYPE_INT
         | TYPE_FLOAT
         | TYPE_DOUBLE
         | TYPE_CHAR
         | TYPE_BOOL
         ;

 /* variables & constants */
variable_declaration: data_type IDENTIFIER ';'              {printf("\t~~~~~~~~~declaration(%s)\n", $2);}
                    ;
variable_init: data_type IDENTIFIER '=' expr ';'            {printf("\t~~~~~~~~~initialization(%s→)\n", $2);}
                    ;

 /* arithmetic operators */


 /* single operators */
single_opr_expr: SNGL_OPR IDENTIFIER %prec PRE_SNGL          {printf("\t~~~~~~~~~pre-(%d)\n", $1);}
                | IDENTIFIER SNGL_OPR %prec POST_SNGL        {printf("\t~~~~~~~~~post-(%d)\n", $2);}
                ;

// logical operators
logic_expr:     expr LOGICAL_AND expr           ; // {$$ = $1 && $3}
        |       expr LOGICAL_OR expr            ; // {$$ = $1 || $3}
        |       LOGICAL_NOT expr                ; // {$$ = !$2}
        ;

// bitwise operators
bit_expr:       expr BIT_AND expr           ; // {$$ = $1 & $3}
        |       expr BIT_OR expr            ; // {$$ = $1 | $3}     
        |       expr BIT_XOR expr           ; // {$$ = $1 ^ $3}
        |       BIT_NOT expr                ; // {$$ = ~$2}
        |       expr SHR expr               ; // {$$ = $1 >> $3}
        |       expr SHL expr               ; // {$$ = $1 << $3}
        ;     

// loops

%%

// const_init: "const" data_type IDENTIFIER '=' expr ';'       {printf("constant initialized with vlaue\n")} /*{addSymValue($3, $2, $5, true);}*/
                    // ;

void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}

int main(void) {
    yyparse();
    return 0;
}
