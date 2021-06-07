%{
#include <stdio.h>
#include <vector>

#include "Headers.h"

extern int yylineno;

int yylex(void);
void yyerror(const char *);
%}


%union {
    int i;
    char c;
    char* s;
    float f;
    bool b;

    Node* placeholder;

    Stmt* stmt;
    IfStmt* ifStmt;
    CondExpr* condExpr;
    ForExpr* forExpr;
    EpsExpr* epsExpr;
    For* forLoop;
    While* whileLoop;
    DoWhile* doWhileLoop;

    VarDec* declare;
    VarInit* init;
    vector<Node*> list;
}

%start program

%token <i> INTEGER
%token <f> FLOAT
%token <c> CHAR
%token <b> BOOL
%token <s> IDENTIFIER
%token TYPE_INT TYPE_FLOAT TYPE_CHAR TYPE_BOOL TYPE_VOID
%token CONST RETURN
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

//everything here should be removed by the end
// %type <placeholder> variable_declaration

%type <stmt> stmt
%type <ifStmt> if_stmt
%type <condExpr> cond_expr
%type <forExpr> for_expr extended_for_expr
%type <epsExpr> eps_expr

%type <declare> variable_declaration
%type <init> variable_init
%type <list> multi_var_definition

%%

program: program stmt
        | program func
        |                       {/*$0->execute(); delete $0;*/;}
        ;

stmt:   multi_var_definition ';' {$$ = new Stmt();}
    |   multi_const_init ';' {$$ = new Stmt();}
    |   expr ';' {$$ = new Stmt();}
    |   WHILE '(' cond_expr ')' stmt            {$$ = new While($3, $5); $$->execute(); printf("%i", yylineno);}
    |   DO stmt WHILE '(' cond_expr ')' ';'     {$$ = new DoWhile($2, $5); $$->execute(); printf("%i", yylineno);}
    |   FOR '(' extended_for_expr ';' for_expr ';' eps_expr ')' stmt     {$$ = new For($3, $5, $7, $9); $$->execute(); printf("%i", yylineno);}
    |   BREAK ';'{$$ = new Stmt();}
    |   CONTINUE ';'{$$ = new Stmt();}
    |   return_stmt ';'{$$ = new Stmt();}
    |   if_stmt		{$$ = new Stmt(); $1->execute();}
    |   switch_stmt{$$ = new Stmt();}
    |   block {$$ = new Stmt();}
    |   ';'{$$ = new Stmt();}
    ;

block:  '{' stmt_list '}'
        |   '{' '}'
        ;

stmt_list:
          stmt
        | stmt_list stmt
        ;

if_stmt:
	IF '(' cond_expr ')' stmt %prec IFX		{$$ = new IfStmt($3, $5);}
	| IF '(' cond_expr ')' stmt ELSE stmt		{$$ = new IfStmt($3, $5, $7);}
	;

switch_stmt:      SWITCH '(' cond_expr ')' '{' cases '}'
                | SWITCH '(' cond_expr ')' '{' cases default_case cases'}';

case:     CASE expr ':' stmt
        | CASE expr ':' case;

default_case:   DEFAULT ':' stmt;

cases:    cases case
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
        |       func_call
        ;    

 /* variables & constants */
variable_declaration: data_type IDENTIFIER      {$$ = new VarDec($1, $2, yylineno);}
                ;

variable_init: data_type IDENTIFIER EQ expr     {$$ = new VarDec($1, $2, $4, yylineno);}
        | data_type IDENTIFIER '(' expr ')'     {$$ = new VarDec($1, $2, $4, yylineno);}
        ;

const_init: CONST data_type IDENTIFIER EQ expr
        | CONST data_type IDENTIFIER '(' expr ')'
        ;

additional_declaration: ',' IDENTIFIER
                    ;

additional_var_init: ',' IDENTIFIER EQ expr
                | ',' IDENTIFIER '(' expr ')'
                ;

multi_var_definition: multi_var_definition additional_declaration       {$$ = $1; $1->push_back($2);}
                | multi_var_definition additional_var_init              {$$ = $1; $1->push_back($2);}
                | variable_declaration  {$$ = new vector<Node*>();}
                | variable_init         {$$ = new vector<Node*>();}
                ;

multi_const_init: multi_const_init additional_var_init
                | const_init
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

// bitwise operators
bit_expr:       expr BIT_AND expr           ; // {$$ = $1 & $3}
        |       expr BIT_OR expr            ; // {$$ = $1 | $3}     
        |       expr BIT_XOR expr           ; // {$$ = $1 ^ $3}
        |       BIT_NOT expr                ; // {$$ = ~$2}
        |       expr SHR expr               ; // {$$ = $1 >> $3}
        |       expr SHL expr               ; // {$$ = $1 << $3}

// comparison operators
rel_expr:       expr IS_EQ expr             ; // {$$ = $1 == $3}
        |       expr NOT_EQ expr            ; // {$$ = $1 != $3}     
        |       expr GT expr                ; // {$$ = $1 > $3}
        |       expr LT expr                ; // {$$ = $1 < $3}
        |       expr GTE expr               ; // {$$ = $1 >= $3}
        |       expr LTE expr               ; // {$$ = $1 <= $3}

// assignment operators
assign_expr:    expr EQ expr               	
	|	expr PLUS_EQ expr          	
	|       expr MINUS_EQ expr          
	|	expr DIV_EQ expr            
	|	expr MULT_EQ expr          	
	|	expr MOD_EQ expr           	
        ;

cond_expr:   expr		{$$ = new CondExpr();}
        |   variable_init	{$$ = new CondExpr();}
        |   const_init		{$$ = new CondExpr();}
        ;

// functions

func:           func_header block
        ;

func_header:    TYPE_VOID IDENTIFIER '(' paramater ')'
        |       data_type IDENTIFIER '(' paramater ')'
        ;

paramater:      /* epsilon */                 	
        |       variable_declaration   
        |       variable_init                    	
        |       parameter_ext ',' variable_declaration
        |       parameter_ext ',' variable_init
        ;

parameter_ext:  variable_declaration      
        |       variable_init                	
        |       parameter_ext ',' variable_declaration  
        |       parameter_ext ',' variable_init     	
        ;

func_call:      IDENTIFIER '(' args ')'              	
        ;

args:           /* epsilon */                  	
        |       expr                     	
        |       args_ext ',' expr         
        ;

args_ext:       expr                     	
        |       args_ext ',' expr         
        ;

return_stmt:    RETURN expr              	
        |       RETURN                         	
        ;


eps_expr: expr  {$$ = new EpsExpr();}
        |       {$$ = nullptr;}
        ;

extended_for_expr: for_expr                     {$$ = new ForExpr(nullptr);}
                 | variable_declaration         {$$ = new ForExpr(nullptr);}

for_expr:   eps_expr            {$$ = new ForExpr(nullptr);}
        |   variable_init       {$$ = new ForExpr(nullptr);}
        |   const_init          {$$ = new ForExpr(nullptr);}
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
