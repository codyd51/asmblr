#include <string>

enum TokenType {
	Instruction = 0,
	Register,
	Number,
	Comma,
	EOFTok
};

struct Token {
	TokenType type;
	std::string strVal;
	int intVal;
};

Token getToken();
