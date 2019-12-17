#include <iostream>
#include <stack>
#include <vector>

using namespace std;


template <class T>
struct node {
	T data;
	node<T> * left;
	node<T> * right;
};

node<int>* createTree(
	int data, 
	node<int>* left = NULL, 
	node<int>* right = NULL) {

	node<int>* root = new node<int>;
	root->data = data;
	root->left = left;
	root->right = right;
	return root;
}

template<class T>
void deleteTree(node<T> * tree) {

}

node<int>* createSample() {
	return 
		createTree(5,
			createTree(4, 
				createTree(1, 
					NULL,
					NULL), 
				createTree(15, NULL, NULL)),
			createTree(8,
				createTree(6,
					NULL,
					createTree(7)),
				createTree(10, 
					NULL,
					NULL)));
}

void print(stack<node<int>* > s) 
{ 
    while (!s.empty()) 
    { 
        cout << s.top()->data << endl; 
        s.pop(); 
    } 
    cout << '\n'; 
} 

// Left, Root, Right
void printRecursive(node<int>* root) {
	if (root == NULL) {
		return;
	}
	printRecursive(root->left);
	cout << root->data << endl;
	printRecursive(root->right);
}

bool contains(vector<node<int>* > v, node<int>* element) {
	return (v.end() != find(v.begin(), v.end(), element));
}

void printLRRi(node<int>* root) {
	if (root == NULL) {
		return;
	}
	vector<node<int>* > visited;
	stack<node<int>* > s;
	s.push(root);

	while (true) {
		if (s.empty()) {
			break;
		}

		node<int>* leftElement = s.top()->left;
		node<int>* rightElement = s.top()->right;

		if (leftElement != NULL && !contains(visited, leftElement)) {
			s.push(leftElement);
		} else {
			cout << s.top()->data << endl;
			visited.push_back(s.top());
			s.pop();

			if (rightElement != NULL && !contains(visited, rightElement)) {
				s.push(rightElement);
			}
		}
	}
}

void printRLRi(node<int>* tree) {
	if (tree == NULL) {
		return;
	}
	stack<node<int>* > s;
	s.push(tree);

	while (true) {
		if (s.empty()) {
			break;
		}
		node<int>* root = s.top();
		cout << root->data << endl;;
		s.pop();

		node<int>* leftElement = root->left;
		node<int>* rightElement = root->right;

		if (rightElement != NULL) {
			s.push(rightElement);
		}

		if (leftElement != NULL) {
			s.push(leftElement);
		}
	}
}


int main() {
	printRecursive(createSample());
	cout << "With STACK" << endl;
	printLRRi(createSample());
	cout << "With STACK ROOT, LEFT, RIGHT" << endl;
	printRLRi(createSample());
	return 0;
}



