#include <iostream>
#include <queue>

using namespace std;

void print(queue<int> q) {
	while (!q.empty()) {
		cout << q.front() << endl; 
		q.pop();
	}
}

int minElement(queue<int>& q) {
	if (q.empty()) {
		return 0;
	}

	int qSize = q.size();
	int min = q.front();
	for (int i = 0; i < qSize; i++) {
		int curr = q.front();

		if (min > curr) {
			min = curr;
		}
		
		q.pop();
		q.push(curr);
	}

	return min;
}

int main() {
	queue<int> q1;
	q1.push(5);
	q1.push(6);
	q1.push(7);
	q1.push(8);
	q1.push(9);
	
	print(q1);
	cout << "minElement: " << minElement(q1) << endl;
	print(q1);
	
	return 0;
}



