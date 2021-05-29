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
%token <s> IDENTIFIER
%token TYPE_INT TYPE_FLOAT TYPE_CHAR TYPE_BOOL
%token CONST
%token ADD SUB MUL DIV REM
%token INC_OPR DEC_OPR
%token LOGICAL_AND LOGICAL_OR LOGICAL_NOT
%token BIT_AND BIT_OR BIT_XOR BIT_NOT SHL SHR
%token FOR WHILE DO BREAK CONTINUE
%token IS_EQ NOT_EQ GT LT GTE LTE
%token EQ PLUS_EQ MINUS_EQ DIV_EQ MULT_EQ MOD_EQ
%token IF ELSE SWITCH CASE DEFAULT

%nonassoc IFX
%nonassoc ELSE
%right EQ PLUS_EQ MINUS_EQ DIV_EQ MULT_EQ MOD_EQ //"<<=" ">>=" "&="" "^=" "|="
%left LOGICAL_OR
%left LOGICAL_AND
%left BIT_OR
%left BIT_AND
%left BIT_XOR
%left IS_EQ NOT_EQ
%left LT GT LTE GTE
%left SHL SHR
%left ADD SUB
%left MUL DIV REM
%right PRE_SNGL BIT_NOT LOGICAL_NOT U_PLUS U_MINUS  //unary+-, prefix inc/dec  xd
%left POST_SNGL     // postfix inc/dec xddd


%%

program: program stmt
        |
        ;

stmt:   variable_declaration ';'
    |   variable_init ';'
    |   const_init ';'
    |   expr ';'
    |   WHILE '(' cond_expr ')' stmt
    |   DO stmt WHILE '(' cond_expr ')' ';'
    |   FOR '(' for_expr ';' for_expr ';' eps_expr ')' stmt
    |   FOR '(' variable_declaration ';' for_expr ';' eps_expr ')' stmt
    |   BREAK ';'
    |   CONTINUE ';'
    |   if_stmt
    |   switch_stmt
    |   '{' stmt_list '}'
    |   '{' '}'
    |   ';'
    ;

stmt_list:
          stmt
        | stmt_list stmt
        ;

if_stmt:          IF '(' cond_expr ')' stmt %prec IFX
                | IF '(' cond_expr ')' stmt ELSE stmt;

switch_stmt:    SWITCH '(' cond_expr ')' '{' cases '}';

case:     CASE expr ':' stmt;

default_case:   DEFAULT ':' stmt;

cases:    cases case
        | cases default_case
        |
        ;



// master expression
expr:     '(' expr ')'
        |       ADD expr %prec U_PLUS
        |       SUB expr %prec U_MINUS
        |       single_opr_expr
        |       logic_expr
        |       bit_expr
        |       arithmetic_expr
        |       IDENTIFIER
        |       literal
        |       rel_expr
        |       assign_expr
        ;    

 /* variables & constants */
variable_declaration: data_type IDENTIFIER
                    ;

variable_init: data_type IDENTIFIER EQ expr
                    | data_type IDENTIFIER '(' expr ')'
                    ;

const_init: CONST data_type IDENTIFIER EQ expr
                    | CONST data_type IDENTIFIER '(' expr ')'
                    ;

 /* arithmetic operators */
arithmetic_expr:    expr ADD expr
                |   expr SUB expr
                |   expr MUL expr
                |   expr DIV expr
                |   expr REM expr
                ;

 /* single operators */
single_opr_expr: INC_OPR IDENTIFIER %prec PRE_SNGL
                | IDENTIFIER INC_OPR %prec POST_SNGL
                | DEC_OPR IDENTIFIER %prec PRE_SNGL
                | IDENTIFIER DEC_OPR %prec POST_SNGL
                ;

literal: INTEGER
        | FLOAT
        | BOOL
        | CHAR
        ;

data_type: TYPE_INT
        |  TYPE_FLOAT
        |  TYPE_CHAR
        |  TYPE_BOOL
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

// comparison operators
rel_expr:       expr IS_EQ expr             ; // {$$ = $1 == $3}
        |       expr NOT_EQ expr            ; // {$$ = $1 != $3}     
        |       expr GT expr                ; // {$$ = $1 > $3}
        |       expr LT expr                ; // {$$ = $1 < $3}
        |       expr GTE expr               ; // {$$ = $1 >= $3}
        |       expr LTE expr               ; // {$$ = $1 <= $3}
        ;     

// assignment operators
assign_expr:    expr EQ expr               	
	|	expr PLUS_EQ expr          	
	|       expr MINUS_EQ expr          
	|	expr DIV_EQ expr            
	|	expr MULT_EQ expr          	
	|	expr MOD_EQ expr           	
        ;

cond_expr:   expr
        |   variable_init
        |   const_init
        ;

eps_expr: expr 
        |
        ;

for_expr:   eps_expr
        |   variable_init
        |   const_init
        ;
%%

void yyerror(const char *s) {

// void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}

int main(void) {
    yyparse();
    return 0;
}
