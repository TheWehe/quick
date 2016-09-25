#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <vector>
#include <string>

enum TokenType {
	TT_NONE,
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
	TT_NEWLINE,
	TT_TAB
};

struct Token {
	Token() = default;
	explicit Token(TokenType type) : type(type) {}
	explicit Token(int i) : type(TT_INT), i(i) {}
	explicit Token(float f) : type(TT_FLOAT), f(f) {}
	explicit Token(bool b) : type(TT_BOOL), b(b) {}
	Token(TokenType type, char* s) : type(type), s(s) {}

	TokenType type = TT_NONE;
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
	void nextToken();
	const Token& peekToken() const;
	const Token& getCurToken() const;

private:
	void clear();

	Token nullToken;
	std::vector<Token> tokens;
	unsigned cur = 0;
};

#endif
