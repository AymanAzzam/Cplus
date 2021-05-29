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

%token <i> INTEGER
%token <f> FLOAT
%token <c> CHAR
%token <b> BOOL
%token <s> ARTH_OPR IDENTIFIER
%token TYPE_INT TYPE_FLOAT TYPE_CHAR TYPE_BOOL INC_OPR DEC_OPR

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
%right PRE_SNGL "!" "~" "+" "-" //unary+-, prefix inc/dec  xd
%left POST_SNGL                 //         postfix inc/dec xddd

%%

program: program stmt
        |
        ;

stmt: variable_declaration
        | variable_init
        | expr ';'
        ;

expr: INTEGER               {printf("\t~~~~~~~~~~~~~~~~~~~~~~lit\n")}
    | IDENTIFIER            {printf("\t~~~~~~~~~~~~~~~~~~~~~~var\n")}
    | single_opr_expr       {printf("\t~~~~~~~~~~~~~~~~~~~~~~single_opr_expr\n")}
    ;

 /* variables & constants */
variable_declaration: data_type IDENTIFIER ';'              {printf("\t~~~~~~~~~declaration(%s)\n", $2);}
                    ;

variable_init: data_type IDENTIFIER '=' expr ';'            {printf("\t~~~~~~~~~initialization(%s→)\n", $2);}
                    ;



 /* arithmetic operators */


 /* single operators */
single_opr_expr: INC_OPR IDENTIFIER %prec PRE_SNGL          {printf("\t~~~~~~~~~pre-inc\n");}
                | IDENTIFIER INC_OPR %prec POST_SNGL        {printf("\t~~~~~~~~~post-inc\n");}
                | DEC_OPR IDENTIFIER %prec PRE_SNGL         {printf("\t~~~~~~~~~pre-dec\n");}
                | IDENTIFIER DEC_OPR %prec POST_SNGL        {printf("\t~~~~~~~~~post-dec\n");}
                ;

literal: INTEGER    {printf("\t~~~~~~~~~~~~~~~~~~~~~~lit=int\n")}
        | FLOAT     {printf("\t~~~~~~~~~~~~~~~~~~~~~~lit=float\n")}
        | BOOL      {printf("\t~~~~~~~~~~~~~~~~~~~~~~lit=bool\n")}
        | CHAR      {printf("\t~~~~~~~~~~~~~~~~~~~~~~lit=char\n")}
        ;

%%

// const_init: "const" data_type IDENTIFIER '=' expr ';'       {printf("constant initialized with vlaue\n")} /*{addSymValue($3, $2, $5, true);}*/
                    // ;
    

void yyerror(const char *s) {
    fprintf(stderr, "%s\n", s);
}

int main(void) {
    yyparse();
    return 0;
}
