#include "parser.hpp"


ast::NodePtr Parser::parse(const std::string& code) {
	tok.tokenize(code);
	auto a = assignment();
	accept(TT_NONE);
	return a;
}

void Parser::accept(TokenType t) {
	tok.nextToken();
}

ast::NodePtr Parser::assignment() {
	auto a = addition();

	if (tok.getCurToken().type == TT_EQUAL) {
		accept(TT_EQUAL);
		auto b = addition();
		return ast::NodePtr(new ast::AssignNode(a, b));
	}

	return a;
}

ast::NodePtr Parser::addition() {
	auto a = primitive();

	while (tok.getCurToken().type == TT_PLUS) {
		accept(TT_PLUS);
		a = ast::NodePtr(new ast::AddNode(a, primitive()));
	}

	return a;
}

ast::NodePtr Parser::primitive() {
	if (tok.getCurToken().type == TT_NAME) {
		auto t = tok.getCurToken();
		accept(TT_NAME);
		return ast::NodePtr(new ast::VariableNode(t.s));
	}
	if (tok.getCurToken().type == TT_INT) {
		auto t = tok.getCurToken();
		accept(TT_INT);
		return ast::NodePtr(new ast::IntNode(t.i));
	}

	return nullptr;
}
