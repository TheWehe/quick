#include <iostream>
#include <string>
#include "variable_mgr.hpp"
#include "variable_handle.hpp"
#include "scope.hpp"
#include "tokenizer.hpp"
#include "ast.hpp"
#include "parser.hpp"


std::string toString(bool b) {
	if (b) return "true";
	else return "false";
}

void printVariable(VariableHandle* h) {
	switch (h->getType()) {
	case DT_NULL: std::cout << "null"; break;
	case DT_INT: std::cout << "int (" << h->asInt() << ")"; break;
	case DT_FLOAT: std::cout << "float (" << h->asFloat() << ")"; break;
	case DT_PINF: std::cout << "inf"; break;
	case DT_NINF: std::cout << "-inf"; break;
	case DT_BOOL: std::cout << "bool (" << toString(h->asBool()) << ")"; break;
	case DT_STRING: std::cout << "string (" << h->asString() << ")"; break;
	}
}


int main() {
	VariableMgr mgr;
	Scope scope(mgr, nullptr);
	Parser parser;

	while (true) {
		std::string input;
		std::getline(std::cin, input);

		auto r = parser.parse(input)->eval(mgr, scope);

		printVariable(r);
		std::cout << std::endl << std::endl;
		
		mgr.destroy(r);
	}
}
