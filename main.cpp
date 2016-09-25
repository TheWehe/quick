#include <iostream>
#include "variable_mgr.hpp"
#include "variable_handle.hpp"
#include "scope.hpp"
#include "tokenizer.hpp"
#include "ast.hpp"
#include "parser.hpp"


int main() {
	VariableMgr mgr;
	Scope scope(mgr, nullptr);
	Parser parser;

	auto term = parser.parse("x = 5 + 7");
	mgr.destroy(term->eval(mgr, scope));
	std::cout << scope.find("x")->asInt() << std::endl;

	auto term2 = parser.parse("x = x + 8");
	mgr.destroy(term2->eval(mgr, scope));
	std::cout << scope.find("x")->asInt() << std::endl;

	scope.destroy("x");

	while (true) {}
}
