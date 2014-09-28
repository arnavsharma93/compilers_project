#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <list>

using namespace std;

class assign_op_node{
	protected:
		int op;
	public:
		assign_op_node(int op);
};

class expr_node{

};

class method_call_node{

};

/*********************** Var Decl Nodes ************************/
class var_decl_node{
	protected:
		string type;
		list<string> *id_list;
	public:
		var_decl_node(string type, list<string> *id_list);
};
/***************************************************************/

/*********************** Literal Nodes *************************/
class literal_node{

};
class int_literal_node : public literal_node{
	protected:
		int value;
	public:
		int_literal_node(int value);
};
class char_literal_node : public literal_node{
	protected:
		string value;
	public:
		char_literal_node(string value);
};
class bool_literal_node : public literal_node{
	protected:
		bool value;
	public:
		bool_literal_node(bool value);
};
/***************************************************************/


/*********************** Location Nodes ************************/
class location_node{
	// TODO : Make this protected after removing the debug
	public:
		string id;
};

class memory_loc : public location_node{
	public:
		memory_loc(string id);
};

class array_loc : public location_node{
	protected:
		expr_node *expr;
	public:
		array_loc(string id, expr_node *expr);
};
/**************************************************************/

/*********************** Expression Nodes ***********************/

class method_call_expr_node : public expr_node{
	protected:
		method_call_node *method_call;
	public:
		method_call_expr_node(method_call_node *method_call);
};

class literal_expr_node : public expr_node{
	protected:
		literal_node *literal;
	public:
		literal_expr_node(literal_node *literal);
};

class operator_node : public expr_node{
	protected:
		expr_node *left, *right;
	public:
		operator_node(expr_node *left, expr_node *right);
};

class not_expr_node : public expr_node{
	protected:
		expr_node *expr;
	public:
		not_expr_node(expr_node *expr);
};

class negate_expr_node : public expr_node{
	protected:
		expr_node *expr;
	public:
		negate_expr_node(expr_node *expr);
};

class location_expr_node : public expr_node{
	protected:
		location_node* location;
	public:
		location_expr_node(location_node* location);
};

class product_node : public operator_node{
	public:
		product_node(expr_node *left, expr_node *right);
};

class division_node : public operator_node{
	public:
		division_node(expr_node *left, expr_node *right);
};

class modulus_node : public operator_node{
	public:
		modulus_node(expr_node *left, expr_node *right);
};

class addition_node : public operator_node{
	public:
		addition_node(expr_node *left, expr_node *right);
};

class subtraction_node : public operator_node{
	public:
		subtraction_node(expr_node *left, expr_node *right);
};

class less_node : public operator_node{
	public:
		less_node(expr_node *left, expr_node *right);
};

class less_eq_node : public operator_node{
	public:
		less_eq_node(expr_node *left, expr_node *right);
};

class greater_node : public operator_node{
	public:
		greater_node(expr_node *left, expr_node *right);
};

class greater_eq_node : public operator_node{
	public:
		greater_eq_node(expr_node *left, expr_node *right);
};

class equal_equal_node : public operator_node{
	public:
		equal_equal_node(expr_node *left, expr_node *right);
};

class not_equal_node : public operator_node{
	public:
		not_equal_node(expr_node *left, expr_node *right);
};

class cond_and_node : public operator_node{
	public:
		cond_and_node(expr_node *left, expr_node *right);
};

class cond_or_node : public operator_node{
	public:
		cond_or_node(expr_node *left, expr_node *right);
};
/****************************************************************/


/*********************** Statement Nodes ************************/
class statement_node{
};

class block_node{
	protected:
		list<statement_node*> *statement_list;
		list<var_decl_node*> *var_list;
	public:
		block_node(list<var_decl_node*> *var_list, list<statement_node*> *statement_list);
};

class method_call_stmt : public statement_node{
	protected: 
		method_call_node* method_call;
	public:
		method_call_stmt(method_call_node* method_call);
};

class assignment_stmt : public statement_node{
	protected:
		location_node *location;
		assign_op_node *assign_op;
		expr_node *expr;
	public:
		assignment_stmt(location_node *location, assign_op_node * assign_op, expr_node *expr);
};

class if_stmt : public statement_node{
	protected:
		block_node *block;
		expr_node *expr;
	public:
		if_stmt(expr_node *expr, block_node *block);
};

class if_else_stmt : public statement_node{
	protected:
		block_node *if_block, *else_block;
		expr_node *expr;
	public:
		if_else_stmt(expr_node *expr, block_node *if_block, block_node *else_block);
};

class for_stmt : public statement_node{
	protected:
		string id;
		expr_node *init_expr, *term_expr;
		block_node *block;
	public:
		for_stmt(string id, expr_node *init_expr, expr_node *term_expr, block_node *block);

};

class return_stmt : public statement_node{
	public:
		return_stmt();
};

class return_expr_stmt : public statement_node{
	protected:
		expr_node *expr;
	public:
		return_expr_stmt(expr_node *expr);
};

class break_stmt : public statement_node{
	public:
		break_stmt();
};

class continue_stmt : public statement_node{
	public:
		continue_stmt();
};

class block_stmt : public statement_node{
	protected:
		block_node *block;
	public:
		block_stmt(block_node *block);
};
/**************************************************************/

/*********************** Callout Arg Nodes *********************************/
class callout_arg_node{

};

class callout_arg_expr : public callout_arg_node{
	protected:
		expr_node *expr;
	public:
		callout_arg_expr(expr_node *expr);
};

class callout_arg_string : public callout_arg_node{
	protected:
		string arg;
	public:
		callout_arg_string(string arg);
};

/********************** METHOD CALL Nodes *********************************/
class method_call_by_id : public method_call_node{
	protected:
		string id;
		list<expr_node*> *param_list;
	public:
		method_call_by_id(string id, list<expr_node*> *param_list);
};

class method_call_by_callout : public method_call_node{
	protected:
		string name;
		list<callout_arg_node*> *callout_args;
	public:
		method_call_by_callout(string name, list<callout_arg_node*> *callout_args);
};
/*************************************************************************/


class argument_node{
	// TODO : Make these protected and remove the debug loop from program constructor.
	public:
		string id, type;
	public:
		argument_node(string type, string id);
};

class field_decl_id_node{

};

class field_decl_id_simple : public field_decl_id_node{
	protected:
		string id;
	public:
		field_decl_id_simple(string id);
};

class field_decl_id_array : public field_decl_id_node{
	protected:
		string id;
		int int_literal;
	public:
		field_decl_id_array(string id, int int_literal);
};

class field_decl_node{
	protected:
		string type;
		list<field_decl_id_node*> *field_decl_id_list;
	public:
		field_decl_node(string type, list<field_decl_id_node*> *field_decl_id_list);

};

class method_decl_node{
	// TODO : Make these protected and remove the debug loop from program constructor.
	public:
		string id, type;
		list<argument_node*> *arg_list;
		block_node* block;
	public:
		method_decl_node(string type, string id, list<argument_node*> *arg_list, block_node* block);
		void evaluate();

};

class program{
	protected:
		list<method_decl_node*> *method_decl_list;
		list<field_decl_node*> *field_decl_list;
	public:
		program(list<field_decl_node*> *field_decl_list, list<method_decl_node*> *method_decl_list);
		void evaluate();
};


extern program *root;