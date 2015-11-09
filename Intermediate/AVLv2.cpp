// Delete element
// Insert without recursion
// maxDepth
// get iter count for search

#include <iostream>
#include <windows.h>
#include <string>

#define LEFT	1
#define RIGHT	2
using namespace std;

struct node {
	int info;
	node *right, *left;
};

void gotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int whereX() {
	CONSOLE_SCREEN_BUFFER_INFO consoleinfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleinfo);
	return consoleinfo.dwCursorPosition.X;
}

int whereY() {
	CONSOLE_SCREEN_BUFFER_INFO consoleinfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleinfo);
	return consoleinfo.dwCursorPosition.Y;
}

class AVLTree {
public:
	node *root = NULL;
	bool debug = true;
	bool flag = false;
	bool doRotate = true;

	node* balance(node* tmp) {
		int balanceFactor = diff(tmp);
		if (balanceFactor > 1) {
			int childBF = diff(tmp->left);
			if (childBF > 0)	tmp = rightRotate(tmp);
			else				tmp = doubleRight(tmp);
		}
		else if (balanceFactor < -1) {
			int childBF = diff(tmp->right);
			if (childBF < 0)	tmp = leftRotate(tmp);
			else				tmp = doubleLeft(tmp);
		}
		return tmp;
	}

	node* insert(node *tmp, int d) {
		if (tmp == NULL) {
			tmp = new node;
			tmp->info = d;
			tmp->right = tmp->left = NULL;
			return tmp;
		}

		if (tmp->info < d) {
			tmp->right = insert(tmp->right, d);
			tmp = balance(tmp);
		}
		else if (tmp->info > d) {
			tmp->left = insert(tmp->left, d);
			tmp = balance(tmp);
		}
		else {
			log("Duplicate value.");
			return tmp;
		}
		return tmp;
	}

	int diff(node *tmp) {
		if (!tmp) return 0;
		return (1 + maxDepth(tmp->left)) - (1 + maxDepth(tmp->right));
	}

	node* leftRotate(node* tmp) {
		if (!tmp) return NULL;
		log("leftRotate\t" + to_string(tmp->info));
		node* tmp2 = tmp->right;
		tmp->right = tmp2->left;
		tmp2->left = tmp;
		return tmp2;
	}

	node* rightRotate(node* tmp) {
		if (!tmp) return NULL;
		log("rightRotate\t" + to_string(tmp->info));
		node* tmp2 = tmp->left;
		tmp->left = tmp2->right;
		tmp2->right = tmp;
		return tmp2;
	}

	node* doubleLeft(node* tmp) {
		if (!tmp) return NULL;
		log("doubleLeft\t" + to_string(tmp->info));
		tmp->right = rightRotate(tmp->right);
		tmp = leftRotate(tmp);
		return tmp;
	}

	node* doubleRight(node* tmp) {
		if (!tmp) return NULL;
		log("doubleRight\t" + to_string(tmp->info));
		tmp->left = leftRotate(tmp->left);
		tmp = rightRotate(tmp);
		return tmp;
	}

	node* search(int d) {
		node *tmp = root;
		while (tmp) {
			if (tmp->info < d) tmp = tmp->right;
			else if (tmp->info > d) tmp = tmp->left;
			else return tmp;
		}
		return NULL;
	}

