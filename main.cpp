#include <iostream>
#include <string>
#include <cassert>
#include <fstream>
#include "function_mgr.hpp"
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

VariableHandle* script_Sin(VariableMgr& mgr, const ParamList& params) {
	assert(params.size() == 1);
	assert(params[0]->getType() == DT_FLOAT || params[0]->getType() == DT_INT);

	if(params[0]->getType() == DT_FLOAT) return mgr.createFloat(std::sin(params[0]->asFloat()));
	else return mgr.createFloat(std::sin(params[0]->asInt()));
}

VariableHandle* script_Print(VariableMgr& mgr, const ParamList& params) {
	for (auto& p : params) {
		switch (p->getType()) {
		case DT_NULL: std::cout << "null"; break;
		case DT_INT: std::cout << p->asInt(); break;
		case DT_FLOAT: std::cout << p->asFloat(); break;
		case DT_PINF: std::cout << "inf"; break;
		case DT_NINF: std::cout << "-inf"; break;
		case DT_BOOL: std::cout << toString(p->asBool()); break;
		case DT_STRING: std::cout << p->asString(); break;
		}
	}

	return mgr.createNull();
}


int main() {
	VariableMgr mgr;
	FunctionMgr fmgr;
	Scope scope(mgr, nullptr);
	Parser parser(fmgr);

	scope.add("pi", mgr.createFloat(3.14159265359f));

	CFunction mySin;
	mySin.name = "sin";
	mySin.callback = &script_Sin;
	fmgr.addCFunc(mySin);

	CFunction myPrint;
	myPrint.name = "print";
	myPrint.callback = &script_Print;
	fmgr.addCFunc(myPrint);

	std::ifstream file("test.q");
	std::string code, temp;
	while (std::getline(file, temp)) code += temp + "\n";

	auto program = parser.analyze(code);
	program->eval(mgr, scope, fmgr);

	while (true);
}
