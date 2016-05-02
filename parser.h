#include "lexer.h"
#include <vector>

using namespace std;

struct InstructionAST {
private:
	Token token;
public:
	string strVal;
	int argCount;
	InstructionAST(Token token) : token(token), strVal(token.strVal), argCount(token.argCount) {}
	InstructionAST() {}
	void setToken(Token tok) {
		token = tok;
		strVal = token.strVal;
		argCount = token.argCount;
	}
};

struct OperandAST {
private:
	Token token;
public:
	string strVal;
	int intVal;
	TokenType type;

	OperandAST(Token token) : token(token), strVal(token.strVal), intVal(token.intVal), type(token.type) {}
	OperandAST() {}
	void setToken(Token tok) {
		token = tok;
		strVal = token.strVal;
		intVal = token.intVal;
		type = token.type;
	}
};

struct StatementAST {
	InstructionAST instruction;
	vector<OperandAST> operands;
	StatementAST(InstructionAST instruction, vector<OperandAST> operands) : instruction(instruction), operands(operands) {}
	StatementAST() {}
};

vector<StatementAST> generateAST();