	node* _remove(node *tmp, int d, node *parent = NULL, bool direction = NULL) {
		if (tmp == NULL) return NULL;
		else if (tmp->info < d || tmp->info > d) {
			if (tmp->info < d) {
				tmp->right = _remove(tmp->right, d, tmp, RIGHT);
			}
			else if (tmp->info > d) {
				tmp->left = _remove(tmp->left, d, tmp, LEFT);
			}
			if (doRotate) tmp = balance(tmp); // Case 4 a/b and 5 a/b is handled by balance
		}
		else {
			// Node found
			log("Value found.");
			int parentBF = diff(parent);
			if (tmp->right == tmp->left && tmp->left == NULL) {
				// No child
				log("Node with no child.");
				delete tmp;
				return NULL;
			}
			else if (tmp->right && !tmp->left) {
				// Right child
				log("Node with right child.");
				node* tmp2 = tmp->right;
				delete tmp;
				return tmp2;
			}
			else if (tmp->left && !tmp->right) {
				// Left child
				log("Node with left child.");
				node* tmp2 = tmp->left;
				delete tmp;
				return tmp2;
			}
			else {
				// Both child
				log("Node with both child.");
				node* tmp2 = getAncestor(tmp->right);
				log(tmp->info + "\t" + tmp2->info);
				tmp->info = tmp2->info;
				tmp->right = _remove(tmp->right, tmp->info);
				return tmp;
			}

			if (
				(parentBF == 0) ||    // Case 1 a/b
				(parentBF == 1 && direction == LEFT) ||  // Case 2a
				(parentBF == -1 && direction == RIGHT)   // Case 2b
			) {
				doRotate = false;
			}
		}
		return tmp;
	}

	node* remove(node *tmp, int d) {
		doRotate = true;
		tmp = _remove(tmp, d);
		doRotate = false;
		return tmp;
	}

	node* getAncestor(node* tmp) {
		if (tmp == NULL) return NULL;
		else if (tmp->left) tmp = getAncestor(tmp->left);
		return tmp;
	}

	void log(string msg) {
		if (debug) cout << msg << endl;
	}

	void print(node *n, int x = 40, int y = 0, int isRight = -1) {
		int tmpY = whereY();

		if (y == 0) y = tmpY;

		if (n == NULL)  {
			gotoXY(x, y);
			cout << "Empty";
			return;
		}

		if (isRight == 1) {
			gotoXY(x + 2, y - 1);
			cout << "/";
		}

		if (isRight == 0) {
			gotoXY(x - 2, y - 1);
			cout << "\\";
		}

		gotoXY(x, y);
		cout << n->info << endl;
		Sleep(100);

		if (n->left != NULL) {
			print(n->left, x - 5, y + 2, 1);
		}

		if (n->right != NULL) {
			print(n->right, x + 5, y + 2, 0);
		}

		gotoXY(0, tmpY + maxDepth(this->root) + 4);
	}

	int maxDepth(node *root) {
		if (root == NULL) return 0;
		int left = maxDepth(root->left);
		int right = maxDepth(root->right);
		return (left > right) ? left + 1 : right + 1;
	}

	void inOrder(node *root) {
		if (root == NULL) return;
		else {
			inOrder(root->left);
			cout << root->info << " ";
			inOrder(root->right);
		}
	}
};



int main() {
	AVLTree t;

	t.root = t.insert(t.root, 1);
	t.root = t.insert(t.root, 2);
	t.root = t.insert(t.root, 3);
	t.root = t.insert(t.root, 4);
	t.root = t.insert(t.root, 5);
	t.root = t.insert(t.root, 6);
	t.root = t.insert(t.root, 7);
	t.root = t.insert(t.root, 8);
	t.root = t.insert(t.root, 9);

	t.root = t.remove(t.root, 1);
	t.root = t.remove(t.root, 2);
	t.root = t.remove(t.root, 3);
	t.root = t.remove(t.root, 4);

	/*
	t.root = t.insert(t.root, 1);
	t.root = t.insert(t.root, 2);
	t.root = t.insert(t.root, 3);
	t.root = t.insert(t.root, 4);
	t.root = t.insert(t.root, 5);
	t.root = t.insert(t.root, 6);
	t.root = t.insert(t.root, 7);
	t.root = t.insert(t.root, 16);
	t.root = t.insert(t.root, 15);
	t.root = t.insert(t.root, 14);
	t.root = t.insert(t.root, 13);
	*/

	t.inOrder(t.root);
	cout << endl << endl;
	t.print(t.root, 40, 0);

	return 0;
}
