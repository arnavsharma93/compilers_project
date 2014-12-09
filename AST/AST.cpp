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
#include <llvm/Support/raw_ostream.h>
#include "AST.h"

#define debug 0

using namespace std;
using namespace llvm;

static IRBuilder<> Builder(getGlobalContext());
static map<string, AllocaInst*> NamedValues;
extern Module *TheModule;

Value *ErrorV(const char *Str) { printf("Error : %s\n", Str );; exit(0); }
void *Error(const char *Str) { printf("Error : %s\n", Str );; exit(0); }

/// CreateEntryBlockAlloca - Create an alloca instruction in the entry block of
/// the function.  This is used for mutable variables etc.
AllocaInst *CreateEntryBlockAlloca(Function *TheFunction, string VarName, string type)
{
    IRBuilder<> TmpB(&TheFunction->getEntryBlock(), TheFunction->getEntryBlock().begin());
    Type *T;
    if(type == "int")
        T = Type::getInt32Ty(getGlobalContext());
    if(type == "boolean")
        T = Type::getInt1Ty(getGlobalContext());
    return TmpB.CreateAlloca(T, 0, VarName);
}

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
	// this->Codegen();
	level--;
}
Value *int_literal_node::Codegen()
{
	Value *temp = ConstantInt::get(getGlobalContext(), APInt(32, this->value));
	if(debug)
		temp->dump();
	return temp;
}
char_literal_node::char_literal_node(string value){
	this->value = value;
}
/* COMPLETED */
void char_literal_node::evaluate()
{
	print_tabs(level);
	level++;
	cout << "Char literal VALUE " << value[1] << endl;
	// this->Codegen();
	level--;
}
Value *char_literal_node::Codegen()
{
	Value *temp = ConstantInt::get(getGlobalContext(), APInt(8, this->value[1]));
	if(debug)
		temp->dump();
	return temp;
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
	// this->Codegen();
	level--;
}
Value *bool_literal_node::Codegen()
{
	Value *temp = ConstantInt::get(getGlobalContext(), APInt(1, this->value));
	if(debug)
		temp->dump();
	return temp;
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
Value* array_loc::Codegen()
{
	return NULL;
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
Value* memory_loc::Codegen()
{
	Value *V = NamedValues[id];
	if (V == 0)
		Error("Unknown variable name");

	// Load the value.
	Value *temp = Builder.CreateLoad(V, id);

	if(debug)
		temp->dump();
	return temp;
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
	// this->Codegen();
	level--;
}

Value* literal_expr_node::Codegen()
{
	Value *temp = literal->Codegen();
	if(debug)
		temp->dump();
	return temp;
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
	// this->Codegen();
}

Value* method_call_expr_node::Codegen()
{
	Value *temp = method_call->Codegen();
	if(debug)
		temp->dump();
	return temp;
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

	// this->Codegen();
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

	// this->Codegen();
}

Value* not_expr_node::Codegen()
{
	Value *E = expr->Codegen();

	int E_size = E->getType()->getIntegerBitWidth();

	if(E_size != 1)
	{
		Error("Logical not defined on int");
	}

	Value *temp = Builder.CreateNot(E, "nottmp");
	if(debug)
		temp->dump();
	return temp;
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

	// this->Codegen();
}

Value* negate_expr_node::Codegen()
{
	Value *E = expr->Codegen();
	Value *temp = Builder.CreateNeg(E, "negtmp");
	if(debug)
		temp->dump();
	return temp;
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

	// this->Codegen();
}

Value* location_expr_node::Codegen(){

	Value *temp = location->Codegen();
	return temp;
}

product_node::product_node(expr_node *left, expr_node *right): operator_node(left, right){
}
Value* product_node::Codegen(){
	Value *L = left->Codegen();
	Value *R = right->Codegen();

	int L_size = L->getType()->getIntegerBitWidth();
	int R_size = R->getType()->getIntegerBitWidth();

	if(L_size == 1 || R_size == 1)
	{
		Error("Multiplication not defined on boolean");
	}

	Value *temp = Builder.CreateMul(L, R, "multmp");
	if(debug)
		temp->dump();
	return temp;
}
division_node::division_node(expr_node *left, expr_node *right): operator_node(left, right){
}
Value* division_node::Codegen(){
	Value *L = left->Codegen();
	Value *R = right->Codegen();

	int L_size = L->getType()->getIntegerBitWidth();
	int R_size = R->getType()->getIntegerBitWidth();

	if(L_size == 1 || R_size == 1)
	{
		Error("Division not defined on boolean");
	}

	Value *temp = Builder.CreateSDiv(L, R, "divtmp");
	if(debug)
		temp->dump();
	return temp;
}
modulus_node::modulus_node(expr_node *left, expr_node *right): operator_node(left, right){
}
Value* modulus_node::Codegen(){
	Value *L = left->Codegen();
	Value *R = right->Codegen();

	int L_size = L->getType()->getIntegerBitWidth();
	int R_size = R->getType()->getIntegerBitWidth();

	if(L_size == 1 || R_size == 1)
	{
		Error("Modulo not defined on boolean");
	}

	Value *temp = Builder.CreateSRem(L, R, "modtmp");
	if(debug)
		temp->dump();
	return temp;
}
addition_node::addition_node(expr_node *left, expr_node *right): operator_node(left, right){
}
Value* addition_node::Codegen(){
	Value *L = left->Codegen();
	Value *R = right->Codegen();

	int L_size = L->getType()->getIntegerBitWidth();
	int R_size = R->getType()->getIntegerBitWidth();

	if(L_size == 1 || R_size == 1)
	{
		Error("Addition not defined on boolean");
	}

	Value *temp = Builder.CreateAdd(L, R, "addtmp");
	if(debug)
		temp->dump();
	return temp;
}
subtraction_node::subtraction_node(expr_node *left, expr_node *right): operator_node(left, right){
}
Value* subtraction_node::Codegen(){
	Value *L = left->Codegen();
	Value *R = right->Codegen();

	int L_size = L->getType()->getIntegerBitWidth();
	int R_size = R->getType()->getIntegerBitWidth();

	if(L_size == 1 || R_size == 1)
	{
		Error("Subtraction not defined on boolean");
	}

	Value *temp = Builder.CreateSub(L, R, "subtmp");
	if(debug)
		temp->dump();
	return temp;
}
less_node::less_node(expr_node *left, expr_node *right): operator_node(left, right){
}
Value* less_node::Codegen(){
	Value *L = left->Codegen();
	Value *R = right->Codegen();

	int L_size = L->getType()->getIntegerBitWidth();
	int R_size = R->getType()->getIntegerBitWidth();

	if(L_size == 1 || R_size == 1)
	{
		Error("Less than not defined on boolean");
	}

	Value *temp = Builder.CreateICmp(CmpInst::ICMP_SLT, L, R, "lesstmp");
	if(debug)
		temp->dump();
	return temp;
}
less_eq_node::less_eq_node(expr_node *left, expr_node *right): operator_node(left, right){
}
Value* less_eq_node::Codegen(){
	Value *L = left->Codegen();
	Value *R = right->Codegen();

	int L_size = L->getType()->getIntegerBitWidth();
	int R_size = R->getType()->getIntegerBitWidth();

	if(L_size == 1 || R_size == 1)
	{
		Error("Less than equal to not defined on boolean");
	}

	Value *temp = Builder.CreateICmp(CmpInst::ICMP_SLE, L, R, "lesseqtmp");
	if(debug)
		temp->dump();
	return temp;
}
greater_node::greater_node(expr_node *left, expr_node *right): operator_node(left, right){
}
Value* greater_node::Codegen(){
	Value *L = left->Codegen();
	Value *R = right->Codegen();

	int L_size = L->getType()->getIntegerBitWidth();
	int R_size = R->getType()->getIntegerBitWidth();

	if(L_size == 1 || R_size == 1)
	{
		Error("Greater than not defined on boolean");
	}

	Value *temp = Builder.CreateICmp(CmpInst::ICMP_SGT, L, R, "gttmp");
	if(debug)
		temp->dump();
	return temp;
}
greater_eq_node::greater_eq_node(expr_node *left, expr_node *right): operator_node(left, right){
}
Value* greater_eq_node::Codegen(){
	Value *L = left->Codegen();
	Value *R = right->Codegen();

	int L_size = L->getType()->getIntegerBitWidth();
	int R_size = R->getType()->getIntegerBitWidth();

	if(L_size == 1 || R_size == 1)
	{
		Error("Greater than equal to not defined on boolean");
	}

	Value *temp = Builder.CreateICmp(CmpInst::ICMP_SGE, L, R, "gteqtmp");
	if(debug)
		temp->dump();
	return temp;
}
equal_equal_node::equal_equal_node(expr_node *left, expr_node *right): operator_node(left, right){
}
Value* equal_equal_node::Codegen(){
	Value *L = left->Codegen();
	Value *R = right->Codegen();

	int L_size = L->getType()->getIntegerBitWidth();
	int R_size = R->getType()->getIntegerBitWidth();


	if(L_size != R_size)
	{
		Error("Datatypes not similar in equal to operator");
	}

	Value *temp = Builder.CreateICmp(CmpInst::ICMP_EQ, L, R, "eqtmp");
	if(debug)
		temp->dump();
	return temp;
}
not_equal_node::not_equal_node(expr_node *left, expr_node *right): operator_node(left, right){
}
Value* not_equal_node::Codegen(){
	Value *L = left->Codegen();
	Value *R = right->Codegen();

	int L_size = L->getType()->getIntegerBitWidth();
	int R_size = R->getType()->getIntegerBitWidth();


	if(L_size != R_size)
	{
		Error("Datatypes not similar in not-equal to operator");
	}

	Value *temp = Builder.CreateICmp(CmpInst::ICMP_NE, L, R, "neqtmp");
	if(debug)
		temp->dump();
	return temp;
}
cond_and_node::cond_and_node(expr_node *left, expr_node *right): operator_node(left, right){
}
Value* cond_and_node::Codegen(){
	Value *L = left->Codegen();
	Value *R = right->Codegen();

	int L_size = L->getType()->getIntegerBitWidth();
	int R_size = R->getType()->getIntegerBitWidth();

	if(L_size == 32 || R_size == 32)
	{
		Error("Conditional operators not defined on int");
	}

	Value *temp = Builder.CreateAnd(L, R, "andtmp");
	if(debug)
		temp->dump();
	return temp;

}
cond_or_node::cond_or_node(expr_node *left, expr_node *right): operator_node(left, right){
}
Value* cond_or_node::Codegen(){
	Value *L = left->Codegen();
	Value *R = right->Codegen();

	int L_size = L->getType()->getIntegerBitWidth();
	int R_size = R->getType()->getIntegerBitWidth();

	if(L_size == 32 || R_size == 32)
	{
		Error("Conditional operators not defined on int");
	}
	Value *temp = Builder.CreateOr(L, R, "ortmp");

	if(debug)
		temp->dump();
	return temp;

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
Value* method_call_stmt::Codegen()
{
    Value *temp = method_call->Codegen();
    if(debug)
        temp->dump();
    return temp;
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
	this->expr->evaluate();
}
Value* assignment_stmt::Codegen()
{
    Value *E = expr->Codegen();

    string id = this->location->id;

	Value *V_name = NamedValues[id];
	if (V_name == 0)
		Error("Unknown variable name");

	Value *V_value = Builder.CreateLoad(V_name, id);

	int V_size = V_value->getType()->getIntegerBitWidth();
	int E_size = E->getType()->getIntegerBitWidth();

	if(V_size != E_size)
	{
		Error("Datatypes of LHS and RHS not same");
	}


	if(this->assign_op->op == 0)
	{
		Builder.CreateStore(E, V_name);
		if(debug)
		{
			V_name->dump();
		}

		return E;
	}
	else if(this->assign_op->op == 1)
	{
		Value *V_new_value = Builder.CreateAdd(V_value, E, "addtmp");
		Builder.CreateStore(V_new_value, V_name);
		if(debug)
		{
			// int type_int=0;
			// llvm::raw_string_ostream rso(&type_int);
			// cout << "printing assignment op value" << endl;
			// V_new_value->print(rso);

			V_new_value->dump();
		}
		return V_new_value;
	}
	else
	{
		Value *V_new_value = Builder.CreateSub(V_value, E, "subtmp");
		Builder.CreateStore(V_new_value, V_name);
		if(debug)
			V_new_value->dump();
		return V_new_value;
	}
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
Value* if_stmt::Codegen()
{
    Value* CondV = this->expr->Codegen();
    if(CondV == 0)
         return 0;

    CondV = Builder.CreateICmpEQ(CondV, ConstantInt::get(getGlobalContext(), APInt(1, 1, false)), "ifcond");

    if(debug)
    {
        cout << "dumping condv" << endl;
        CondV->dump();
    }

}

if_else_stmt::if_else_stmt(expr_node *expr, block_node *then_block, block_node *else_block)
{
	this->expr = expr;
	this->then_block = then_block;
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
	then_block->evaluate();
	print_tabs(level-1);
	cout << "ELSE Block" << endl;
	else_block->evaluate();

	level--;
}
Value* if_else_stmt::Codegen()
{
	 Value* CondV = this->expr->Codegen();
	if(CondV == 0)
	     return 0;

	CondV = Builder.CreateICmpEQ(CondV, ConstantInt::get(getGlobalContext(), APInt(1, 1, false)), "ifcond");

	// get the parent function of the current basic block: the function in which the current BB is embedded
	Function *TheFunction = Builder.GetInsertBlock()->getParent();

	// create BB for the Then block and insert it at the end of the current function
	BasicBlock *ThenBB = BasicBlock::Create(getGlobalContext(), "then", TheFunction);

	// BB for Else block
	BasicBlock *ElseBB = BasicBlock::Create(getGlobalContext(), "else");
	// BB for merge
	BasicBlock *MergeBB = BasicBlock::Create(getGlobalContext(), "ifcont");

	// Choose the BB based upon the value of CondV
	Builder.CreateCondBr(CondV, ThenBB, ElseBB);


	// Codegen of then block
	// Emit Then Value - Starts inserting at the beginning of Then block
	Builder.SetInsertPoint(ThenBB);

	// block codegen not working
	Value *ThenV = then_block->Codegen();
	if (ThenV == 0) return 0;
	// Unconditional merge back
	Builder.CreateBr(MergeBB);
	// Codegen of 'Then' can change the current block, update ThenBB for the PHI.
	ThenBB = Builder.GetInsertBlock();


	// Codegen of else block
	TheFunction->getBasicBlockList().push_back(ElseBB);
	Builder.SetInsertPoint(ElseBB);

	// block codegen not working
	Value *ElseV = else_block->Codegen();
	if (ElseV == 0) return 0;
	Builder.CreateBr(MergeBB);
	// Codegen of 'Else' can change the current block, update ElseBB for the PHI.
	ElseBB = Builder.GetInsertBlock();

	// Emit merge block
	TheFunction->getBasicBlockList().push_back(MergeBB);
	Builder.SetInsertPoint(MergeBB);
	PHINode *PN = Builder.CreatePHI(Type::getVoidTy(getGlobalContext()), 2,
                                  "iftmp");

	// int pn_size = PN->getType()->getIntegerBitWidth();

	// printf("%d\n", pn_size);

	PN->addIncoming(ThenV, ThenBB);
	PN->addIncoming(ElseV, ElseBB);
	return PN;
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
Value* for_stmt::Codegen()
{
    return NULL;
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
Value* return_stmt::Codegen()
{
    return NULL;
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
Value* return_expr_stmt::Codegen()
{
    return NULL;
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
Value* break_stmt::Codegen()
{
    return NULL;
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
Value* continue_stmt::Codegen()
{
    return NULL;
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

	// block->Codegen();
}
Value* block_stmt::Codegen()
{
    Value *temp;
    temp = block->Codegen();
    if(debug)
    {
        printf("IN BLOCK STMT\n");
        // temp->dump();
    }
    return temp;
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
Value* callout_arg_expr::Codegen()
{
	Value *temp = expr->Codegen();

	return temp;
}
callout_arg_string::callout_arg_string(string arg)
{
	int len = arg.length();
	this->arg = arg.substr(1, len-2);
}

/* COMPLETED */
void callout_arg_string::evaluate()
{
	print_tabs(level);
	level++;
	cout << "callout_arg using string " << arg << endl;
	level--;
}

Value* callout_arg_string::Codegen()
{
	Value *temp = Builder.CreateGlobalStringPtr(arg);
	return temp;
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

    // this->Codegen();
}
Value* method_call_by_id::Codegen()
{
    Function *CalleeF = TheModule->getFunction(id);
    if (CalleeF == 0)
        Error("Unknown function referenced");

    // If argument mismatch error.
    if (CalleeF->arg_size() != param_list->size())
        Error("Incorrect # arguments passed");

    std::vector<Value*> ArgsV;
    Value *temp;
    for (list<expr_node*>::iterator it=param_list->begin(); it!=param_list->end(); ++it)
    {
        temp = (*it)->Codegen();
        ArgsV.push_back(temp);
        if (temp == 0)
            return 0;
    }
    temp = Builder.CreateCall(CalleeF, ArgsV, "calltmp");
    if(debug)
        temp->dump();
    return temp;
}
method_call_by_callout::method_call_by_callout(string name, list<callout_arg_node*> *callout_args)
{
    int len = name.length();
	this->name = name.substr(1, len-2);
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
Value* method_call_by_callout::Codegen()
{
	cout << "In callout" << endl;
	cout << name << endl;

	// Check if this function is in the module.
	// If not, put it in the module with no body.
	Function *CalleeF = TheModule->getFunction(name);
    if (CalleeF == 0)
    {
	    Type *ret_type;
		vector<Type*> args;
		ret_type = Type::getInt32Ty(getGlobalContext());

		// Create the function definition.
		FunctionType *FT = FunctionType::get(ret_type, args, true);
		Function *F = Function::Create(FT, GlobalValue::ExternalLinkage, name, TheModule);
		if(debug)
			F->dump();
	}

	// Get the function
	CalleeF = TheModule->getFunction(name);

	// Construct the arguments
    std::vector<Value*> ArgsV;
    Value *temp;
    for (list<callout_arg_node*>::iterator it=callout_args->begin(); it!=callout_args->end(); ++it)
    {
        temp = (*it)->Codegen();
        ArgsV.push_back(temp);
        if (temp == 0)
            return 0;
    }
    // Make the call instruction
    temp = Builder.CreateCall(CalleeF, ArgsV, "calltmp");
    if(debug)
        temp->dump();
    return temp;
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
Value* block_node::Codegen()
{
    vector<AllocaInst *> OldBindings;
    Function *TheFunction = Builder.GetInsertBlock()->getParent();
    map<string, bool> CurrentVars;

    // Check for multiple declarations of variable.
    for(list<var_decl_node*>::iterator it = var_list->begin(); it!=var_list->end(); ++it)
    {
        list<string> *ids = (*it)->id_list;

        for(list<string>::iterator it2 = ids->begin(); it2!=ids->end(); ++it2)
        {
            if(CurrentVars.find((*it2))!= CurrentVars.end())
                // Variable declared more than once.
                Error("Redeclaration of variable in block");
            else
                CurrentVars[*it2] = true;
        }
    }

	// Put variable declarations in scope.
	for(list<var_decl_node*>::iterator it = var_list->begin(); it!=var_list->end(); ++it)
	{
		list<string> *ids = (*it)->id_list;

		for(list<string>::iterator it2 = ids->begin(); it2!=ids->end(); ++it2)
		{
            AllocaInst *Alloca = CreateEntryBlockAlloca(TheFunction, (*it2), (*it)->type);
            Value *InitVal;

            if(((*it)->type == "int"))
                InitVal = ConstantInt::get(getGlobalContext(), APInt(32, 0));
            else if(((*it)->type == "boolean"))
                InitVal = ConstantInt::get(getGlobalContext(), APInt(1, false));
            Builder.CreateStore(InitVal, Alloca);

            OldBindings.push_back(NamedValues[(*it2)]);

            // Remember this binding.
            NamedValues[(*it2)] = Alloca;
		}
	}
    cout << "Before Local Var ";
    for(map<string, AllocaInst*>::iterator it=NamedValues.begin(); it!=NamedValues.end(); ++it)
    {
     cout << (*it).first << " ";
    }
    cout << endl;

    // Execute the statements.
    for(list<statement_node*>::iterator it = statement_list->begin(); it!=statement_list->end(); ++it)
        (*it)->Codegen();

    // Pop all our variables from scope.
    int i=0;
    for(list<var_decl_node*>::iterator it = var_list->begin(); it!=var_list->end(); ++it)
    {
        list<string> *ids = (*it)->id_list;

        for(list<string>::iterator it2 = ids->begin(); it2!=ids->end(); ++it2)
        {
            if(OldBindings[i] == NULL)
                NamedValues.erase(*it2);
            else
                NamedValues[(*it2)] = OldBindings[i];
            i++;
        }
    }


	// cout << "After Local Var ";
	// for(map<string, AllocaInst*>::iterator it=NamedValues.begin(); it!=NamedValues.end(); ++it)
	// {
	// 	cout << (*it).first << " ";
	// }
	// cout << endl;

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
Type* argument_node::Codegen()
{
	if(type == "int")
		return Type::getInt32Ty(getGlobalContext());
	else if(type == "boolean")
		return Type::getInt1Ty(getGlobalContext());
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
	// this->Codegen();
}

Function* method_decl_node::Codegen()
{
	vector<AllocaInst *> OldBindings;
	// main function should be called with no arguments.
	if(id == "main")
	{
		// argument list must be empty
		if(arg_list->size()!=0)
		{
			Error("main function should have no arguments");
			return 0;
		}
	}
	Type *ret_type;
	vector<Type*> args;

	// Set the return type
	if(type == "int")
		ret_type = Type::getInt32Ty(getGlobalContext());
	else if(type == "boolean")
		ret_type = Type::getInt1Ty(getGlobalContext());
	else if(type == "void")
		ret_type = Type::getVoidTy(getGlobalContext());

	// Construct the arguments.
	for (list<argument_node*>::iterator it=arg_list->begin(); it!=arg_list->end(); ++it)
		args.push_back((*it)->Codegen());

	// Create the function definition.
	FunctionType *FT = FunctionType::get(ret_type, args, false);
	Function *F = Function::Create(FT, Function::ExternalLinkage, id, TheModule);

	// If function already defined.
	if (F->getName() != id){
		Error("redefinition of function");
		return 0;
	}

    // Create a new basic block to start insertion into.
    BasicBlock *BB = BasicBlock::Create(getGlobalContext(), "entry", F);
    Builder.SetInsertPoint(BB);

    list<argument_node*>::iterator it;
    map<string, bool> CurrentVars;
    // Check for multiple declarations of variable.
    for(it=arg_list->begin(); it!=arg_list->end(); ++it)
    {
        if(CurrentVars.find((*it)->id)!= CurrentVars.end())
            // Variable declared more than once.
            Error("Redeclaration of variable in function declaration");
        else
            CurrentVars[(*it)->id] = true;

    }

	// Add all arguments to the symbol table and create their allocas.
	it=arg_list->begin();
	for (Function::arg_iterator AI = F->arg_begin(); it != arg_list->end(); ++AI, ++it)
	{
		AI->setName((*it)->id);
        // Create an alloca for this variable.
        AllocaInst *Alloca = CreateEntryBlockAlloca(F, (*it)->id, (*it)->type);

        // Store the initial value into the alloca.
        Builder.CreateStore(AI, Alloca);

        // Remember the old variable binding so that we can restore the binding when we unrecurse.
        OldBindings.push_back(NamedValues[(*it)->id]);

        // Add arguments to variable symbol table.
        NamedValues[(*it)->id] = Alloca;
	}


	// TODO : See what to do with RetVal
	Value* RetVal = block->Codegen();

    int idx=0;
    for (it=arg_list->begin(); it != arg_list->end(); ++it, idx++)
    {
        // Restore old
        if(OldBindings[idx] == NULL)
            NamedValues.erase((*it)->id);
        else
            NamedValues[(*it)->id] = OldBindings[idx];
    }

	if(debug)
		F->dump();

	return F;
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
void program::Codegen()
{
    for (list<method_decl_node*>::iterator it=method_decl_list->begin(); it!=method_decl_list->end(); ++it)
        (*it)->Codegen();


}