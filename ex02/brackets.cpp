// Проверка за валидност на скобите

#include <iostream>
#include <string>
#include <stack>

using namespace std;

const string OPEN_BRACKETS = "([{<";
const string CLOSE_BRACKETS = ")]}>";

bool isOpenBracket(char c) {
	return 0 <= ((int) OPEN_BRACKETS.find(c));
}

bool isCloseBracket(char c) {
	// find() returns size_t = unsigned int
	return 0 <= ((int) CLOSE_BRACKETS.find(c));
}

bool isMatchingBracket(char openBracket, char closeBracket) {
	int bracketIdx = OPEN_BRACKETS.find(openBracket);
	return closeBracket == CLOSE_BRACKETS[bracketIdx];
}

bool hasValidBrackets(string expr) {
	stack<char> openBrackets;

	for (int i = 0; i < expr.size(); i++) {
		char currentChar = expr[i];

		if (isOpenBracket(currentChar)) {
			openBrackets.push(currentChar);

		} else if (isCloseBracket(currentChar)) {
			if (!openBrackets.empty() 
				&& isMatchingBracket(openBrackets.top(), 
									 currentChar)) {
				openBrackets.pop();
			} else {
				return false;
			}
		}
	}

	return openBrackets.empty();
}

int main() {
	cout << hasValidBrackets("()") << endl;
	cout << hasValidBrackets("(") << endl;
	cout << hasValidBrackets("}") << endl;
	cout << hasValidBrackets("{[()]}") << endl;
	cout << hasValidBrackets("<{[()]}>") << endl;
	cout << hasValidBrackets("(<{[()]}>)") << endl;
	cout << hasValidBrackets("asd(asda<dd>ddd(asd{123[sa(a<a)d]ba}as)<d>asd)a") << endl;
	return 0;
}