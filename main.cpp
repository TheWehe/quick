#include <iostream>
#include "variable_mgr.hpp"
#include "variable_handle.hpp"
#include "scope.hpp"
#include "tokenizer.hpp"
#include "ast.hpp"


int main() {
	VariableMgr mgr;
	Scope scope(nullptr);
	
	scope.add("x", mgr.createInt(50));
	
	Token token;
	token.type = TT_FLOAT;
	token.f = -45.25f;
	
	auto program = ast::NodePtr(new ast::DivNode(
		ast::NodePtr(new ast::VariableNode("x")), 
		ast::NodePtr(new ast::PrimitiveNode(token))
	));
	
	std::cout << program->eval(mgr, scope).asFloat() << std::endl;
}
