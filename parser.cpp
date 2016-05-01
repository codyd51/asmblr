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
	if (currTok.type == Instruction) {
		stmt.Instruction = currTok;
	}
	else {
		cout << "Expected instruction, received '" << currTok.strVal << "'" << endl;
	}
	
	if (currTok.argCount > 0) {
		getTok();
		if (currTok.type == Register || currTok.type == Number) {
			stmt.Operands.push_back(currTok);
			for (int i = 1; i < currTok.argCount - 1; i++) {
				//eat comma
				getTok();
				if (currTok.type == Comma) {
					getTok();
					if (currTok.type == Register || currTok.type == Number) {
						stmt.Operands.push_back(currTok);
					}
				}
				else {
					cout << "Expected comma, received '" << currTok.strVal << "'" << endl;
				}
			}
		}
		else {
			cout << "Expected register or number, received '" << currTok.strVal << "'" << endl;
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
