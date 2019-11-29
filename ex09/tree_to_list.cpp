#include <iostream>

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
				NULL),
			createTree(8,
				createTree(6,
					NULL,
					createTree(7)),
				createTree(10, 
					NULL,
					NULL)));	
}

node<int>* findLastElement(node<int> * l) {
	if (NULL == l) {
		return NULL;
	}
	if (NULL == l->right) {
		return l;
	}
	return findLastElement(l->right);
}

// void treeToList(node<int> * root, node<int>*& start) {
// }
// 
// node<int>* treeToList(node<int> * root) {
// 	node<int>* start = root;
// 	treeToList(root, start);
// 	return start;
// }


node<int>* treeToList(node<int> * root, node<int>*& start) {
	if (NULL == root) {
		return NULL;
	}

	if (NULL == root->left && NULL == root->right) {
		return root;
	}

	if (NULL == root->left) { // diagram: right subtree
		node<int> * rightStart = treeToList(root->right);
		rightStart->left = root;
		root->right = rightStart;
		return root;
	}

	if (NULL == root->right) {
		node<int> * leftStart = treeToList(root->left);
		node<int> * leftEnd = findLastElement(leftStart);
		
		root->left = leftEnd;
		leftEnd->right = root;

		return leftStart;
	}

	// diagram: left & right subtree
	node<int> * rightStart = treeToList(root->right);
	node<int> * leftStart = treeToList(root->left);
	node<int> * leftEnd = findLastElement(leftStart);

	// connect with left list
	root->left = leftEnd;
	leftEnd->right = root;

	// connect with right list
	rightStart->left = root;
	root->right = rightStart;

	return leftStart;
}

void printList(node<int> * l) {
	if (NULL == l) {
		cout << endl;
		return;
	}
	cout << l->data << " ";
	printList(l->right);
}

void printListReverse(node<int> * l) {
	if (NULL == l) {
		cout << endl;
		return;
	}
	cout << l->data << " ";
	printListReverse(l->left);
}


int main() {
	node<int>* start = treeToList(createSample());
	printList(start);
	printListReverse(findLastElement(start));
	
	return 0;
}

