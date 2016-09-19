#ifndef PARSER_HPP
#define PARSER_HPP

#include "ast.hpp"
#include "tokenizer.hpp"

class Parser {
public:
	ast::NodePtr parse(const std::string& code);

private:
	void accept(TokenType t);
	
	ast::NodePtr assignment();
	ast::NodePtr addition();
	ast::NodePtr multiplication();
	ast::NodePtr primitive();
	
	Tokenizer tok;
};

#endif
