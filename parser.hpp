#ifndef PARSER_HPP
#define PARSER_HPP

#include "ast.hpp"
#include "tokenizer.hpp"
#include "function_mgr.hpp"

class Parser {
public:
	Parser(FunctionMgr& fmgr) : fmgr(fmgr) {}
	ast::NodePtr analyze(const std::string& code);

private:
	void accept(TokenType t);

	ast::NodePtr control(unsigned indentCount);

	ast::NodePtr assign();
	ast::NodePtr logic();
	ast::NodePtr comp();
	ast::NodePtr add();
	ast::NodePtr mul();
	ast::NodePtr neg();
	ast::NodePtr paren();
	ast::NodePtr prim();
	
	FunctionMgr& fmgr;
	Tokenizer tok;
};

#endif
