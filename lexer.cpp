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

	//comma separating operands
	if (lastChar == ',') {
		token.type = Comma;
		token.strVal = ",";
		lastChar = getchar();
	}

	//don't eat EOF!
	else if (lastChar == EOF || lastChar == '\n' || lastChar == '\r' || lastChar == 'q') {
		token.type = EOFTok;
	}

	//identifier
	else if (isalpha(lastChar)) {
		string tokenStr;

		//while there are characters to read, build up this identifier
		while (isalnum(lastChar)) {
			tokenStr += lastChar;
			lastChar = getchar();
		}
	
		//match keywords here
		if (tokenStr == "ret") {
			token.type = Instruction;
		}
		else if (tokenStr.at(0) == 'r' || tokenStr.at(0) == 'R') {
			token.type = Register;
		}
		else {
			//unknown!
			cout << "Unknown token encountered: " << tokenStr << endl;
			exit(1);
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

