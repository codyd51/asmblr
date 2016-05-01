#include "lexer.h"
#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <string>
#include <stdlib.h>
using namespace std;

Token getToken() {
	Token token;
	static int lastChar = ' ';

	//skip any whitespace
	while (isspace(lastChar)) {
		lastChar = getchar();
	}

	//identifier
	if (isalpha(lastChar)) {
		string tokenStr;

		//while there are characters to read, build up this identifier
		while (isalpha(lastChar)) {
			tokenStr += lastChar;
			lastChar = getchar();
		}
	
		//match keywords here
		if (tokenStr == "ret") {
			token.type = Instruction;
		}
		else {
			token.type = Register;
		}

		token.strVal = tokenStr;
	}

	//numbers
	else if (lastChar == '#') {
		//while we have numbers to read, build up this number
		lastChar = getchar();
		string tokenStr;
		tokenStr += lastChar;
		while (isdigit(lastChar = getchar())) {
			tokenStr += lastChar;
		}

		token.type = Number;
		token.intVal = atoi(tokenStr.c_str());
	}

	//comments
	else if (lastChar == ';') {
		//skip to end of line
		do {
			lastChar = getchar();
		} while (lastChar != EOF && lastChar != '\n' && lastChar != '\r');

		//we skipped to the end of this line, so return the next token
		if (lastChar != EOF) {
			return getToken();
		}
	}

	//don't eat EOF!
	else if (lastChar == EOF || lastChar == '\n' || lastChar == '\r') {
		token.type = EOFTok;
	}

	//unknown token encountered
	else {
		//get full token string, then tell them it's unrecognized
		string tokenStr;
		while (!isspace(lastChar)) {
			tokenStr += lastChar;
			lastChar = getchar();
		}
		cout << "Unknown token encountered: " << tokenStr << endl;
		exit(1);
	}

	return token;
}

int main(int argv, char** args) {
	Token token;
	while ((token = getToken()).type != EOFTok) {
		if (token.type == Number) {
			cout << "Number " << token.intVal << endl;
		}
		else {
			if (token.type == Instruction) {
				cout << "Instruction ";
			}
			else if (token.type == Register) {
				cout << "Register ";
			}
			cout << token.strVal << endl;
		}
	}

	return 0;
}	
