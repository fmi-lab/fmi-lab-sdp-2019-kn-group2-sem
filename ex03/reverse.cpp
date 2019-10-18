#include <iostream>
#include <queue>
#include <stack>


using namespace std;

void copy(queue<int> & from, stack<int> & to) {
	while (!from.empty()) {
		to.push(from.front());
		from.pop();
	}
}

void copy(stack<int> & from, queue<int> & to) {
	while (!from.empty()) {
		to.push(from.top());
		from.pop();
	}
}

queue<int> reverse(queue<int> q) {
	stack<int> reversed;
	queue<int> result;

	copy(q, reversed);
	copy(reversed, result);

	return result;
}

void print(queue<int> q) {
	while (!q.empty()) {
		cout << q.front() << endl; 
		q.pop();
	}
}

int main() {
	queue<int> q1;
	q1.push(5);
	q1.push(6);
	q1.push(7);
	q1.push(8);
	q1.push(9);
	
	print(reverse(q1));
	
	return 0;
}



