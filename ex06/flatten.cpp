#include <iostream>
#include <list>
#include <stack>

using namespace std;

template <class T>
struct node {
	T data;
	node<T> * next;
};

// [
// 	[10, 20, 30]
// 	[100, 200, 300, 400]
// 	[1000]
// ] ---> [10, 20, 30, 100, 200, 300, 400, 1000]
list<int> flatten_cpp11(list<list<int> > l) {
	list<int> result;
	for (auto currentList : l) {
		for (auto x : currentList) {
			result.push_back(x);
		}
	}
	return result;
}

list<int> flatten_cpp11Auto(list<list<int> > l) {
	list<int> result;

	for (auto mainIt = l.begin(); mainIt != l.end(); mainIt++) {
	
		list<int> currentList = *mainIt;
		for (auto it = currentList.begin(); it != currentList.end(); it++) {
			result.push_back(*it);
		}
	}
	return result;
}

list<int> flatten(list<list<int> > l) {
	list<int> result;

	for (list<list<int> >::iterator mainIt = l.begin(); 
		mainIt != l.end(); 
		mainIt++) {
	
		list<int> currentList = *mainIt;
		for (list<int>:: iterator it = currentList.begin(); it != currentList.end(); it++) {
			result.push_back(*it);
		}
	}
	return result;
}

void print_cpp11(list<int> l) {
	for (auto x : l) {
		cout << x << " ";
	}
	cout << endl;	
}

void print_cpp11Auto(list<int> l) {
	for (auto it = l.begin(); it != l.end(); it++) {
		cout << (*it) << " ";
	}
	cout << endl;
}

void print(list<int> l) {
	for (list<int>::iterator it = l.begin(); it != l.end(); it++) {
		cout << (*it) << " ";
	}
	cout << endl;
}

void test_flatten_list() {
list<int> l1;
	l1.push_back(10);
	l1.push_back(20);
	l1.push_back(30);

	list<int> l2;
	l2.push_back(100);
	l2.push_back(200);
	l2.push_back(300);
	l2.push_back(400);

	list<int> l3;
	l3.push_back(1000);

	list<list<int> > ll;
	ll.push_back(l1);
	ll.push_back(l2);
	ll.push_back(l3);

	print(flatten_cpp11(ll));
}

node<int> * findLastElement(node<int> * start) {
	if (NULL == start->next) {
		return start;
	}
	return findLastElement(start->next);
}

void print_int(node<int> * start) {
	if (NULL == start) {
		return;
	}
	cout << start->data << " ";
	print_int(start->next);
}

void print(node<int> * start) {
	print_int(start);
	cout << endl;
}

void flatten(node<node<int> * >* start, node<int> * lastElement) {
	if (NULL == start) {
		return;
	}

	if (NULL == start->data) {
		return flatten(start->next, lastElement);
	}

	lastElement->next = start->data;
	flatten(start->next, findLastElement(start->data));
}

node<int> * flatten(node<node<int> * >* start) {
	if (NULL == start) {
		return NULL;
	}

	if (NULL == start->data) {
		return flatten(start->next);
	}

	node<int> * result = start->data;
	flatten(start->next, findLastElement(start->data));
	return result;
}

void test_flatten_node() {
	node<int> n13 = {31, NULL};
	node<int> n12 = {21, &n13};
	node<int> n11 = {11, &n12};

	node<int> n24 = {401, NULL};
	node<int> n23 = {301, &n24};
	node<int> n22 = {201, &n23};
	node<int> n21 = {101, &n22};

	node<int> n31 = {1001, NULL};

	node<node<int>* > n3 = {&n31, NULL};
	node<node<int>* > n2 = {&n21, &n3};
	node<node<int>* > n1 = {&n11, &n2};

	node<int> * result = flatten(&n1);
	print(result);
}


//	           |10|
//	|10|       |20|
//	|20| |100| |30|
//	|30| |200| |40|
//	|--| |---| |--|
//
// 10, 20, 30, 100, 200, 10, 20, 30, 40
// reverse on odds: 30, 20, 10, 100, 200, 40, 30, 20, 10
list<int> flatten(list<stack<int> > data) {
	list<int> result;
	for (list<stack<int> >::iterator it = data.begin(); it != data.end(); it++) {
		stack<int> currentStack = *it;
		while (!currentStack.empty()) {
			result.push_back(currentStack.top());
			currentStack.pop();
		}
	}
	return result;
}

void test_flatten_stack() {
	stack<int> s1;
	s1.push(30);
	s1.push(20);
	s1.push(10);

	stack<int> s2;
	s2.push(200);
	s2.push(100);

	stack<int> s3;
	s3.push(40);
	s3.push(30);
	s3.push(20);
	s3.push(10);

	list<stack<int> > stacks;
	stacks.push_back(s1);
	stacks.push_back(s2);
	stacks.push_back(s3);

	print(flatten(stacks));
}


int main() {
	test_flatten_list();
	test_flatten_node();
	test_flatten_stack();
}












