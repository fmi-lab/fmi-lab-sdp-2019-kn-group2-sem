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

node<int>* createSampleBalanced() {
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
						NULL))));
	
}

template <class T>
node<T>* findElement(node<T>* tree, T element) {
	if (NULL == tree) {
		return NULL;
	}

	if (tree->data == element) {
		return tree;
	} else if (tree->data > element) {
		return findElement(tree->left, element);
	} else {
		return findElement(tree->right, element);
	}
}

void testFindElement() {
	node<int>* myTree = createSample();
	cout << "Find 20: " << findElement(myTree, 20) << endl; 
	cout << "Find -5: " << findElement(myTree, -5) << endl; 
	deleteTree(myTree);	
}

int sumLeafs(node<int> * tree) {
	if (NULL == tree) {
		return 0;
	}

	if (NULL == tree->left && NULL == tree->right) {
		return tree->data;
	}

	return sumLeafs(tree->left) + sumLeafs(tree->right);
}

void testSumLeafs() {
	node<int> * myTree = createSample();
	cout << "31 == " << sumLeafs(myTree) << endl;
	deleteTree(myTree);
}


int sumLeafsByHeight(node<int> * tree, int height = 1) {
	if (NULL == tree) {
		return 0;
	}

	if (NULL == tree->left && NULL == tree->right) {
		return tree->data * height;
	}

	return sumLeafsByHeight(tree->left, height + 1) 
		 + sumLeafsByHeight(tree->right, height + 1);
}

void testSumLeafsByHeight() {
	node<int> * myTree = createSample();
	cout << "140 == " << sumLeafsByHeight(myTree) << endl;
	deleteTree(myTree);
}

template <class T>
int height(node<T> * tree) {
	if (NULL == tree) {
		return 0;
	}

	return 1 + max(height(tree->left), 
				   height(tree->right));
}

template <class T>
bool isAVLBalanced(node<T> * tree) {
	if (NULL == tree) {
		return true;
	}

	int balanceFactor = height(tree->left) - height(tree->right);
	if (-1 <= balanceFactor && balanceFactor <= 1) {
		return isAVLBalanced(tree->left)
		    && isAVLBalanced(tree->right);
	} else {
		return false;
	}
}

void testAVLBalannced() {
	node<int> * unbalancedTree = createSample();
	node<int> * balancedTree = createSampleBalanced();

	cout << "false == " << isAVLBalanced(unbalancedTree) << endl;
	cout << "true == " << isAVLBalanced(balancedTree) << endl;
}

int main() {
	// testFindElement();
	// testSumLeafs();
	// testSumLeafsByHeight();
	testAVLBalannced();
	return 0;
}

