#ifndef PARSER_HPP
#define PARSER_HPP

#include "ast.hpp"
#include "tokenizer.hpp"

class Parser {
public:
	ast::NodePtr parse(const std::string& code);

private:
	void accept(TokenType t);
	
	ast::NodePtr assign();
	ast::NodePtr logic();
	ast::NodePtr comp();
	ast::NodePtr add();
	ast::NodePtr mul();
	ast::NodePtr neg();
	ast::NodePtr paren();
	ast::NodePtr prim();
	
	Tokenizer tok;
};

#endif
