#include <iostream>
using namespace std;

struct node {
	int data;
	node* left, *right;
};

class BST {
public:
	node* root = NULL;

	node* insert(node* tmp, int data) {
		if (tmp == NULL) {
			tmp = new node;
			tmp->data = data;
			tmp->right = tmp->left = NULL;
		}
		else if (tmp->data > data) {
			tmp->right = insert(tmp->right, data);
		}
		else if (tmp->data < data) {
			tmp->left = insert(tmp->left, data);
		}
		else {
			cout << "Duplicate" << endl;
		}
		return tmp;
	}

	node* getAncestor(node* tmp) {
		if (tmp == NULL) 
			return NULL;
		else if (tmp->left) 
			tmp = getAncestor(tmp->left);
		return tmp;
	}

	node* remove(node* tmp, int data) {
		if (tmp == NULL) return NULL;
		else if (tmp->data > data) {
			tmp->right = remove(tmp->right, data);
		}
		else if (tmp->data < data) {
			tmp->left = remove(tmp->left, data);
		}
		else {
			// value found
			if (tmp->right == NULL && tmp->left == NULL) {
				delete tmp;
				tmp = NULL;
			}
			else if (tmp->right != NULL && tmp->left == NULL) {
				node* tmp2 = tmp->right;
				delete tmp;
				tmp = tmp2;
			}
			else if (tmp->left != NULL && tmp->right == NULL) {
				node* tmp2 = tmp->left;
				delete tmp;
				tmp = tmp2;
			}
			else {
				node* ances = getAncestor(tmp->right);
				tmp->data = ances->data;
				tmp->right = remove(tmp->right, tmp->data);
			}
		}
		return tmp;
	}

	void inOrder(node *root) {
		if (root == NULL) {
			cout << "Empty";
		}
		else {
			if (root->left) inOrder(root->left);
			cout << root->data << " ";
			if (root->right) inOrder(root->right);
		}
	}
};

int main() {
	BST tree;
	tree.root = tree.insert(tree.root, 10);
	tree.root = tree.insert(tree.root, 20);
	tree.root = tree.insert(tree.root, 30);

	tree.root = tree.remove(tree.root, 10);

	tree.inOrder(tree.root);

	return 0;
}