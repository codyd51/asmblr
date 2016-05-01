#include "lexer.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Token currTok;

struct Statement {
	Token Instruction;
	vector<Token> Operands;
};

Token getTok() {
	currTok = getToken();
	return currTok;
}

Statement parseStatement() {
	Statement stmt;
	stmt.Instruction = currTok;
	
	if (currTok.argCount > 0) {
		stmt.Operands.push_back(getTok());
		for (int i = 1; i < currTok.argCount - 1; i++) {
			//eat comma
			getTok();
			
			stmt.Operands.push_back(getTok());
		}
	}

	return stmt;
}

int main(int argv, char** args) {
	vector<Statement> stmtList;
	while (getTok().type != EOFTok) {
		Statement stmt = parseStatement();
		stmtList.push_back(stmt);
		cout << "{Instruction} " << stmt.Instruction.strVal << endl;
		for (int i = 0; i < stmt.Operands.size(); i++) {
			cout << "{Operand} " << stmt.Operands.at(i).strVal << endl;
		}
	}

	return 0;
}
