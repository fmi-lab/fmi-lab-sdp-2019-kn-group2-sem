#include <iostream>
#include <string>
#include <stack>

using namespace std;

string reverse(string str) {
	stack<char> theReverser;
	for (int i = 0; i < str.size(); i++) {
		theReverser.push(str[i]);
	}

	string result;
	while (!theReverser.empty()) {
		result += theReverser.top();
		theReverser.pop();
	}
	
	return result;
}

void example() {
	stack<char> s;
	s.push('a');
	s.push('b');
	s.push('c');
	s.push('d');
	s.push('e');

	s.pop();
	s.pop();

	while (!s.empty()) {
		cout << s.top() << endl;
		s.pop();
	}
}


int main() {
	cout << reverse("") << endl;
	cout << reverse("bala") << endl;
	cout << reverse("ala bala") << endl;
	cout << reverse("ala") << endl;
	cout << reverse("ala?????") << endl;
	return 0;
}





