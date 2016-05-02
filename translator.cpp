#include "parser.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <map>
#include <sstream>

//static readonly lookup table
//used to convert mnemonics into raw hex instructions
const static map<string, string> InstructionLookupTable = {
	{ "mov", "66" },
	{ "ret", "c3" }
};

//lookup table to convert registers into corresponding codes
const static map<string, string> RegisterLookupTable = {
	{ "ax", "b8" },
	{ "cx", "b9" },
	{ "dx", "ba" },
	{ "bx", "bb" },
	{ "sp", "bc" },
	{ "bp", "bd" },
	{ "si", "be" },
	{ "di", "bf" }
};

string translateStatement(StatementAST stmt) {
	string result = "";
	string opCode = InstructionLookupTable.at(stmt.instruction.token.strVal);
	result += opCode;
	for (int i = 0; i < stmt.instruction.token.argCount; i++) {
		if (stmt.operands.at(i).token.type == Register) {
			string reg = stmt.operands.at(i).token.strVal;
			result += RegisterLookupTable.at(reg);
		}
		else if (stmt.operands.at(i).token.type == Number) {
			//convert int to hex
			stringstream sstream;
			sstream << hex << stmt.operands.at(i).token.intVal;
			result += sstream.str();
			//lower 2 bytes of hex
			result += "00";
		}
	}
	return result;
}

int main(int argv, char** args) {
	vector<StatementAST> stmtList = generateAST();

	vector<string> hexStmtList;
/*
	for (unsigned i = 0; i < stmtList.size(); i++) {
		StatementAST stmt = stmtList.at(i);
		cout << "{Instruction} " << stmt.instruction.token.strVal;
		for (unsigned j = 0; j < stmt.operands.size(); j++) {
			cout << " {Operand} " << stmt.operands.at(j).token.strVal;
		}
		cout << endl;

		hexStmtList.push_back(translateStatement(stmt));
	}
*/
	for (unsigned i = 0; i < stmtList.size(); i++) {
		StatementAST stmt = stmtList.at(i);
		hexStmtList.push_back(translateStatement(stmt));
	}

	cout << endl;
	for (unsigned i = 0; i < hexStmtList.size(); i++) {
		cout << hexStmtList.at(i) << endl;
	}

	return 0;
}


