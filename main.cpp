#include <iostream>
#include "variable_mgr.hpp"
#include "variable_handle.hpp"
#include "scope.hpp"
#include "tokenizer.hpp"
#include "ast.hpp"
#include "parser.hpp"


int main() {
	VariableMgr mgr;
	Scope scope(nullptr);
	Parser parser;
	
	auto program = parser.parse("x = 5");
	auto result = program->eval(mgr, scope);
	
	std::cout << scope.find("x").getType() << std::endl;
}
