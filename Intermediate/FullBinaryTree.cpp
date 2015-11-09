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

class FullTree {
public:
	node *root = NULL;
	bool debug = true;

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

	node* insert(node *tmp) {
		if (tmp == NULL) {
			tmp = new node;
			cout << "Enter value: ";
			cin >> tmp->info;
			tmp->right = NULL;
			tmp->left = NULL;
		}
		else {
			tmp->left = insert(tmp->left);
			tmp->right = insert(tmp->right);
		}
		return tmp;
	}
};



int main() {
	FullTree t;
	t.root = t.insert(t.root);
	t.root = t.insert(t.root);
	t.root = t.insert(t.root);
	t.root = t.insert(t.root);

	cout << endl << endl;
	t.print(t.root, 40, 0);

	return 0;
}
