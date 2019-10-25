#include <iostream>
#include <list>

using namespace std;

void eraseEvenIndexes(list<int>& l) {
	int i = 0;
	for (list<int>::iterator it = l.begin(); it != l.end(); it++, i++) {
		if (i % 2 == 0) {
			l.erase(it);	
		}
	}
}

list<int> reverse(list<int> l) {
	list<int> result;
	// better for Single Linked List
	for (list<int>::iterator it = l.begin(); it != l.end(); it++) {
		result.push_front(*it);
	}

	// OK if Double Linked List
	// for (list<int>::reverse_iterator it = l.rbegin(); it != l.rend(); it++) {
	// 	result.push_back(*it);
	// }

	return result;
}

list<int> generateFibonacciIndexes(int maxNumber) {
	list<int> result;

	if (maxNumber <= 0) {
		return result;
	}

	int fibA = 0;
	int fibB = 1;

	result.push_back(0); // maxNumber is at least 1
	while (fibB < maxNumber) {
		result.push_back(fibB);
		fibB = fibB + fibA;
		fibA = fibB - fibA;
	}
	return result;
}

void printFibonacci(list<int> l) {
	if (l.size() == 0) {
		return;
	}

	if (l.size() == 1) {
		cout << l.front() << endl; // print the first element
		return;
	}

	list<int> fibonacciIndexes = generateFibonacciIndexes(l.size());
	list<int>::iterator fibonacciIterator = fibonacciIndexes.begin();
	int prevFibonacciIndex = 0; 
	int currentFibonacciIndex = 0;
	fibonacciIterator++;

	list<int>::iterator it = l.begin();
	cout << *it << " "; // index 0

	while (fibonacciIterator != fibonacciIndexes.end()) {
		prevFibonacciIndex = currentFibonacciIndex;
		currentFibonacciIndex = *fibonacciIterator;

		advance(it, currentFibonacciIndex - prevFibonacciIndex);
		cout << *it << " ";

		fibonacciIterator++;
	}
	
	cout << endl;
}


void eraseEvenIndexesWithAdvance(list<int>& l) {
	for (list<int>::iterator it = l.begin(); it != l.end(); advance(it, 2)) {
		l.erase(it);	
	}
}

void print(list<int>& l) {
	for (list<int>::iterator it = l.begin(); it != l.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}

void printReverse(list<int>& l) {
	for (list<int>::reverse_iterator it = l.rbegin(); it != l.rend(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}


int main() {
	list<int> l;
	l.push_back(5);
	l.push_front(4);
	l.push_back(7);
	l.push_front(3);
	print(l);
	// expected: 3 4 5 7

	list<int> reversed = reverse(l);
	print(reversed);
	// expected: 7 5 4 3

	printFibonacci(l);
	// expected: 3 4 4 5 7

	printReverse(l);
	// expected: 7 5 4 3

	eraseEvenIndexesWithAdvance(l);
	print(l);
	// expected 4 7

	return 0;
}











