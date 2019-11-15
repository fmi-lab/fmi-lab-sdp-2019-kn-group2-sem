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

node<int> * createTree2() {
	node<int> * l122 = new node<int>();
	l122->data = 10;
	l122->left = NULL;
	l122->right = NULL;

	node<int> * l12 = new node<int>();
	l12->data = 5;
	l12->left = NULL;
	l12->right = l122;

	node<int> * l1 = new node<int>();
	l1->data = 3;
	l1->left = NULL;
	l1->right = l12;

	node<int> * r1 = new node<int>();
	r1->data = 10;
	r1->left = NULL;
	r1->right = NULL;

	node<int> * root = new node<int>();
	root->data = 2;
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

int sum(node<int> * root) {
	if (NULL == root) {
		return 0;
	}

	return root->data 
		 + sum(root->left)
	 	 + sum(root->right);
}

template <class T>
bool isEmpty(node<T> * root) {
	return NULL == root;
}

template <class T>
T coalesce(T t1, T t2) {
	if (NULL != t1) {
		return t1;
	}
	return t2;
}

template <class T>
bool isLeaf(node<T> * node) {
	return isEmpty(node->left) 
	    && isEmpty(node->right);
}

int mult(node<int> * tree1, node<int> * tree2, int lastTree1 = 0, int lastTree2 = 0) {
	if (isEmpty(tree1) && isEmpty(tree2)) {
		return 0;
	}

	if (!isEmpty(tree1)) {
		lastTree1 = tree1->data;
	}

	if (!isEmpty(tree2)) {
		lastTree2 = tree2->data;
	}

	int sum = lastTree1 * lastTree2;

	if (isEmpty(tree1)) {
		sum += mult(tree1, tree2->left, lastTree1, lastTree2)
			 + mult(tree1, tree2->right, lastTree1, lastTree2);
	} else if (isEmpty(tree2)) {
		sum += mult(tree1->left, tree2, lastTree1, lastTree2)
			 + mult(tree1->right, tree2, lastTree1, lastTree2);
	} else {
		sum += mult(tree1->left, tree2->left, lastTree1, lastTree2)
			 + mult(tree1->right, tree2->right, lastTree1, lastTree2);
	}

	return sum;
}

template <class T> 
int height(node<T> * root) {
	if (isEmpty(root)) {
		return 0;
	}

	return 1 + max(height(root->left), 
				   height(root->right));
}

void test_height() {
	node<int> * root = createTree();
	cout << "The tree height is: "
		 << height(root)
		 << endl;
	deleteTree(root);
}

void test_sum() {
	node<int> * root = createTree();
	cout << "The tree sum is: "
		 << sum(root)
		 << endl;
	deleteTree(root);
}

void test_mult() {
	node<int> * tree1 = createTree();
	node<int> * tree2 = createTree2();
	cout << "The tree mult is: "
		 << mult(tree1, tree2)
		 << endl;
	deleteTree(tree1);
	deleteTree(tree2);
}

int main() {
	test_height();
	test_sum();
	test_mult();
	return 0;
}


