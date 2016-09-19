#include "tokenizer.hpp"


Tokenizer::~Tokenizer() {
	clear();
}

void Tokenizer::tokenize(const std::string& code) {
	
}

Token* Tokenizer::getNextToken(bool peek) {
	if(cur >= tokens.size()) return nullptr;
	
	if(peek) {
		return &tokens[cur];
	}
	else {
		return &tokens[cur++];
	}
}

void Tokenizer::clear() {
	for(auto& t : tokens) {
		if(t.type == TT_STRING) {
			delete[] t.s;
		}
	}
}
