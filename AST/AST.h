#include "llvm/IR/Verifier.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <list>

using namespace std;
using namespace llvm;

class assign_op_node{
	protected:
		int op;
	public:
		assign_op_node(int op);
		void evaluate();
		// virtual Value *Codegen() = 0;
};

class expr_node{
	public:
		virtual void evaluate() = 0;
		virtual Value* Codegen() = 0;
};

class method_call_node{
	public:
		virtual void evaluate() = 0;
		virtual Value* Codegen() = 0;
};

/*********************** Var Decl Nodes ************************/
class var_decl_node{
	public:
		string type;
		list<string> *id_list;
	public:
		var_decl_node(string type, list<string> *id_list);
		void evaluate();
		Type *Codegen();
};
/***************************************************************/

/*********************** Literal Nodes *************************/
/* COMPLETED */
class literal_node{
	public:
		virtual void evaluate() = 0;
		virtual Value *Codegen() = 0;
};
class int_literal_node : public literal_node{
	protected:
		int value;
	public:
		int_literal_node(int value);
		void evaluate();
		virtual Value *Codegen();
};
class char_literal_node : public literal_node{
	protected:
		string value;
	public:
		char_literal_node(string value);
		void evaluate();
		virtual Value *Codegen();
};
class bool_literal_node : public literal_node{
	protected:
		bool value;
	public:
		bool_literal_node(bool value);
		void evaluate();
		virtual Value *Codegen();
};
/***************************************************************/


/*********************** Location Nodes ************************/
class location_node{
	public:
		string id;
		virtual void evaluate() = 0;
		virtual Value *Codegen() = 0;
};

class memory_loc : public location_node{
	public:
		memory_loc(string id);
		void evaluate();
		virtual Value *Codegen();
};

class array_loc : public location_node{
	protected:
		expr_node *expr;
	public:
		array_loc(string id, expr_node *expr);
		void evaluate();
		virtual Value *Codegen();
};
/**************************************************************/

/*********************** Expression Nodes ***********************/

class method_call_expr_node : public expr_node{
	protected:
		method_call_node *method_call;
	public:
		method_call_expr_node(method_call_node *method_call);
		void evaluate();
		virtual Value *Codegen();
};

class literal_expr_node : public expr_node{
	protected:
		literal_node *literal;
	public:
		literal_expr_node(literal_node *literal);
		void evaluate();
		virtual Value *Codegen();
};

class operator_node : public expr_node{
	protected:
		expr_node *left, *right;
	public:
		operator_node(expr_node *left, expr_node *right);
		void evaluate();
		virtual Value *Codegen() = 0;
};

class not_expr_node : public expr_node{
	protected:
		expr_node *expr;
	public:
		not_expr_node(expr_node *expr);
		void evaluate();
		virtual Value *Codegen();
};

class negate_expr_node : public expr_node{
	protected:
		expr_node *expr;
	public:
		negate_expr_node(expr_node *expr);
		void evaluate();
		virtual Value *Codegen();
};

class location_expr_node : public expr_node{
	protected:
		location_node* location;
	public:
		location_expr_node(location_node* location);
		void evaluate();
		virtual Value *Codegen();
};

class product_node : public operator_node{
	public:
		product_node(expr_node *left, expr_node *right);
		virtual Value *Codegen();
};

class division_node : public operator_node{
	public:
		division_node(expr_node *left, expr_node *right);
		virtual Value *Codegen();
};

class modulus_node : public operator_node{
	public:
		modulus_node(expr_node *left, expr_node *right);
		virtual Value *Codegen();
};

class addition_node : public operator_node{
	public:
		addition_node(expr_node *left, expr_node *right);
		virtual Value *Codegen();
};

class subtraction_node : public operator_node{
	public:
		subtraction_node(expr_node *left, expr_node *right);
		virtual Value *Codegen();
};

class less_node : public operator_node{
	public:
		less_node(expr_node *left, expr_node *right);
		virtual Value *Codegen();
};

class less_eq_node : public operator_node{
	public:
		less_eq_node(expr_node *left, expr_node *right);
		virtual Value *Codegen();
};

class greater_node : public operator_node{
	public:
		greater_node(expr_node *left, expr_node *right);
		virtual Value *Codegen();
};

class greater_eq_node : public operator_node{
	public:
		greater_eq_node(expr_node *left, expr_node *right);
		virtual Value *Codegen();
};

class equal_equal_node : public operator_node{
	public:
		equal_equal_node(expr_node *left, expr_node *right);
		virtual Value *Codegen();
};

class not_equal_node : public operator_node{
	public:
		not_equal_node(expr_node *left, expr_node *right);
		virtual Value *Codegen();
};

class cond_and_node : public operator_node{
	public:
		cond_and_node(expr_node *left, expr_node *right);
		virtual Value *Codegen();
};

class cond_or_node : public operator_node{
	public:
		cond_or_node(expr_node *left, expr_node *right);
		virtual Value *Codegen();
};
/****************************************************************/


