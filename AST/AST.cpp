#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <list>
#include "AST.h"

using namespace std;

assign_op_node::assign_op_node(int op)
{
	// This stores the char id or the macro id of the assign op.
	this->op = op;
}

/*********************** Var Decl Nodes ************************/
var_decl_node::var_decl_node(string type, list<string> *id_list){
	this->type = type;
	this->id_list = id_list;
}
/***************************************************************/

/*********************** Literal Nodes *************************/
int_literal_node::int_literal_node(int value){
	this->value = value;
}
char_literal_node::char_literal_node(string value){
	this->value = value;
}
bool_literal_node::bool_literal_node(bool value){
	this->value = value;
}
/**************************************************************/

/*********************** Location Nodes ************************/
array_loc::array_loc(string id, expr_node *expr)
{
	this->id = id;
	this->expr = expr;
}
memory_loc::memory_loc(string id)
{
	this->id = id;
}
/**************************************************************/

/*********************** Expression Nodes *********************/
literal_expr_node::literal_expr_node(literal_node *literal)
{
	this->literal = literal;
}

method_call_expr_node::method_call_expr_node(method_call_node *method_call)
{
	this->method_call = method_call;
	printf("\t\t\t\tMethod call expr_node\n");
}
operator_node::operator_node(expr_node *left, expr_node *right)
{
	//printf("\t\t\t\toperator_node\n");
	this->left = left;
	this->right = right;
}

not_expr_node::not_expr_node(expr_node *expr)
{
	this->expr = expr;
}

negate_expr_node::negate_expr_node(expr_node *expr)
{
	this->expr = expr;
}

location_expr_node::location_expr_node(location_node* location)
{
	this->location = location;
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
	cout << "\t\t\tMETHOD CALL STATEMENT " << endl;
}

assignment_stmt::assignment_stmt(location_node *location, assign_op_node * assign_op, expr_node *expr)
{
	this->location = location;
	this->assign_op = assign_op;
	this->expr = expr;
	cout << "\t\t\tAssignment Statement " << endl;
}

if_stmt::if_stmt(expr_node *expr, block_node *block)
{
	this->expr = expr;
	this->block = block;
	cout << "\t\t\tIF Statement " << endl;
}

if_else_stmt::if_else_stmt(expr_node *expr, block_node *if_block, block_node *else_block)
{
	this->expr = expr;
	this->if_block = if_block;
	this->else_block = else_block;
	cout << "\t\t\tIF else Statement " << endl;
}

for_stmt::for_stmt(string id, expr_node *init_expr, expr_node *term_expr, block_node *block){
	this->id = id;
	this->init_expr = init_expr;
	this->term_expr = term_expr;
	this->block = block;
	cout << "\t\t\tFOR Statement " << endl;

}

return_stmt::return_stmt()
{
	cout << "\t\t\tReturn Statement " << endl;
	// Do nothing
}

return_expr_stmt::return_expr_stmt(expr_node *expr){
	cout << "\t\t\tReturn EXPR Statement " << endl;
	this->expr = expr;
}

break_stmt::break_stmt()
{
	cout << "\t\t\tBreak Statement " << endl;
	// Do nothing
}
continue_stmt::continue_stmt()
{
	cout << "\t\t\tContinue Statement " << endl;
	// Do nothing
}

block_stmt::block_stmt(block_node *block)
{
	cout << "\t\t\tBlock Statement " << endl;
	this->block = block;
}
/**************************************************************/

callout_arg_expr::callout_arg_expr(expr_node *expr)
{
	this->expr = expr;
}
callout_arg_string::callout_arg_string(string arg)
{
	this->arg = arg;
	cout << "\t\t\t\tCallout arg string " << arg << endl;
}

/********************** METHOD CALL Nodes *********************************/
method_call_by_id::method_call_by_id(string id, list<expr_node*> *param_list){
	this->id = id;
	this->param_list = param_list;
	cout << "\t\t\tMethod call by id " << id << " with "<< param_list->size() << " parameters" << endl;
}

method_call_by_callout::method_call_by_callout(string name, list<callout_arg_node*> *callout_args)
{
	this->name = name;
	this->callout_args = callout_args;
	cout << "\t\t\tMethod call by callout " << name << endl;

}

/*************************************************************************/

block_node::block_node(list<var_decl_node*> *var_list, list<statement_node*> *statement_list)
{
	this->statement_list = statement_list;
}

argument_node::argument_node(string type, string id)
{
	this->type = type;
	this->id = id;
}

field_decl_id_simple::field_decl_id_simple(string id)
{
	this->id = id;
	cout <<  "\t\t\t\t\t Field Decl array " << id << endl;
}
field_decl_id_array::field_decl_id_array(string id, int int_literal)
{
	this->id = id;
	this->int_literal = int_literal;

	cout <<  "\t\t\t\t\t Field Decl array " << id << " " << int_literal << endl;
}

field_decl_node::field_decl_node(string type, list<field_decl_id_node*> *field_decl_id_list)
{
	this->type = type;
	this->field_decl_id_list = field_decl_id_list;
}

method_decl_node::method_decl_node(string type, string id, list<argument_node*> *arg_list, block_node* block)
{
	/************************************ For DEBUG ************************************/
	printf("Method decl constructor\n");
	cout << "\tTYPE, ID " << type << " " << id << endl;
	cout << "\targ_list contains " << endl;
    for (list<argument_node*>::iterator it=arg_list->begin(); it!=arg_list->end(); ++it)
        cout << "\t\t" << (*(*it)).type << " " << (*(*it)).id << endl;
    cout << endl;
    /**********************************************************************************/
	
	this->type = type;
	this->id = id;
	this->arg_list = arg_list;
	this->block = block;
}

program::program(list<field_decl_node*> *field_decl_list, list<method_decl_node*> *method_decl_list){
	
	/************************************ For DEBUG ************************************/
	printf("Program Constructor\n");
	cout << "method_decl contains " << endl;
    for (list<method_decl_node*>::iterator it=method_decl_list->begin(); it!=method_decl_list->end(); ++it)
        cout << '\t' << (*(*it)).id;
    cout << endl;
    /**********************************************************************************/

	this->method_decl_list = method_decl_list;
	this->field_decl_list = field_decl_list;
}

void program::evaluate(){
	printf("Evaluating the program\n");
}