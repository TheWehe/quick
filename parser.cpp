#include "parser.hpp"

#include <cassert> // temp


ast::NodePtr Parser::parse(const std::string& code) {
	tok.tokenize(code);
	auto a = assignment();
	accept(TT_NONE);
	return a;
}

void Parser::accept(TokenType t) {
	assert(tok.getCurToken().type != TT_NONE);
	tok.nextToken(); 
}

ast::NodePtr Parser::assignment() {
	auto a = addition();
	
	if(tok.getCurToken().type == TT_EQUAL) {
		accept(TT_EQUAL);
		auto b = addition();
		return ast::NodePtr(new ast::AssignNode(a, b));
	}
	
	return a;
}

ast::NodePtr Parser::addition() {
	auto a = multiplication();
	
	while(tok.getCurToken().type == TT_PLUS || tok.getCurToken().type == TT_MINUS) {
		if(tok.getCurToken().type == TT_PLUS) {
			accept(TT_PLUS);
			a = ast::NodePtr(new ast::AddNode(a, multiplication()));
		}
		else {
			accept(TT_MINUS);
			a = ast::NodePtr(new ast::SubNode(a, multiplication()));
		}
	}
	
	return a;
}

ast::NodePtr Parser::multiplication() {
	auto a = primitive();
	
	while(tok.getCurToken().type == TT_STAR || tok.getCurToken().type == TT_SLASH) {
		if(tok.getCurToken().type == TT_STAR) {
			accept(TT_STAR);
			a = ast::NodePtr(new ast::MulNode(a, primitive()));
		}
		else {
			accept(TT_SLASH);
			a = ast::NodePtr(new ast::DivNode(a, primitive()));
		}
	}
	
	return a;
}

ast::NodePtr Parser::primitive() {
	if(tok.getCurToken().type == TT_NAME) {
		auto t = tok.getCurToken();
		accept(TT_NAME);
		return ast::NodePtr(new ast::VariableNode(t.s));
	}
	if(tok.getCurToken().type == TT_NULL) {
		auto t = tok.getCurToken();
		accept(TT_NULL);
		return ast::NodePtr(new ast::PrimitiveNode(t));
	}
	if(tok.getCurToken().type == TT_PINF) {
		auto t = tok.getCurToken();
		accept(TT_PINF);
		return ast::NodePtr(new ast::PrimitiveNode(t));
	}
	if(tok.getCurToken().type == TT_NINF) {
		auto t = tok.getCurToken();
		accept(TT_NINF);
		return ast::NodePtr(new ast::PrimitiveNode(t));
	}
	if(tok.getCurToken().type == TT_INT) {
		auto t = tok.getCurToken();
		accept(TT_INT);
		return ast::NodePtr(new ast::PrimitiveNode(t));
	}
	if(tok.getCurToken().type == TT_FLOAT) {
		auto t = tok.getCurToken();
		accept(TT_FLOAT);
		return ast::NodePtr(new ast::PrimitiveNode(t));
	}
	if(tok.getCurToken().type == TT_BOOL) {
		auto t = tok.getCurToken();
		accept(TT_BOOL);
		return ast::NodePtr(new ast::PrimitiveNode(t));
	}
	if(tok.getCurToken().type == TT_STRING) {
		auto t = tok.getCurToken();
		accept(TT_STRING);
		return ast::NodePtr(new ast::PrimitiveNode(t));
	}
	
	assert(false);
	return nullptr;
}
