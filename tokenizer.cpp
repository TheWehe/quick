#include "tokenizer.hpp"

#include <cctype>
#include <cassert> // temp


Tokenizer::~Tokenizer() {
	clear();
}

void Tokenizer::tokenize(const std::string& code) {
	clear();

	assert(code.size() != 0);

	unsigned curPos = 0;
	char curChar = code[curPos];

	auto posValid = [&]() {
		if (curPos < code.size()) return true;
		else return false;
	};
	auto nextChar = [&]() {
		curPos++;
		if (posValid()) curChar = code[curPos];
	};

	while (posValid()) {
		while (isspace(curChar) && curChar != '\n' && curChar != '\t' && posValid()) {
			nextChar();
		}

		switch (curChar) {
		case '(':
			nextChar();
			tokens.push_back(Token(TT_LPAREN));
			continue;

		case ')':
			nextChar();
			tokens.push_back(Token(TT_RPAREN));
			continue;

		case '=':
			nextChar();
			if (curChar == '=') {
				tokens.push_back(Token(TT_DOUBLEEQUAL));
				nextChar();
			}
			else {
				tokens.push_back(Token(TT_EQUAL));
			}
			continue;

		case '+':
			tokens.push_back(Token(TT_PLUS));
			nextChar();
			continue;

		case '-':
			tokens.push_back(Token(TT_MINUS));
			nextChar();
			continue;

		case '*':
			tokens.push_back(Token(TT_STAR));
			nextChar();
			continue;

		case '/':
			tokens.push_back(Token(TT_SLASH));
			nextChar();
			continue;

		case '%':
			tokens.push_back(Token(TT_PERCENT));
			nextChar();
			continue;

		case '!':
			nextChar();
			if (curChar == '=') {
				tokens.push_back(Token(TT_EXCLEQUAL));
				nextChar();
			}
			else {
				assert(false);
			}
			continue;

		case '<':
			nextChar();
			tokens.push_back(Token(TT_LESS));
			continue;

		case '>':
			nextChar();
			tokens.push_back(Token(TT_GREATER));
			continue;

		case ',':
			nextChar();
			tokens.push_back(Token(TT_COMMA));
			continue;

		case '\t':
			if (!tokens.empty() && tokens[tokens.size() - 1].type == TT_TAB) {
				tokens[tokens.size() - 1].i++;
			}
			else {
				tokens.push_back(Token(TT_TAB));
				tokens[tokens.size() - 1].i = 1;
			}
			nextChar();
			continue;

		case '\n':
			if (!tokens.empty()) {
				if (tokens[tokens.size() - 1].type == TT_TAB) {
					tokens.erase(tokens.begin() + tokens.size() - 1);
				}
				else if (tokens[tokens.size() - 1].type != TT_NEWLINE) {
					tokens.push_back(Token(TT_NEWLINE));
				}
			}
			nextChar();
			continue;
		}

		if (posValid() && curChar == '\"') {
			nextChar();
			std::string buffer;

			while (posValid() && curChar != '\"' && curChar != '\n') {
				buffer += curChar;
				nextChar();
			}

			if (posValid() && curChar == '\"') {
				nextChar();
				char* s = new char[buffer.size() + 1];
				for (unsigned i = 0; i < buffer.size(); i++) {
					s[i] = buffer[i];
				}
				s[buffer.size()] = '\0';
				tokens.push_back(Token(TT_STRING, s));
				continue;
			}
			else {
				assert(false);
			}
		}

		if (posValid() && (isalpha(curChar) || curChar == '_')) {
			std::string buffer;
			while (posValid() && (isalnum(curChar) || curChar == '_')) {
				buffer += curChar;
				nextChar();
			}

			if (buffer == "null") {
				tokens.push_back(Token(TT_NULL));
			}
			else if (buffer == "inf") {
				tokens.push_back(Token(TT_INF));
			}
			else if (buffer == "true") {
				tokens.push_back(Token(true));
			}
			else if (buffer == "false") {
				tokens.push_back(Token(false));
			}
			else if (buffer == "and") {
				tokens.push_back(Token(TT_AND));
			}
			else if (buffer == "or") {
				tokens.push_back(Token(TT_OR));
			}
			else if (buffer == "if") {
				tokens.push_back(Token(TT_IF));
			}
			else if (buffer == "else") {
				tokens.push_back(Token(TT_ELSE));
			}
			else if (buffer == "elif") {
				tokens.push_back(Token(TT_ELIF));
			}
			else if (buffer == "while") {
				tokens.push_back(Token(TT_WHILE));
			}
			else if (buffer == "function") {
				tokens.push_back(Token(TT_FUNC));
			}
			else if (buffer == "return") {
				tokens.push_back(Token(TT_RETURN));
			}
			else {
				char* s = new char[buffer.size() + 1];
				for (unsigned i = 0; i < buffer.size(); i++) {
					s[i] = buffer[i];
				}
				s[buffer.size()] = '\0';

				tokens.push_back(Token(TT_NAME, s));
			}
			continue;
		}

		if (posValid() && isdigit(curChar)) {
			std::string buffer;

			while (posValid() && isdigit(curChar)) {
				buffer += curChar;
				nextChar();
			}

			if (posValid() && curChar == '.') {
				buffer += curChar;
				nextChar();

				if (posValid() && isdigit(curChar)) {
					while (posValid() && isdigit(curChar)) {
						buffer += curChar;
						nextChar();
					}

					tokens.push_back(Token(static_cast<float>(atof(buffer.c_str()))));
					continue;
				}
				else {
					assert(false);
				}
			}

			tokens.push_back(Token(atoi(buffer.c_str())));
			continue;
		}

		assert(false);
	}

	if (!tokens.empty())
	{
		if (tokens[tokens.size() - 1].type != TT_NEWLINE)
		{
			tokens.push_back(Token(TT_NEWLINE));
		}
	}
}

void Tokenizer::nextToken() {
	cur++;
}

const Token& Tokenizer::peekToken() const {
	if (cur + 1 >= tokens.size() || cur + 1 < 0) return nullToken;
	else return tokens[cur + 1];
}

const Token& Tokenizer::getCurToken() const {
	if (cur >= tokens.size() || cur < 0) return nullToken;
	else return tokens[cur];
}

void Tokenizer::clear() {
	for (auto& x : tokens) {
		if (x.type == TT_NAME || x.type == TT_STRING) {
			delete[] x.s;
		}
	}
	
	tokens.clear();
	cur = 0;
}
