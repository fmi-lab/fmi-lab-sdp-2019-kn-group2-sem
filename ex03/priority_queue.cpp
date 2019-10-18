#include <iostream>
#include <queue>

using namespace std;

template<class T, int NUMBER_OF_PRIORITIES = 4>
class PriorityQueue {
public:
	void push(T x, int priority = 0) { // 0 = lowest
		if (priority >= NUMBER_OF_PRIORITIES) {
			throw "Unsupported priority";
		}

		qs[priority].push(x);
	}
	
	void pop() {
		for (int priority = NUMBER_OF_PRIORITIES - 1; priority >=0; priority--) {
			if (!qs[priority].empty()) {
				qs[priority].pop();
				return;
			}
		}
	}
	
	T front() const {
		for (int priority = NUMBER_OF_PRIORITIES - 1; priority >=0; priority--) {
			if (!qs[priority].empty()) {
				return qs[priority].front();
			}
		}

		throw "Empty queue";
	}
	
	bool empty() const {
		for (int priority = 0; priority < NUMBER_OF_PRIORITIES; priority++) {
			if (!qs[priority].empty()) {
				return false;
			}
		}
		return true;
	}
	
	int size() const {
		int totalSize = 0;
		for (int priority = 0; priority < NUMBER_OF_PRIORITIES; priority++) {
			totalSize += qs[priority].size();
		}
		return totalSize;
	}

private:
	queue<T> qs[NUMBER_OF_PRIORITIES];
};

int main() {
	PriorityQueue<int, 5> q;
	q.push(1, 4);
	q.push(2, 2);
	q.push(3, 1);
	q.push(4, 3);
	// 4, 2, 3, 1

	cout << (q.front()) << endl;
	q.pop();
	cout << (q.front()) << endl;
	q.pop();
	cout << (q.front()) << endl;
	q.pop();
	cout << (q.front()) << endl;
	q.pop();

	return 0;
}
