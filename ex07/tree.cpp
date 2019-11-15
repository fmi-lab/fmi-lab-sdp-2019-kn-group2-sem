#include <iostream>

using namespace std;

template <class T>
struct node {
	T data;
	node<T> * left;
	node<T> * right;
};

node<int> * createTree() {
	node<int> * l11 = new node<int>();
	l11->data = 2;
	l11->left = NULL;
	l11->right = NULL;

	node<int> * l12 = new node<int>();
	l12->data = 4;
	l12->left = NULL;
	l12->right = NULL;

	node<int> * l1 = new node<int>();
	l1->data = 3;
	l1->left = l11;
	l1->right = l12;

	node<int> * r11 = new node<int>();
	r11->data = 6;
	r11->left = NULL;
	r11->right = NULL;

	node<int> * r12 = new node<int>();
	r12->data = 8;
	r12->left = NULL;
	r12->right = NULL;

	node<int> * r1 = new node<int>();
	r1->data = 7;
	r1->left = r11;
	r1->right = r12;

	node<int> * root = new node<int>();
	root->data = 5;
	root->left = l1;
	root->right = r1;

	return root;
}

template <class T> 
void deleteTree(node<T> * root) {
	if (NULL == root) {
		return;
	}

	deleteTree(root->left);
	deleteTree(root->right);

	delete root;
}

int sum(node<T> * root) {

}

template <class T> 
int height(node<T> * root) {
	if (NULL == root) { // empty tree
		return 0;
	}

	return 1 + max(height(root->left), 
				   height(root->right));
}

int main() {
	node<int> * root = createTree();
	cout << "The tree height is: "
		 << height(root)
		 << endl;
	deleteTree(root);
	return 0;
}