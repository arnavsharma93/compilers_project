#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <list>
#include "AST.h"

using namespace std;

int level = 0;
void print_tabs(int levels)
{
	for(int i=0;i<levels;i++)
		cout << "\t";
}

assign_op_node::assign_op_node(int op)
{
	// This stores the char id or the macro id of the assign op.
	this->op = op;
}

/* COMPLETED */
void assign_op_node::evaluate()
{
	print_tabs(level);
	
	cout << "Assign_Op" << endl;
}

/*********************** Var Decl Nodes ************************/
var_decl_node::var_decl_node(string type, list<string> *id_list){
	this->type = type;
	this->id_list = id_list;
}
/* COMPLETED */
void var_decl_node::evaluate()
{
	print_tabs(level);
	level++;
	cout << "var_decl_node TYPE " << type << " ";

	for(list<string>::iterator it = id_list->begin(); it!= id_list->end(); ++it)
		cout << *it << " ";
	cout << endl;

	level--;
}
/***************************************************************/

/*********************** Literal Nodes *************************/
int_literal_node::int_literal_node(int value){
	this->value = value;
}
/* COMPLETED */
void int_literal_node::evaluate()
{
	print_tabs(level);
	level++;
	cout << "Int literal VALUE " << value << endl;
	level--;
}
char_literal_node::char_literal_node(string value){
	this->value = value;
}
/* COMPLETED */
void char_literal_node::evaluate()
{
	print_tabs(level);
	level++;
	cout << "Char literal VALUE " << value << endl;
	level--;	
}
bool_literal_node::bool_literal_node(bool value){
	this->value = value;
}
/* COMPLETED */
void bool_literal_node::evaluate()
{
	print_tabs(level);
	level++;
	cout << "Bool literal VALUE " << value << endl;
	level--;
}
/**************************************************************/

/*********************** Location Nodes ************************/
array_loc::array_loc(string id, expr_node *expr)
{
	this->id = id;
	this->expr = expr;
}
/* COMPLETED */
void array_loc::evaluate()
{
	print_tabs(level);
	level++;
	cout << "array_location ID " << id << endl;

	print_tabs(level-1);
	cout << "array_loc_expr" << endl;
	expr->evaluate();

	level--;
}

memory_loc::memory_loc(string id)
{
	this->id = id;
}

/* COMPLETED */
void memory_loc::evaluate()
{
	print_tabs(level);
	level++;
	cout << "memory_loc ID " << id << endl;
	level--;
}
/**************************************************************/

/*********************** Expression Nodes *********************/
literal_expr_node::literal_expr_node(literal_node *literal)
{
	this->literal = literal;
}
/* COMPLETED */
void literal_expr_node::evaluate()
{
	print_tabs(level);
	level++;
	cout << "literal_expr_node" << endl;
	literal->evaluate();
	level--;
}

method_call_expr_node::method_call_expr_node(method_call_node *method_call)
{
	this->method_call = method_call;
}
/* COMPLETED */
void method_call_expr_node::evaluate()
{
	print_tabs(level);
	level++;
	cout << "method_call_expr_node" << endl;
	method_call->evaluate();
	level--;
}

operator_node::operator_node(expr_node *left, expr_node *right)
{
	//printf("\t\t\t\toperator_node\n");
	this->left = left;
	this->right = right;
}
/* COMPLETED */
void operator_node::evaluate()
{
	print_tabs(level);
	level++;
	cout << "operator_node" << endl;
	
	print_tabs(level-1);
	cout << "left expression" << endl;	
	left->evaluate();

	print_tabs(level-1);
	cout << "right expression" << endl;	
	right->evaluate();

	level--;
}

not_expr_node::not_expr_node(expr_node *expr)
{
	this->expr = expr;
}
/* COMPLETED */
void not_expr_node::evaluate()
{
	print_tabs(level);
	level++;
	cout << "! expr_node" << endl;
	expr->evaluate();
	level--;
}

negate_expr_node::negate_expr_node(expr_node *expr)
{
	this->expr = expr;
}
/* COMPLETED */
void negate_expr_node::evaluate()
{
	print_tabs(level);
	level++;
	cout << "- expr_node" << endl;
	expr->evaluate();
	level--;
}

location_expr_node::location_expr_node(location_node* location)
{
	this->location = location;
}
/* COMPLETED */
void location_expr_node::evaluate()
{
	print_tabs(level);
	level++;
	cout << "location_expr_node" << endl;
	location->evaluate();
	level--;
}

