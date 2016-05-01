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
		string errorStr = "Expected type " + to_string(type) + ", received type " + to_string(currTok.type);
		error(errorStr);
	}
}

void match(string str) {
	if (currTok.strVal != str) {
		string errorStr = "Expected " + str + ", received " + currTok.strVal;
		error(errorStr);
	}
	getTok();
}
	

InstructionAST parseInstruction() {
	verifyType(Instruction);
	InstructionAST ret(currTok);
	getTok();
	return ret;
}

OperandAST parseOperand() {
	//verifyType only handles checking one type, whereas an operand can be a register or number
	//check manually for now
	if (currTok.type != Register && currTok.type != Number) {
		verifyType(Register);
	}
	OperandAST operand(currTok);
	getTok();
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
	getTok();
	while (currTok.type != EOFTok) {
		StatementAST stmt = parseStatement();
		stmtList.push_back(stmt);
	}

	for (unsigned i = 0; i < stmtList.size(); i++) {
		StatementAST stmt = stmtList.at(i);
		cout << "{Instruction} " << stmt.instruction.token.strVal;
		for (unsigned j = 0; j < stmt.operands.size(); j++) {
			cout << " {Operand} " << stmt.operands.at(j).token.strVal;
		}
		cout << endl;
	}


	return 0;
}
