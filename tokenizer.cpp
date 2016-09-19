#include "tokenizer.hpp"

#include <cctype>
#include <cassert> // temp
#include <iostream> // temp


Tokenizer::~Tokenizer() {
	clear();
}

void Tokenizer::tokenize(const std::string& code) {
	clear();
	
	assert(code.size() != 0);
	
	unsigned curPos = 0;
	char curChar = code[curPos];
	
	auto posValid = [&]() {
		if(curPos < code.size()) return true;
		else return false;
	};
	auto nextChar = [&]() {
		curPos++;
		if(posValid()) curChar = code[curPos];
	};
	
	while(posValid()) {
		while(isspace(curChar) && curChar != '\n' && curChar != '\t' && posValid()) {
			nextChar();
		}

		switch (curChar) {
		case '=':
			nextChar();
			tokens.push_back(Token(TT_EQUAL));
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
			
		case '\t':
			tokens.push_back(Token(TT_TAB));
			nextChar();
			continue;

		case '\n':
			if(!tokens.empty()) {
				if(tokens[tokens.size() - 1].type != TT_NEWLINE) {
					tokens.push_back(Token(TT_NEWLINE));
				}
			}
			nextChar();
			continue;
		}
		
		if(posValid() && curChar == '\"') {
			nextChar();
			std::string buffer;
			
			while(posValid() && curChar != '\"' && curChar != '\n') {
				buffer += curChar;
				nextChar();
			}
			
			if(posValid() && curChar == '\"') {
				nextChar();
				char* s = new char[buffer.size() + 1];
				for(unsigned i = 0; i < buffer.size(); i++) {
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

		if(posValid() && (isalpha(curChar) || curChar == '_')) {
			std::string buffer;
			while(posValid() && (isalnum(curChar) || curChar == '_')) {
				buffer += curChar;
				nextChar();
			}

			if(buffer == "null") {
				tokens.push_back(Token(TT_NULL));
			}
			else if(buffer == "pinf") {
				tokens.push_back(Token(TT_PINF));
			}
			else if(buffer == "ninf") {
				tokens.push_back(Token(TT_NINF));
			}
			else if(buffer == "true") {
				tokens.push_back(Token(true));
			}
			else if(buffer == "false") {
				tokens.push_back(Token(false));
			}
			else {
				char* s = new char[buffer.size() + 1];
				for(unsigned i = 0; i < buffer.size(); i++) {
					s[i] = buffer[i];
				}
				s[buffer.size()] = '\0';
				
				tokens.push_back(Token(TT_NAME, s));
			}
			continue;
		}

		if(posValid() && isdigit(curChar) && curChar != '0') {
			std::string buffer;
			
			while(posValid() && isdigit(curChar)) {
				buffer += curChar;
				nextChar();
			}
			
			if(posValid() && curChar == '.') {
				buffer += curChar;
				nextChar();
				
				if(posValid() && isdigit(curChar)) {
					while(posValid() && isdigit(curChar)) {
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
	if(cur + 1 >= tokens.size() || cur + 1 < 0) return nullToken;
	else return tokens[cur + 1];
}

const Token& Tokenizer::getCurToken() const {
	if(cur >= tokens.size() || cur < 0) return nullToken;
	else return tokens[cur];
}

void Tokenizer::clear() {
	tokens.clear();
}
