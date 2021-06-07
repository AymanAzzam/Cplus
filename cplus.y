%{
#include <stdio.h>
#include "Stmt.h"
#include "IfStmt.h"
#include "CondExpr.h"
#include "expressions/expressions.h"
int yylex(void);
void yyerror(const char *);
%}

%union {
    int i;
    char c;
    string s;
    float f;
    bool b;
    Stmt* stmt;
    IfStmt* ifStmt;
    CondExpr* condExpr;
    ExprNode* exprNode;
    TypeNode* typeNode;
    ValueNode* valueNode;
}

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


%type <stmt> stmt
%type <ifStmt> if_stmt
%type <condExpr> cond_expr
%type <exprNode> eps_expr expr arithmetic_expr assign_expr rel_expr bit_expr logic_expr single_opr_expr
%type <TypeNode> data_type
%type <ValueNode> literal

%%

program: program stmt
        | program func
        |
        ;

stmt:   multi_var_definition ';' {$$ = new Stmt();}
    |   multi_const_init ';' {$$ = new Stmt();}
    |   expr ';' {$$ = new Stmt();}
    |   WHILE '(' cond_expr ')' stmt {$$ = new Stmt();}
    |   DO stmt WHILE '(' cond_expr ')' ';' {$$ = new Stmt();}
    |   FOR '(' for_expr ';' for_expr ';' eps_expr ')' stmt {$$ = new Stmt();}
    |   FOR '(' variable_declaration ';' for_expr ';' eps_expr ')' stmt {$$ = new Stmt();}
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
expr:     '(' expr ')'                          {$$ = new Expression($2);}
        |       ADD expr %prec U_PLUS           {$$ = new RightOpNode($2, ADD);}
        |       SUB expr %prec U_MINUS          {$$ = new RightOpNode($2, SUB);}
        |       single_opr_expr
        |       logic_expr
        |       bit_expr
        |       arithmetic_expr
        |       IDENTIFIER                      {$$ = new IdentifierNode($1);}
        |       literal                         {$$ = $1;}
        |       rel_expr
        |       assign_expr
        |       func_call                       {$$ = $1;}
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

additional_declaration: ',' IDENTIFIER
                    ;

additional_var_init: ',' IDENTIFIER EQ expr
                | ',' IDENTIFIER '(' expr ')'
                ;

multi_var_definition: multi_var_definition additional_declaration
                | multi_var_definition additional_var_init
                | variable_declaration
                | variable_init
                ;

multi_const_init: multi_const_init additional_var_init
                | const_init
                ;        

 /* arithmetic operators */
arithmetic_expr:    expr ADD expr               {$$ = new TwoOpNode($1, $3, ADD);}
                |   expr SUB expr               {$$ = new TwoOpNode($1, $3, SUB);}
                |   expr MUL expr               {$$ = new TwoOpNode($1, $3, MUL);}
                |   expr DIV expr               {$$ = new TwoOpNode($1, $3, DIV);}
                |   expr REM expr               {$$ = new TwoOpNode($1, $3, REM);}
                ;

 /* single operators */
single_opr_expr: INC_OPR IDENTIFIER %prec PRE_SNGL      {$$ = new RightOpNode($2, INC_OPR);}
                | IDENTIFIER INC_OPR %prec POST_SNGL    {$$ = new LeftOpNode($1, INC_OPR);}
                | DEC_OPR IDENTIFIER %prec PRE_SNGL     {$$ = new RightOpNode($2, DEC_OPR);}
                | IDENTIFIER DEC_OPR %prec POST_SNGL    {$$ = new LeftOpNode($1, DEC_OPR);}
                ;

literal: INTEGER                            {$$ = new ValueNode($1);}
        | FLOAT                             {$$ = new ValueNode($1);}
        | BOOL                              {$$ = new ValueNode($1);}
        | CHAR                              {$$ = new ValueNode($1);}
        ;

data_type: TYPE_INT                         {$$ = new TypeNode(TYPE_INT);}
        |  TYPE_FLOAT                       {$$ = new TypeNode(TYPE_FLOAT);}
        |  TYPE_CHAR                        {$$ = new TypeNode(TYPE_CHAR);}
        |  TYPE_BOOL                        {$$ = new TypeNode(TYPE_BOOL);}
        ;

// logical operators
logic_expr:     expr LOGICAL_AND expr       {$$ = new TwoOpNode($1, $3, LOGICAL_AND);}
        |       expr LOGICAL_OR expr        {$$ = new TwoOpNode($1, $3, LOGICAL_OR);}
        |       LOGICAL_NOT expr            {$$ = new RightOpNode($2, LOGICAL_NOT);}

// bitwise operators
bit_expr:       expr BIT_AND expr           {$$ = new TwoOpNode($1, $3, BIT_AND);}
        |       expr BIT_OR expr            {$$ = new TwoOpNode($1, $3, BIT_OR);}     
        |       expr BIT_XOR expr           {$$ = new TwoOpNode($1, $3, BIT_XOR);}
        |       BIT_NOT expr                {$$ = new RightOpNode($2, BIT_NOT);}
        |       expr SHR expr               {$$ = new TwoOpNode($1, $3, SHR);}
        |       expr SHL expr               {$$ = new TwoOpNode($1, $3, SHL);}

// comparison operators
rel_expr:       expr IS_EQ expr             {$$ = new TwoOpNode($1, $3, IS_EQ);}
        |       expr NOT_EQ expr            {$$ = new TwoOpNode($1, $3, NOT_EQ);}     
        |       expr GT expr                {$$ = new TwoOpNode($1, $3, GT);}
        |       expr LT expr                {$$ = new TwoOpNode($1, $3, LT);}
        |       expr GTE expr               {$$ = new TwoOpNode($1, $3, GTE);}
        |       expr LTE expr               {$$ = new TwoOpNode($1, $3, LTE);}

// assignment operators
assign_expr:    expr EQ expr                {$$ = new TwoOpNode($1, $3, EQ);}
	|	expr PLUS_EQ expr           {$$ = new TwoOpNode($1, $3, PLUS_EQ);}	
	|       expr MINUS_EQ expr          {$$ = new TwoOpNode($1, $3, MINUS_EQ);}
	|	expr DIV_EQ expr            {$$ = new TwoOpNode($1, $3, DIV_EQ);}
	|	expr MULT_EQ expr           {$$ = new TwoOpNode($1, $3, MULT_EQ);}
	|	expr MOD_EQ expr            {$$ = new TwoOpNode($1, $3, MOD_EQ);}
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

identifier:     IDENTIFIER
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


eps_expr: expr                          {$$ = $1;}
        |                               {$$ = NULL;}
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
