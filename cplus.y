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
    
    ExprNode* exprNode;
    TypeNode* typeNode;
    ValueNode* valueNode;
    IdentifierNode* identifierNode;
    ForExpr* forExpr;
    EpsExpr* epsExpr;
    For* forLoop;
    While* whileLoop;
    DoWhile* doWhileLoop;
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

%type <stmt> stmt
%type <ifStmt> if_stmt
%type <condExpr> cond_expr
%type <exprNode> eps_expr expr arithmetic_expr assign_expr rel_expr bit_expr logic_expr single_opr_expr
%type <typeNode> data_type
%type <valueNode> literal
%type <identifierNode> identifier
%type <forExpr> for_expr extended_for_expr
// %type <epsExpr> eps_expr

%%

program: program stmt
        | program func
        |                       {/*$0->execute(); delete $0;*/;}
        ;

stmt:   multi_var_definition ';' {$$ = new Stmt();}
    |   multi_const_init ';' {$$ = new Stmt();}
    |   expr ';' {$$ = new Stmt();}
    |   WHILE '(' cond_expr ')' stmt            {$$ = new While($3, $5); $$->execute();}
    |   DO stmt WHILE '(' cond_expr ')' ';'     {$$ = new DoWhile($2, $5); $$->execute();}
    |   FOR '(' extended_for_expr ';' for_expr ';' eps_expr ')' stmt     {$$ = new For($3, $5, $7, $9); $$->execute();}
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
        |       ADD expr %prec U_PLUS           {Operator o = _ADD; $$ = new RightOpNode($2, o);}
        |       SUB expr %prec U_MINUS          {Operator o = _SUB; $$ = new RightOpNode($2, o);}
        |       single_opr_expr
        |       logic_expr
        |       bit_expr
        |       arithmetic_expr
        |       identifier                      {$$ = $1;}
        |       literal                         {$$ = $1;}
        |       rel_expr
        |       assign_expr
        |       func_call                       {$$ = new ExprNode();}
        ;    

 /* variables & constants */
variable_declaration: data_type IDENTIFIER
                ;

variable_init: data_type IDENTIFIER EQ expr
        // | data_type IDENTIFIER '(' expr ')'
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
arithmetic_expr:    expr ADD expr               {Operator o = _ADD; $$ = new TwoOpNode($1, $3, o);}
                |   expr SUB expr               {Operator o = _SUB; $$ = new TwoOpNode($1, $3, o);}
                |   expr MUL expr               {Operator o = _MUL; $$ = new TwoOpNode($1, $3, o);}
                |   expr DIV expr               {Operator o = _DIV; $$ = new TwoOpNode($1, $3, o);}
                |   expr REM expr               {Operator o = _REM; $$ = new TwoOpNode($1, $3, o);}
                ;

 /* single operators */
single_opr_expr: INC_OPR identifier %prec PRE_SNGL      {Operator o = _INC_OPR; $$ = new RightOpNode($2, o);}
                | identifier INC_OPR %prec POST_SNGL    {Operator o = _INC_OPR; $$ = new LeftOpNode($1, o);}
                | DEC_OPR identifier %prec PRE_SNGL     {Operator o = _DEC_OPR; $$ = new RightOpNode($2, o);}
                | identifier DEC_OPR %prec POST_SNGL    {Operator o = _DEC_OPR; $$ = new LeftOpNode($1, o);}
                ;

literal: INTEGER                            {DataType t = _TYPE_INT; $$ = new ValueNode(to_string($1), t);}
        | FLOAT                             {DataType t = _TYPE_FLOAT; $$ = new ValueNode(to_string($1), t);}
        | BOOL                              {DataType t = _TYPE_BOOL; $$ = new ValueNode(to_string($1), t);}
        | CHAR                              {DataType t = _TYPE_CHAR; $$ = new ValueNode(to_string($1), t);}
        ;

data_type: TYPE_INT                         {DataType t = _TYPE_INT; $$ = new TypeNode(t);}
        |  TYPE_FLOAT                       {DataType t = _TYPE_FLOAT; $$ = new TypeNode(t);}
        |  TYPE_CHAR                        {DataType t = _TYPE_CHAR; $$ = new TypeNode(t);}
        |  TYPE_BOOL                        {DataType t = _TYPE_BOOL; $$ = new TypeNode(t);}
        ;

// logical operators
logic_expr:     expr LOGICAL_AND expr       {Operator o = _LOGICAL_AND; $$ = new TwoOpNode($1, $3, o);}
        |       expr LOGICAL_OR expr        {Operator o = _LOGICAL_OR; $$ = new TwoOpNode($1, $3, o);}
        |       LOGICAL_NOT expr            {Operator o = _LOGICAL_NOT; $$ = new RightOpNode($2, o);}

// bitwise operators
bit_expr:       expr BIT_AND expr           {Operator o = _BIT_AND; $$ = new TwoOpNode($1, $3, o);}
        |       expr BIT_OR expr            {Operator o = _BIT_OR; $$ = new TwoOpNode($1, $3, o);}     
        |       expr BIT_XOR expr           {Operator o = _BIT_XOR; $$ = new TwoOpNode($1, $3, o);}
        |       BIT_NOT expr                {Operator o = _BIT_NOT; $$ = new RightOpNode($2, o);}
        |       expr SHR expr               {Operator o = _SHR; $$ = new TwoOpNode($1, $3, o);}
        |       expr SHL expr               {Operator o = _SHL; $$ = new TwoOpNode($1, $3, o);}

// comparison operators
rel_expr:       expr IS_EQ expr             {Operator o = _IS_EQ; $$ = new TwoOpNode($1, $3, o);}
        |       expr NOT_EQ expr            {Operator o = _NOT_EQ; $$ = new TwoOpNode($1, $3, o);}     
        |       expr GT expr                {Operator o = _GT; $$ = new TwoOpNode($1, $3, o);}
        |       expr LT expr                {Operator o = _LT; $$ = new TwoOpNode($1, $3, o);}
        |       expr GTE expr               {Operator o = _GTE; $$ = new TwoOpNode($1, $3, o);}
        |       expr LTE expr               {Operator o = _LTE; $$ = new TwoOpNode($1, $3, o);}

// assignment operators
assign_expr:    expr EQ expr                {Operator o = _EQ; $$ = new TwoOpNode($1, $3, o);}
	|	expr PLUS_EQ expr           {Operator o = _PLUS_EQ; $$ = new TwoOpNode($1, $3, o);}	
	|       expr MINUS_EQ expr          {Operator o = _MINUS_EQ; $$ = new TwoOpNode($1, $3, o);}
	|	expr DIV_EQ expr            {Operator o = _DIV_EQ; $$ = new TwoOpNode($1, $3, o);}
	|	expr MULT_EQ expr           {Operator o = _MULT_EQ; $$ = new TwoOpNode($1, $3, o);}
	|	expr MOD_EQ expr            {Operator o = _MOD_EQ; $$ = new TwoOpNode($1, $3, o);}
        ;

cond_expr:   expr		{$$ = new CondExpr();}
        |   variable_init	{$$ = new CondExpr();}
        |   const_init		{$$ = new CondExpr();}
        ;

// functions

func:           func_header block
        ;

func_header:    TYPE_VOID identifier '(' paramater ')'
        |       data_type identifier '(' paramater ')'
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

func_call:      identifier '(' args ')'              	
        ;

identifier:     IDENTIFIER              {$$ = new IdentifierNode($1);}
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
        |                               {$$ = nullptr;}
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
