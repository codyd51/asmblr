#include "lexer.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

Token currTok;

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

Token getTok() {
	currTok = getToken();
	return currTok;
}

void error(string errorStr) {
	cout << "Error: " << errorStr << "." << endl;
	exit(1);
}

void verifyType(TokenType type) {
	if (currTok.type != type) {
		string errorStr = "Expected type " + type + ", received type "+currTok.type;
		error(errorStr);
	}
}

void match(string str) {
	getTok();
	if (currTok.strVal != str) {
		string errorStr = "Expected " + str + ", received " + currTok.strVal;
		error(errorStr);
	}
}
	

InstructionAST parseInstruction() {
	getTok();

	verifyType(Instruction);
	InstructionAST ret(currTok);
	return ret;
}

OperandAST parseOperand() {
	getTok();

	//verifyType only handles checking one type, whereas an operand can be a register or number
	//check manually for now
	if (currTok.type != Register && currTok.type != Number) {
		verifyType(Register);
	}
	OperandAST operand(currTok);
	return operand;
}



StatementAST parseStatement() {
	StatementAST stmt;
	stmt.instruction = parseInstruction();
	
	if (stmt.instruction.token.argCount > 0) {
		stmt.operands.push_back(parseOperand());
	
		for (int i = 1; i < stmt.instruction.token.argCount; i++) {
			//eat comma
			match(",");

			//get next operand
			stmt.operands.push_back(parseOperand());
		}
	}

	return stmt;
}

int main(int argv, char** args) {
	vector<StatementAST> stmtList;
	while (currTok.type != EOFTok) {
		StatementAST stmt = parseStatement();
		stmtList.push_back(stmt);
		cout << "{Instruction} " << stmt.instruction.token.strVal << endl;
		for (int i = 0; i < stmt.operands.size(); i++) {
			cout << "{Operand} " << stmt.operands.at(i).token.strVal << endl;
		}
	}

	return 0;
}
