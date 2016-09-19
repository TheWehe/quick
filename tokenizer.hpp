#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <vector>

enum TokenType {
	TT_NAME,
	
	TT_NULL,
	TT_PINF,
	TT_NINF,
	TT_INT,
	TT_FLOAT,
	TT_BOOL,
	TT_STRING,
	
	TT_EQUAL,
	TT_PLUS,
	TT_MINUS,
	TT_STAR,
	TT_SLASH,
	
	TT_ENDLINE,
	TT_TAB
};

struct Token {
	TokenType type;
	
	union {
		int i;
		float f;
		bool b;
		char* s;
	};
};

class Tokenizer {
public:
	~Tokenizer();
	
	void tokenize(const std::string& code);
	Token* getNextToken(bool peek = false);
	
private:
	void clear();
	
	std::vector<Token> tokens;
	int cur = 0;
};

#endif
