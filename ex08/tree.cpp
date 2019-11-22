#include <iostream>

using namespace std;

template <class T>
struct node {
	T data;
	node<T> * left;
	node<T> * right;
};

template <class T>
node<T>* findElement(node<T>* tree, T element) {
	return NULL;
}

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

node<int>* createSample() {
	return 
		createTree(5,
			createTree(3, 
				createTree(2, 
					createTree(1),
					NULL), 
				createTree(4)),
			createTree(10,
				createTree(7,
					createTree(6),
					NULL),
				createTree(15, 
					NULL,
					createTree(17,
						NULL,
						createTree(20)))));
	
}

int main() {
	return 0;
}

