#include "lexer.h"
#include <vector>

using namespace std;

struct InstructionAST {
	Token token;
	InstructionAST(Token token) : token(token) {}
	InstructionAST() {}
};

struct OperandAST {
	Token token;
	//bool position;
	OperandAST(Token token) : token(token) {}
	OperandAST() {}
};

struct StatementAST {
	InstructionAST instruction;
	vector<OperandAST> operands;
	StatementAST(InstructionAST instruction, vector<OperandAST> operands) : instruction(instruction), operands(operands) {}
	StatementAST() {}
};

vector<StatementAST> generateAST();
