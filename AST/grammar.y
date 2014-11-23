%{
  #include "llvm/IR/Verifier.h"
  #include "llvm/IR/DerivedTypes.h"
  #include "llvm/IR/IRBuilder.h"
  #include "llvm/IR/LLVMContext.h"
  #include "llvm/IR/Module.h"
  #include <iostream>
  #include <string>
  #include <stdlib.h>
  #include <map>
  #include <list>
  #include <math.h>
  #include "AST.h"
  using namespace std;
  using namespace llvm;

  int yylex();
  void yyerror(char * s);

  program* root;
  int line_num = 1;

  Module *TheModule;
  
%}

%union{
    char *id, *type;
    char *string_literal, *char_literal;   // NOTE : This will come with quotes
    int int_literal;
    bool bool_literal;
    program* prog;
    method_decl_node* method_decl;
    list<method_decl_node*> *method_decl_list;
    list<argument_node*> *arg_list;
    
    var_decl_node* var_decl;
    list<var_decl_node*> *var_decl_list;
    
    list<string> *id_list;
    field_decl_id_node* field_decl_id;
    list<field_decl_id_node*> *field_decl_id_list;
    
    field_decl_node *field_decl;
    list<field_decl_node*> *field_decl_list;
    
    block_node* block;
    list<statement_node*> *statement_list;
    statement_node *statement;
    
    location_node *location;
    assign_op_node *assign_op;
    
    expr_node *expr;
    method_call_node* method_call;
    list<expr_node*> *expr_list;
    callout_arg_node *callout_arg;
    list<callout_arg_node*> *callout_arg_list;
    literal_node* literal;
}

%token <id> IDENTIFIER
%token CLASS
%token PROGRAM
%token <type> VOID
%token <type> TYPE
%token IF
%token ELSE
%token <int_literal> INT_LITERAL
%token FOR
%token RETURN
%token BREAK
%token CONTINUE
%token PLUSEQUAL
%token MINUSEQUAL
%token <bool_literal> BOOL_LITERAL
%token LESSEQUAL
%token GTEQUAL
%token EQEQUAL
%token NOTEQUAL
%token COND_AND
%token COND_OR
%token <char_literal> CHAR_LITERAL
%token <string_literal> STRING_LITERAL
%token CALLOUT

%nonassoc "empty"
%nonassoc TYPE

%left COND_OR
%left COND_AND
%left EQEQUAL NOTEQUAL
%left '<' LESSEQUAL GTEQUAL '>'
%left '+' '-'
%left '*' '/' '%'
%nonassoc "not"
%nonassoc "negate"

%type <prog>program
%type <method_decl>method_decl
%type <method_decl_list>method_decl_star
%type <arg_list>comma_type_id
%type <var_decl>var_decl
%type <var_decl_list>var_decl_star
%type <id_list> comma_id
%type <block>block
%type <statement_list>statement_star
%type <statement>statement
%type <location>location
%type <assign_op>assign_op
%type <expr>expr
%type <method_call>method_call
%type <expr_list>comma_expr
%type <callout_arg>callout_arg
%type <callout_arg_list>comma_callout_arg
%type <literal>literal
%type <field_decl_id>simple_or_array
%type <field_decl_id_list>comma_simple_or_array
%type <field_decl> field_decl
%type <field_decl_list> field_decl_star
%%


program: CLASS PROGRAM '{' field_decl_star method_decl_star '}' {
                                                                    printf("In program rule\n");
                                                                    $$ = new program($4, $5);
                                                                    root = $$;
                                                                }

/* COMPLETED */
method_decl_star: /*empty string */                             {$$ = new list<method_decl_node*>();}
                | method_decl method_decl_star                  {
                                                                    $2->push_front($1);
                                                                    $$ = $2;
                                                                }
