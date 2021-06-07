%{
#include <stdio.h>
#include "Stmt.h"
#include "Headers.h"
int yylex(void);
void yyerror(const char *);
%}

%union {
    int i;
    char c;
    char* s;
    float f;
    bool b;
    Stmt* stmt;
    IfStmt* ifStmt;
    CondExpr* condExpr;
    StmtList* stmtList;
    Case* aCase;
    Cases* cases;
    SwitchStmt* switchStmt;
    Expr* expr;
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
%type <stmtList> stmt_list
%type <aCase> case_with_body default_with_body case default_case
%type <cases> top_cases bottom_cases
%type <switchStmt> switch_stmt
%type <expr> expr

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
    |   switch_stmt	{$$ = new Stmt(); $1->execute();}
    |   block {$$ = new Stmt();}
    |   ';'{$$ = new Stmt();}
    ;

block:  '{' stmt_list '}'
        |   '{' '}'
        ;

stmt_list:
	stmt	{$$ = new StmtList($1);}
        | stmt_list stmt	{$$ = $1; $$->push($2);}
        ;

if_stmt:
	IF '(' cond_expr ')' stmt %prec IFX		{$$ = new IfStmt($3, $5);}
	| IF '(' cond_expr ')' stmt ELSE stmt		{$$ = new IfStmt($3, $5, $7);}
	;

switch_stmt:
	SWITCH '(' cond_expr ')' '{' top_cases default_with_body  '}'	{$6->push($7); $$ = new SwitchStmt($6);}
	| SWITCH '(' cond_expr ')' '{' top_cases default_case bottom_cases'}'	{$6->push($7)->push($8); $$ = new SwitchStmt($6);}
	| SWITCH '(' cond_expr ')' '{' bottom_cases '}'	{$$ = new SwitchStmt($6);}
	| SWITCH '(' cond_expr ')' '{' '}'	{$$ = new SwitchStmt();}
	;

top_cases:
	top_cases case			{$$ = $1; $$->push($2);}
	|				{$$ = new Cases();}
	;

// The last case must have body
bottom_cases:
	top_cases case_with_body	{$$ = $1; $$->push($2);}
	;

case:
	case_with_body
	| CASE expr ':'			{$$ = new Case($2);}
	;

case_with_body:
	CASE expr ':' stmt_list		{$$ = new Case($2, $4);}
	;

default_case:
	default_with_body
	| DEFAULT ':'			{$$ = new Case();}
	;

default_with_body:
	DEFAULT ':' stmt_list		{$$ = new Case($3);}
	;



// master expression
expr:     '(' expr ')' {$$=new Expr();}
        |       ADD expr %prec U_PLUS {$$=new Expr();}
        |       SUB expr %prec U_MINUS {$$=new Expr();}
        |       single_opr_expr {$$=new Expr();}
        |       logic_expr {$$=new Expr();}
        |       bit_expr {$$=new Expr();}
        |       arithmetic_expr {$$=new Expr();}
        |       IDENTIFIER {$$=new Expr();}
        |       literal {$$=new Expr();}
        |       rel_expr {$$=new Expr();}
        |       assign_expr {$$=new Expr();}
        |       func_call {$$=new Expr();}
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