/*********************** Statement Nodes ************************/
class statement_node{
	public:
		virtual void evaluate() = 0;
		virtual Value* Codegen() = 0;
};

class block_node{
	protected:
		list<statement_node*> *statement_list;
		list<var_decl_node*> *var_list;
	public:
		map<string, Value*> LocalVars;
		block_node(list<var_decl_node*> *var_list, list<statement_node*> *statement_list);
		void evaluate();
		Value* Codegen();
};

class method_call_stmt : public statement_node{
	protected:
		method_call_node* method_call;
	public:
		method_call_stmt(method_call_node* method_call);
		void evaluate();
		virtual Value* Codegen();
};

class assignment_stmt : public statement_node{
	protected:
		location_node *location;
		assign_op_node *assign_op;
		expr_node *expr;
	public:
		assignment_stmt(location_node *location, assign_op_node * assign_op, expr_node *expr);
		void evaluate();
		virtual Value* Codegen();
};

class if_stmt : public statement_node{
	protected:
		block_node *block;
		expr_node *expr;
	public:
		if_stmt(expr_node *expr, block_node *block);
		void evaluate();
		virtual Value* Codegen();
};

class if_else_stmt : public statement_node{
	protected:
		block_node *if_block, *else_block;
		expr_node *expr;
	public:
		if_else_stmt(expr_node *expr, block_node *if_block, block_node *else_block);
		void evaluate();
		virtual Value* Codegen();
};

class for_stmt : public statement_node{
	protected:
		string id;
		expr_node *init_expr, *term_expr;
		block_node *block;
	public:
		for_stmt(string id, expr_node *init_expr, expr_node *term_expr, block_node *block);
		void evaluate();
		virtual Value* Codegen();

};

class return_stmt : public statement_node{
	public:
		return_stmt();
		void evaluate();
		virtual Value* Codegen();
};

class return_expr_stmt : public statement_node{
	protected:
		expr_node *expr;
	public:
		return_expr_stmt(expr_node *expr);
		void evaluate();
		virtual Value* Codegen();
};

class break_stmt : public statement_node{
	public:
		break_stmt();
		void evaluate();
		virtual Value* Codegen();
};

class continue_stmt : public statement_node{
	public:
		continue_stmt();
		void evaluate();
		virtual Value* Codegen();
};

class block_stmt : public statement_node{
	protected:
		block_node *block;
	public:
		block_stmt(block_node *block);
		void evaluate();
		virtual Value* Codegen();
};
/**************************************************************/

/*********************** Callout Arg Nodes *********************************/
class callout_arg_node{
	public:
		virtual void evaluate() = 0;
};

class callout_arg_expr : public callout_arg_node{
	protected:
		expr_node *expr;
	public:
		callout_arg_expr(expr_node *expr);
		void evaluate();
};

class callout_arg_string : public callout_arg_node{
	protected:
		string arg;
	public:
		callout_arg_string(string arg);
		void evaluate();
};

/********************** METHOD CALL Nodes *********************************/
class method_call_by_id : public method_call_node{
	protected:
		string id;
		list<expr_node*> *param_list;
	public:
		method_call_by_id(string id, list<expr_node*> *param_list);
		void evaluate();
		virtual Value* Codegen();

};

class method_call_by_callout : public method_call_node{
	protected:
		string name;
		list<callout_arg_node*> *callout_args;
	public:
		method_call_by_callout(string name, list<callout_arg_node*> *callout_args);
		void evaluate();
		virtual Value* Codegen();
};
/*************************************************************************/


class argument_node{
	// TODO : Make these protected and remove the debug loop from program constructor.
	public:
		string id, type;
	public:
		argument_node(string type, string id);
		void evaluate();
		Type* Codegen();
};

class field_decl_id_node{
	public:
		virtual void evaluate() = 0;
};

class field_decl_id_simple : public field_decl_id_node{
	protected:
		string id;
	public:
		field_decl_id_simple(string id);
		void evaluate();
};

class field_decl_id_array : public field_decl_id_node{
	protected:
		string id;
		int int_literal;
	public:
		field_decl_id_array(string id, int int_literal);
		void evaluate();
};

class field_decl_node{
	protected:
		string type;
		list<field_decl_id_node*> *field_decl_id_list;
	public:
		field_decl_node(string type, list<field_decl_id_node*> *field_decl_id_list);
		void evaluate();

};

class method_decl_node{
	protected:
		string id, type;
		list<argument_node*> *arg_list;
		block_node* block;
		// map<string, Value*> LocalVars;
	public:
		method_decl_node(string type, string id, list<argument_node*> *arg_list, block_node* block);
		void evaluate();
		Function *Codegen();

};

class program{
	protected:
		list<method_decl_node*> *method_decl_list;
		list<field_decl_node*> *field_decl_list;
	public:
		program(list<field_decl_node*> *field_decl_list, list<method_decl_node*> *method_decl_list);
		void evaluate();
		void Codegen();
};


extern program *root;