/* COMPLETED */
method_decl: VOID IDENTIFIER '(' ')' block                              {
                                                                    list<argument_node*> *arg_list = new list<argument_node*>();
                                                                    $$ = new method_decl_node($1, $2, arg_list, $5);
                                                                }
           | VOID IDENTIFIER '(' TYPE IDENTIFIER comma_type_id ')' block        {
                                                                    argument_node* a = new argument_node($4, $5);
                                                                    $6->push_front(a);

                                                                    $$ = new method_decl_node($1, $2, $6, $8);
                                                                }
           | TYPE IDENTIFIER '(' TYPE IDENTIFIER comma_type_id ')' block        {
                                                                    argument_node* a = new argument_node($4, $5);
                                                                    $6->push_front(a);
                                                                    
                                                                    $$ = new method_decl_node($1, $2, $6, $8);
                                                                }
           | TYPE IDENTIFIER '(' ')' block                              {
                                                                    list<argument_node*> *arg_list = new list<argument_node*>();
                                                                    $$ = new method_decl_node($1, $2, arg_list, $5);
                                                                }
           ;

/* COMPLETED */
comma_type_id: /* empty string */                               {$$ = new list<argument_node*>();}
             | ',' TYPE IDENTIFIER comma_type_id                        {
                                                                    argument_node* a = new argument_node($2, $3);
                                                                    $4->push_front(a);
                                                                    $$ = $4;
                                                                }

/* COMPLETED */
block: '{' var_decl_star statement_star '}'                     {
                                                                    $$ = new block_node($2, $3);
                                                                }

/* COMPLETED */
var_decl_star: /* empty string */                               {$$ = new list<var_decl_node*>();}
             | var_decl var_decl_star                           {
                                                                    $2->push_front($1);
                                                                    $$ = $2;
                                                                }

/* COMPLETED */
var_decl: TYPE IDENTIFIER comma_id ';'                          {
                                                                    $3->push_front($2);
                                                                    $$ = new var_decl_node($1, $3);
                                                                }

/* COMPLETED */
statement_star: /* empty string */                              {$$ = new list<statement_node*>();}
              | statement statement_star                        {
                                                                    $2->push_front($1);
                                                                    $$ = $2;
                                                                }
statement: location assign_op expr ';'                          {$$ = new assignment_stmt($1, $2, $3);}
          /* DONE */
         | method_call ';'                                      {$$ = new method_call_stmt($1);}
         | IF '(' expr ')' block                                {$$ = new if_stmt($3, $5);}
         | IF '(' expr ')' block ELSE block                     {$$ = new if_else_stmt($3, $5, $7);}
         | FOR IDENTIFIER '=' expr ',' expr block                       {$$ = new for_stmt($2, $4, $6, $7);}
         | RETURN ';'                                           {$$ = new return_stmt();}
         | RETURN expr ';'                                      {$$ = new return_expr_stmt($2);}
         | BREAK ';'                                            {$$ = new break_stmt();}
         | CONTINUE ';'                                         {$$ = new continue_stmt();}
         | block                                                {$$ = new block_stmt($1);}                                        

location: IDENTIFIER                                                    {$$ = new memory_loc($1);}
        | IDENTIFIER '[' expr ']'                                       {$$ = new array_loc($1, $3);}

assign_op: '='                                                  {$$ = new assign_op_node('=');}
         | PLUSEQUAL                                            {$$ = new assign_op_node(PLUSEQUAL);}
         | MINUSEQUAL                                           {$$ = new assign_op_node(MINUSEQUAL);}

expr: location                                                  {$$ = new location_expr_node($1);}
    /* DONE */
    | method_call                                               {$$ = new method_call_expr_node($1);}
    /* DONE */
    | literal                                                   {$$ = new literal_expr_node($1);}
    /* DONE */
    | '(' expr ')'                                              {$$ = $2;}
    /* DONE */
    | '!' expr %prec "not"                                      {$$ = new not_expr_node($2);}
    /* DONE */
    | '-' expr %prec "negate"                                   {$$ = new negate_expr_node($2);}
    /* DONE */
    | expr '*' expr                                             {$$ = new product_node($1, $3);} 
    /* DONE */
    | expr '/' expr                                             {$$ = new division_node($1, $3);}
    /* DONE */
    | expr '%' expr                                             {$$ = new modulus_node($1, $3);}
    /* DONE */
    | expr '+' expr                                             {$$ = new addition_node($1, $3);}
    /* DONE */
    | expr '-' expr                                             {$$ = new subtraction_node($1, $3);}
    /* DONE */
    | expr '<' expr                                             {$$ = new less_node($1, $3);}                                            
    /* DONE */
    | expr LESSEQUAL expr                                       {$$ = new less_eq_node($1, $3);}
    /* DONE */
    | expr GTEQUAL expr                                         {$$ = new greater_eq_node($1, $3);}   
    /* DONE */
    | expr '>' expr                                             {$$ = new greater_node($1, $3);}
    /* DONE */
    | expr EQEQUAL expr                                         {$$ = new equal_equal_node($1, $3);}
    /* DONE */
    | expr NOTEQUAL expr                                        {$$ = new not_equal_node($1, $3);}
    | expr COND_AND expr                                        {$$ = new cond_and_node($1, $3);}
    | expr COND_OR expr                                         {$$ = new cond_or_node($1, $3);}

