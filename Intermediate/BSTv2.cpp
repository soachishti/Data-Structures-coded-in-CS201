// Delete element
// Insert without recursion
// maxDepth
// get iter count for search

#include <iostream>
#include <windows.h>
#include <string>

#define LEFT	0
#define RIGHT	1
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

class BSTTree {
public:
	node *root = NULL;
	bool debug = true;

	node* insert(node *tmp, int d) {
		if (tmp == NULL) {
			tmp = new node;
			tmp->info = d;
			tmp->right = tmp->left = NULL;
			return tmp;
		}

		if (tmp->info < d) {
			tmp->right = insert(tmp->right, d);
		}
		else if (tmp->info > d) {
			tmp->left = insert(tmp->left, d);
		}
		else {
			log("Duplicate value.");
			return tmp;
		}
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

	node* remove(node *tmp, int d) {
		if (tmp == NULL) return NULL;
		else if (tmp->info < d) tmp->right = remove(tmp->right, d);
		else if (tmp->info > d) tmp->left = remove(tmp->left, d);
		else {
			// Node found
			log("Value found."); 
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
				tmp->right = remove(tmp->right, tmp->info);
				return tmp;
			}
		}
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
	BSTTree t;

	t.root = t.insert(t.root, 20);
	t.root = t.insert(t.root, 10);
	t.root = t.insert(t.root, 30);
	t.root = t.insert(t.root, 5);
	t.root = t.insert(t.root, 25);
	t.root = t.insert(t.root, 27);
	t.root = t.insert(t.root, 40);
	t.root = t.insert(t.root, 100);

	cout << t.search(100) << endl;
	cout << t.search(0) << endl;
	cout << t.search(1) << endl;
	cout << t.search(5) << endl;
	cout << t.search(40) << endl;

	
	t.remove(t.root, 5);
	t.remove(t.root, 20);
	t.remove(t.root, 10);
	//t.remove(t.root, 27);
	t.remove(t.root, 30);

	t.inOrder(t.root);
	cout << endl << endl;
	t.print(t.root, 40, 0);

	return 0;
}