product_node::product_node(expr_node *left, expr_node *right): operator_node(left, right){
}
division_node::division_node(expr_node *left, expr_node *right): operator_node(left, right){
}
modulus_node::modulus_node(expr_node *left, expr_node *right): operator_node(left, right){
}
addition_node::addition_node(expr_node *left, expr_node *right): operator_node(left, right){
}
subtraction_node::subtraction_node(expr_node *left, expr_node *right): operator_node(left, right){
}
less_node::less_node(expr_node *left, expr_node *right): operator_node(left, right){
}
less_eq_node::less_eq_node(expr_node *left, expr_node *right): operator_node(left, right){
}
greater_node::greater_node(expr_node *left, expr_node *right): operator_node(left, right){
}
greater_eq_node::greater_eq_node(expr_node *left, expr_node *right): operator_node(left, right){
}
equal_equal_node::equal_equal_node(expr_node *left, expr_node *right): operator_node(left, right){
}
not_equal_node::not_equal_node(expr_node *left, expr_node *right): operator_node(left, right){
}
cond_and_node::cond_and_node(expr_node *left, expr_node *right): operator_node(left, right){
}
cond_or_node::cond_or_node(expr_node *left, expr_node *right): operator_node(left, right){
}
/**************************************************************/

/*********************** Statement Nodes ************************/
method_call_stmt::method_call_stmt(method_call_node* method_call)
{
	this->method_call = method_call;
}
/* COMPLETED */
void method_call_stmt::evaluate()
{
	print_tabs(level);
	level++;
	cout << "METHOD CALL STATEMENT " << endl;
	method_call->evaluate();
	level--;
}

assignment_stmt::assignment_stmt(location_node *location, assign_op_node * assign_op, expr_node *expr)
{
	this->location = location;
	this->assign_op = assign_op;
	this->expr = expr;
}
void assignment_stmt::evaluate()
{
	print_tabs(level);
	level++;
	cout << "assignment_stmt " << endl;	
	level--;	
}

if_stmt::if_stmt(expr_node *expr, block_node *block)
{
	this->expr = expr;
	this->block = block;
}

/* COMPLETED */
void if_stmt::evaluate()
{
	print_tabs(level);
	level++;
	cout << "IF Statement " << endl;

	print_tabs(level-1);
	cout << "IF Expr" << endl;
	expr->evaluate();

	print_tabs(level-1);
	cout << "IF Block" << endl;
	block->evaluate();
	level--;
}

if_else_stmt::if_else_stmt(expr_node *expr, block_node *if_block, block_node *else_block)
{
	this->expr = expr;
	this->if_block = if_block;
	this->else_block = else_block;
}

/* COMPLETED */
void if_else_stmt::evaluate()
{
	print_tabs(level);
	level++;
	cout << "IF else Statement " << endl;

	print_tabs(level-1);
	cout << "IF Expr" << endl;
	expr->evaluate();
	print_tabs(level-1);
	cout << "IF Block" << endl;
	if_block->evaluate();
	print_tabs(level-1);
	cout << "ELSE Block" << endl;
	else_block->evaluate();

	level--;
}

for_stmt::for_stmt(string id, expr_node *init_expr, expr_node *term_expr, block_node *block){
	this->id = id;
	this->init_expr = init_expr;
	this->term_expr = term_expr;
	this->block = block;

}

/* COMPLETED */
void for_stmt::evaluate()
{
	print_tabs(level);
	level++;
	cout << "FOR Statement " << endl;
	
	print_tabs(level-1);
	cout << "init_expr" << endl;
	init_expr->evaluate();

	print_tabs(level-1);
	cout << "terminal_expr" << endl;
	term_expr->evaluate();

	block->evaluate();
	level--;
}

return_stmt::return_stmt()
{
	// Do nothing
}

/* COMPLETED */
void return_stmt::evaluate()
{
	print_tabs(level);
	level++;
	cout << "Return Statement " << endl;
	level--;
}

return_expr_stmt::return_expr_stmt(expr_node *expr){
	this->expr = expr;
}

/* COMPLETED */
void return_expr_stmt::evaluate()
{
	print_tabs(level);
	level++;
	cout << "Return EXPR Statement " << endl;
	expr->evaluate();
	level--;
}

break_stmt::break_stmt()
{
	// Do nothing
}

/* COMPLETED */
void break_stmt::evaluate()
{
	print_tabs(level);
	level++;
	cout << "Break Statement " << endl;
	level--;
}

continue_stmt::continue_stmt()
{
	// Do nothing
}

/* COMPLETED */
void continue_stmt::evaluate()
{
	print_tabs(level);
	level++;
	cout << "Continue Statement " << endl;
	level--;
}

block_stmt::block_stmt(block_node *block)
{
	this->block = block;
}
/* COMPLETED */
void block_stmt::evaluate()
{
	print_tabs(level);
	level++;
	cout << "Block Statement " << endl;
	block->evaluate();
	level--;
}
/**************************************************************/