/* COMPLETED */
comma_expr: /* empty string */                                  {$$ = new list<expr_node*>();}
          | ',' expr comma_expr                                 {
                                                                    $3->push_front($2);
                                                                    $$ = $3;
                                                                }
method_call: IDENTIFIER '(' ')'       /* DONE */                            {
                                                                                $$ = new method_call_by_id($1, 
                                                                                new list<expr_node*>());
                                                                            }
          /* DONE */
          | IDENTIFIER '(' expr comma_expr ')'                              {
                                                                                $4->push_front($3);
                                                                                $$ = new method_call_by_id($1, $4);
                                                                            }
          | CALLOUT '(' STRING_LITERAL ')'                                  {
                                                                                $$ = new method_call_by_callout($3, 
                                                                                    new list<callout_arg_node*>());
                                                                            }
          | CALLOUT '(' STRING_LITERAL ',' callout_arg comma_callout_arg ')'{
                                                                                $6->push_front($5);
                                                                                $$ = new method_call_by_callout($3, $6);
                                                                            }


callout_arg: expr                                                           {$$ = new callout_arg_expr($1);}
           | STRING_LITERAL                                                 {$$ = new callout_arg_string($1);}


comma_callout_arg: /* empty string */                                       {$$ = new list<callout_arg_node*>();}
                 | ',' callout_arg comma_callout_arg                        {
                                                                                $3->push_front($2);
                                                                                $$ = $3;
                                                                            }
                 ;

/* COMPLETED */
literal: INT_LITERAL                                                {$$ = new int_literal_node($1);}
       | CHAR_LITERAL                                               {$$ = new char_literal_node($1);}
       | BOOL_LITERAL                                               {$$ = new bool_literal_node($1);}


/*
bin_op: arith_op | rel_op | eq_op | cond_op;
arith_op: '+' | '-' | '*' | '/' | '%';
rel_op: '<' | '>' | LESSEQUAL | GTEQUAL;
eq_op: NOTEQUAL | EQEQUAL;
cond_op: COND_OP;
*/

field_decl_star: /* empty string */ %prec "empty"                   {$$ = new list<field_decl_node*>();}
               | field_decl_star field_decl                         {
                                                                            $1->push_back($2);
                                                                            $$ = $1;
                                                                    }

field_decl: TYPE simple_or_array comma_simple_or_array';'          {
                                                                            $3->push_front($2);
                                                                            $$ = new field_decl_node($1, $3);
                                                                    }

simple_or_array: IDENTIFIER                                                 {$$ = new field_decl_id_simple($1);}
               | IDENTIFIER '[' INT_LITERAL ']'                             {$$ = new field_decl_id_array($1, $3);}
               ;

comma_simple_or_array: /* empty string */                           {$$ = new list<field_decl_id_node*>();}
                     | ',' simple_or_array comma_simple_or_array    {
                                                                        $3->push_front($2); 
                                                                        $$ = $3;
                                                                    }
                     ;

comma_id: /* empty string */                                        {$$ = new list<string>();}
        | ',' IDENTIFIER comma_id                                           {
                                                                        $3->push_front($2);
                                                                        $$ = $3;
                                                                    }
%%

int main()
{
  //  yydebug = 1;
  LLVMContext &Context = getGlobalContext();
  TheModule = new Module("Decaf Compiler", Context);

  yyparse();
  root->evaluate();
  root->Codegen();

  // Print out all of the generated code.
  TheModule->dump();
}

void yyerror(char * s)
{
  //fprintf(stderr, "line %d: %s\n", line_num, s);
  printf("Error %d: %s", line_num, s);
}

