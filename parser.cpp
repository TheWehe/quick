#include "parser.hpp"


ast::NodePtr Parser::parse(const std::string& code) {
	tok.tokenize(code);
	auto a = assign();
	accept(TT_NONE);
	return a;
}

void Parser::accept(TokenType t) {
	tok.nextToken();
}

ast::NodePtr Parser::assign() {
	auto a = logic();

	if (tok.getCurToken().type == TT_EQUAL) {
		accept(TT_EQUAL);
		auto b = logic();
		return ast::NodePtr(new ast::AssignNode(a, b));
	}

	return a;
}

ast::NodePtr Parser::logic() {
	auto r = comp();

	while (tok.getCurToken().type == TT_AND || tok.getCurToken().type == TT_OR) {
		if (tok.getCurToken().type == TT_AND) {
			accept(TT_AND);
			r = ast::NodePtr(new ast::AndNode(r, comp()));
		}
		else {
			accept(TT_OR);
			r = ast::NodePtr(new ast::OrNode(r, comp()));
		}
	}

	return r;
}

ast::NodePtr Parser::comp() {
	auto r = add();

	while (tok.getCurToken().type == TT_DOUBLEEQUAL ||
		tok.getCurToken().type == TT_EXCLEQUAL ||
		tok.getCurToken().type == TT_LESS ||
		tok.getCurToken().type == TT_GREATER) {

		if (tok.getCurToken().type == TT_DOUBLEEQUAL) {
			accept(TT_DOUBLEEQUAL);
			r = ast::NodePtr(new ast::EqualNode(r, add()));
		}
		else if (tok.getCurToken().type == TT_EXCLEQUAL) {
			accept(TT_EXCLEQUAL);
			r = ast::NodePtr(new ast::NotEqualNode(r, add()));
		}
		else if (tok.getCurToken().type == TT_LESS) {
			accept(TT_LESS);
			r = ast::NodePtr(new ast::LessNode(r, add()));
		}
		else {
			accept(TT_GREATER);
			r = ast::NodePtr(new ast::GreaterNode(r, add()));
		}
	}

	return r;
}

ast::NodePtr Parser::add() {
	auto r = mul();

	while (tok.getCurToken().type == TT_PLUS || tok.getCurToken().type == TT_MINUS) {
		if (tok.getCurToken().type == TT_PLUS) {
			accept(TT_PLUS);
			r = ast::NodePtr(new ast::AddNode(r, mul()));
		}
		else {
			accept(TT_MINUS);
			r = ast::NodePtr(new ast::SubNode(r, mul()));
		}
	}

	return r;
}

ast::NodePtr Parser::mul() {
	auto r = neg();

	while (tok.getCurToken().type == TT_STAR ||
		tok.getCurToken().type == TT_SLASH ||
		tok.getCurToken().type == TT_PERCENT) {

		if (tok.getCurToken().type == TT_STAR) {
			accept(TT_STAR);
			r = ast::NodePtr(new ast::MulNode(r, neg()));
		}
		else if (tok.getCurToken().type == TT_SLASH) {
			accept(TT_SLASH);
			r = ast::NodePtr(new ast::DivNode(r, neg()));
		}
		else {
			accept(TT_PERCENT);
			r = ast::NodePtr(new ast::ModNode(r, neg()));
		}
	}

	return r;
}

ast::NodePtr Parser::neg() {
	if (tok.getCurToken().type == TT_MINUS) {
		accept(TT_MINUS);
		return ast::NodePtr(new ast::NegNode(paren()));
	}
	else {
		return paren();
	}
}

ast::NodePtr Parser::paren() {
	ast::NodePtr r;
	
	if (tok.getCurToken().type == TT_LPAREN) {
		accept(TT_LPAREN);
		r = assign();
		accept(TT_RPAREN);
	}
	else {
		r = prim();
	}

	return r;
}

ast::NodePtr Parser::prim() {
	if (tok.getCurToken().type == TT_NAME) {
		auto t = tok.getCurToken();
		accept(TT_NAME);
		return ast::NodePtr(new ast::VariableNode(t.s));
	}
	if (tok.getCurToken().type == TT_NULL) {
		accept(TT_NULL);
		return ast::NodePtr(new ast::NullNode());
	}
	if (tok.getCurToken().type == TT_INT) {
		auto t = tok.getCurToken();
		accept(TT_INT);
		return ast::NodePtr(new ast::IntNode(t.i));
	}
	if (tok.getCurToken().type == TT_FLOAT) {
		auto t = tok.getCurToken();
		accept(TT_FLOAT);
		return ast::NodePtr(new ast::FloatNode(t.f));
	}
	if (tok.getCurToken().type == TT_INF) {
		accept(TT_INF);
		return ast::NodePtr(new ast::InfNode());
	}
	if (tok.getCurToken().type == TT_BOOL) {
		auto t = tok.getCurToken();
		accept(TT_BOOL);
		return ast::NodePtr(new ast::BoolNode(t.b));
	}
	if (tok.getCurToken().type == TT_STRING) {
		auto t = tok.getCurToken();
		accept(TT_STRING);
		return ast::NodePtr(new ast::StringNode(t.s));
	}

	return nullptr;
}