callout_arg_expr::callout_arg_expr(expr_node *expr)
{
	this->expr = expr;
}
/* COMPLETED */
void callout_arg_expr::evaluate()
{
	print_tabs(level);
	level++;
	cout << "callout_arg using expr" << endl;
	expr->evaluate();
	level--;
}
callout_arg_string::callout_arg_string(string arg)
{
	this->arg = arg;
}

/* COMPLETED */
void callout_arg_string::evaluate()
{
	print_tabs(level);
	level++;
	cout << "callout_arg using string " << arg << endl;
	level--;
}

/********************** METHOD CALL Nodes *********************************/
method_call_by_id::method_call_by_id(string id, list<expr_node*> *param_list){
	this->id = id;
	this->param_list = param_list;
}

/* COMPLETED */
void method_call_by_id::evaluate()
{
	print_tabs(level);
	level++;
	cout << "method_call_by_id ID " << id << " with "<< param_list->size() << " parameters" << endl;
	for(list<expr_node*>::iterator it = param_list->begin(); it!=param_list->end(); ++it)
		(*it)->evaluate();
	level--;
}
method_call_by_callout::method_call_by_callout(string name, list<callout_arg_node*> *callout_args)
{
	this->name = name;
	this->callout_args = callout_args;
}
/* COMPLETED */
void method_call_by_callout::evaluate()
{
	print_tabs(level);
	level++;
	cout << "method_call_by_callout " << name << endl;
	for(list<callout_arg_node*>::iterator it = callout_args->begin(); it!=callout_args->end(); ++it)
		(*it)->evaluate();
	level--;
}

/*************************************************************************/

block_node::block_node(list<var_decl_node*> *var_list, list<statement_node*> *statement_list)
{
	this->var_list = var_list;
	this->statement_list = statement_list;
}

/* COMPLETED */
void block_node::evaluate()
{
	print_tabs(level);
	level++;
	cout << "block_node " << endl;

	for(list<var_decl_node*>::iterator it = var_list->begin(); it!=var_list->end(); ++it)
		(*it)->evaluate();

	for(list<statement_node*>::iterator it = statement_list->begin(); it!=statement_list->end(); ++it)
		(*it)->evaluate();

	level--;
}

argument_node::argument_node(string type, string id)
{
	this->type = type;
	this->id = id;
}

/* COMPLETED */
void argument_node::evaluate()
{
	print_tabs(level-1);
	level++;
	cout << " TYPE " << type << " ID " << id ;
	level--;
}

field_decl_id_simple::field_decl_id_simple(string id)
{
	this->id = id;
}

/* COMPLETED */
void field_decl_id_simple::evaluate()
{
	print_tabs(level);
	level++;
	cout << "field_decl_id_simple " << id << endl;
	level--;
}

field_decl_id_array::field_decl_id_array(string id, int int_literal)
{
	this->id = id;
	this->int_literal = int_literal;
}

/* COMPLETED */
void field_decl_id_array::evaluate()
{
	print_tabs(level);
	level++;
	cout << "field_decl_id_array " << id << "[" << int_literal << "]" <<endl;
	level--;
}

field_decl_node::field_decl_node(string type, list<field_decl_id_node*> *field_decl_id_list)
{
	this->type = type;
	this->field_decl_id_list = field_decl_id_list;
}
/* COMPLETED */
void field_decl_node::evaluate()
{
	print_tabs(level);
	level++;
	cout << "field_decl_node TYPE " << type << endl;
	for(list<field_decl_id_node*>::iterator it = field_decl_id_list->begin(); it!=field_decl_id_list->end(); ++it)
		(*it)->evaluate();

	level--;
}

method_decl_node::method_decl_node(string type, string id, list<argument_node*> *arg_list, block_node* block)
{
	this->type = type;
	this->id = id;
	this->arg_list = arg_list;
	this->block = block;
}
/* COMPLETED */
void method_decl_node::evaluate()
{
	print_tabs(level);
	level++;
	cout << "method_decl_node TYPE " << type << " ID " << id << endl;

	print_tabs(level-1);
	cout << "Argument list ";
	for (list<argument_node*>::iterator it=arg_list->begin(); it!=arg_list->end(); ++it)
        (*it)->evaluate();
    cout << endl;
    
    block->evaluate();

	level--;
}

program::program(list<field_decl_node*> *field_decl_list, list<method_decl_node*> *method_decl_list){
	
	this->method_decl_list = method_decl_list;
	this->field_decl_list = field_decl_list;
}

/* COMPLETED */
void program::evaluate(){
	print_tabs(level);
	level++;
	printf("Program\n");

	for(list<field_decl_node*>::iterator it = field_decl_list->begin(); it!=field_decl_list->end(); ++it)
		(*it)->evaluate();

	for (list<method_decl_node*>::iterator it=method_decl_list->begin(); it!=method_decl_list->end(); ++it)
        (*it)->evaluate();

	level--;
}