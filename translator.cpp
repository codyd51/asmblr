#include "parser.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <map>
#include <sstream>
#include <fstream>
#include <iterator>
#include <algorithm>

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

void error(string errorStr, unsigned lineNumber) {
	cout << "Error (line " << to_string(lineNumber) << "): " << errorStr << "." << endl;
	exit(1);
}

string translateStatement(StatementAST stmt, unsigned lineNumber) {
	string result = "";
	if (InstructionLookupTable.find(stmt.instruction.strVal) == InstructionLookupTable.end()) {
		string errorStr = "Unknown instruction " + stmt.instruction.strVal;
		error(errorStr, lineNumber);
	}
	string opCode = InstructionLookupTable.at(stmt.instruction.strVal);
	result += opCode;
	for (int i = 0; i < stmt.instruction.argCount; i++) {
		OperandAST operand = stmt.operands.at(i);	
		if (operand.type == Register) {
			if (RegisterLookupTable.find(operand.strVal) == RegisterLookupTable.end()) {
				string errorStr = "Unknown register " + operand.strVal;
				error(errorStr, lineNumber);
			}
			string reg = operand.strVal;
			result += RegisterLookupTable.at(reg);
		}
		else if (operand.type == Number) {
			//convert int to hex
			stringstream sstream;
			sstream << hex << operand.intVal;
			result += sstream.str();
			//lower 2 bytes of hex
			result += "00";
		}
	}
	return result;
}

string binaryFromHex(string hex) {
	string ret = "";
	for (unsigned i = 0; i < hex.length(); i++) {
		switch (hex[i]) {
			case '0': ret.append("0000");  break;
			case '1': ret.append("0001");  break;
			case '2': ret.append("0010");  break;
			case '3': ret.append("0011");  break;
			case '4': ret.append("0100");  break;
			case '5': ret.append("0101");  break;
			case '6': ret.append("0110");  break;
			case '7': ret.append("0111");  break;
			case '8': ret.append("1000");  break;
			case '9': ret.append("1001");  break;
			case 'A': ret.append("1010");  break;
			case 'B': ret.append("1011");  break;
			case 'C': ret.append("1100");  break;
			case 'D': ret.append("1101");  break;
			case 'E': ret.append("1110");  break;
			case 'F': ret.append("1111");  break;
		}
	}
	return ret;
}

vector<string> hexBytesFromString(string str) {
	vector<string> ret;
	string buff;
	for (unsigned i = 0; i < str.length(); i++) {
		buff += str[i];
	
		if (buff.length() >= 4) {
			ret.push_back(buff);
			buff = "";
		}
	}
	
	//handle strings with uneven number of characters
	//if it was odd, we still have a character left over
	//if (buff.length() != 0) {
	//	ret.push_back(buff);
	//}
	return ret;
}

void writeRawHexStringToFile(string str, ofstream& file) {
	istringstream buff(str);
	int hexVal;
	buff >> hex >> hexVal;	
	file.write(reinterpret_cast<char*>(&hexVal), sizeof(int));
}

void writeHexStringToFile(string header, ofstream& file) {
	vector<string> hexBytes = hexBytesFromString(header);
	for (unsigned i = 0; i < hexBytes.size(); i++) {
		istringstream buff(hexBytes.at(i));
		int hexVal;
		buff >> hex >> hexVal;
		cout << "writing " << buff << " (of length " << buff.str().length() << ") as " << hexVal << endl;
		file.write(reinterpret_cast<char*>(&hexVal), sizeof(int));
	}
}

void writeHeader(ofstream& file) {
/*	istringstream header("464c457f");
	int hexVal;
	header >> hex >> hexVal;
	file.write(reinterpret_cast<char*>(&hexVal), sizeof(hexVal));	
*/
	int hexVal;
	string header = "464c457f";
	writeRawHexStringToFile(header, file);
/*
	istringstream headerInfo("A1");
	hexVal = 0;
	headerInfo >> hex >> hexVal;
	file.write(reinterpret_cast<char*>(&hexVal), sizeof(hexVal));
*/
//	string headerInfo = "a1";
//	writeHexStringToFile(headerInfo, file);
	//istringstream headerInfo("00010101");
	//append last 9 bytes we need
	//a full ELF header is 16 bytes, but we only use the top 7
	//4 for ELF magic, 3 below
	//append last 9 bytes last since we're little endian
	//istringstream headerInfo("000000000000000000");
	
	//headerInfo += "000000000000000000";
	//append other 3 used bytes in header
	istringstream headerInfo("00010101");
	hexVal = 0;
	headerInfo >> hex >> hexVal;
	file.write(reinterpret_cast<char*>(&hexVal), sizeof(hexVal));

	for (int i = 0; i < 2; i++) {
		istringstream headerInfo("0000");
		hexVal = 0;
		headerInfo >> hex >> hexVal;
		file.write(reinterpret_cast<char*>(&hexVal), sizeof(hexVal));
	}

	istringstream footer("00030001");
	hexVal = 0;
	footer >> hex >> hexVal;
	file.write(reinterpret_cast<char*>(&hexVal), sizeof(hexVal));

	istringstream footer2("0001");
	hexVal = 0;
	footer2 >> hex >> hexVal;
	file.write(reinterpret_cast<char*>(&hexVal), sizeof(hexVal));
/*
	istringstream headerInfoStream(headerInfo);

	hexVal = 0;
	headerInfoStream >> hex >> hexVal;
	file.write(reinterpret_cast<char*>(&hexVal), sizeof(hexVal));
*/
}

int main(int argv, char** args) {
	vector<StatementAST> stmtList = generateAST();

	vector<string> hexStmtList;
	
	for (unsigned i = 0; i < stmtList.size(); i++) {
		StatementAST stmt = stmtList.at(i);
		hexStmtList.push_back(translateStatement(stmt, i));
	}

	cout << endl;
	for (unsigned i = 0; i < hexStmtList.size(); i++) {
		cout << hexStmtList.at(i) << endl;
	}

	ofstream file("asmbld.o", ios::out | ios::binary);
	
	writeHeader(file);
	
	for (unsigned i = 0; i < hexStmtList.size(); i++) {
		writeHexStringToFile(hexStmtList.at(i), file);
	}

	file.close();

	return 0;
}


