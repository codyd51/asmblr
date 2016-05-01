#include "lexer.h"
#include <iostream>
#include <string>

using namespace std;

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
