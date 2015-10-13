// Delete element
// Insert without recursion
// maxDepth
// get iter count for search

#include <iostream>
#include <windows.h>
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

class Tree {
private:
	node *root = NULL;
public:
	node *rootNode() {
		return root;
	}

	bool search(node *root, int d) {
		if (root == NULL) return 0;
		if (root->info == d) {
			return 1;
		}
		else {
			if (root->info > d) {
				return search(root->right, d);
			}
			else {
				return search(root->left, d);
			}
		}
	}

	void insert(node *root, int d) {
		if (root == NULL) {
			this->root = new node;
			this->root->info = d;
			this->root->right = NULL;
			this->root->left = NULL;
			return;
		}

		if (root->info > d) {
			if (root->right == NULL) {
				root->right = new node;
				root->right->info = d;
				root->right->right = NULL;
				root->right->left = NULL;
				return;
			}
			else
				insert(root->right, d);
		}

		if (root->info < d) {
			if (root->left == NULL) {
				root->left = new node;
				root->left->info = d;
				root->left->right = NULL;
				root->left->left = NULL;
				return;
			}
			else
				insert(root->left, d);
		}

		if (root->info == d) {
			cout << "Duplicate value found" << endl;
		}
	}

	void destroy(node *root) {
		if (root == NULL)
			return;
		else {
			if (root->right != NULL) {
				destroy(root->right);
				delete root->right;
				root->right = NULL;
			}

			if (root->left != NULL) {
				destroy(root->left);
				delete root->left;
				root->left = NULL;
			}
		}

		if (root == this->root) {
			delete this->root;
			this->root = NULL;
		}
	}

	void remove(node *root, int d, node *parent = NULL) {
		if (root == NULL) return;

		if (root->info == d) {

		}

		if (root->info < d) {
			remove(root->left, d, parent);
		}

		if (root->info > d) {
			remove(root->right, d, parent);
		}
	}


	void print(node *n, int x = 40, int y = 0, int isRight = -1) {
		if (n == NULL) return;
		
		if (isRight == 1) {
			gotoXY(x + 2, y-1);
			cout << "/";
		}

		if (isRight == 0) {
			gotoXY(x - 2, y-1);
			cout << "\\";
		}
		
		gotoXY(x, y);
		cout << n->info << endl;

		if (n->right != NULL) {
			print(n->right, x-5, y+2, 1);
		}
		
		if (n->left != NULL) {
			print(n->left, x+5, y+2, 0);
		}

	}
};



int main() {
	Tree t;
	t.insert(t.rootNode(), 10);
	t.insert(t.rootNode(), 5);
	t.insert(t.rootNode(), 9);
	t.insert(t.rootNode(), 3);
	t.insert(t.rootNode(), 15);
	t.insert(t.rootNode(), 30);
	t.insert(t.rootNode(), 40);

	
	cout << t.search(t.rootNode(), 10) << endl;
	cout << t.search(t.rootNode(), 1) << endl;
	cout << t.search(t.rootNode(), 2) << endl;
	cout << t.search(t.rootNode(), 15) << endl;
	


	t.print(t.rootNode(), 40, whereY());

	cout << "Destorying" << endl;
	t.destroy(t.rootNode());
	
	t.print(t.rootNode(), 40, whereY());
	cout << endl << endl << endl << endl;
	return 0;
}