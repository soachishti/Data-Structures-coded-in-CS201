#include <iostream>
#include <windows.h>
#include <string>

#define	LEFT	1
#define	RIGHT	1
#define THREAD	1
#define CHILD	2
#define MAX_VALUE	65000
using namespace std;

struct node {
	int info;
	node *right, *left;
	char lth, rth;
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

class ThreadedBinaryTree {
public:
	node *root = NULL;
	bool debug = true;
	node *dummy = NULL;
	node *tmpGlobal = NULL;

	ThreadedBinaryTree() {
		dummy = new node;
		dummy->right = dummy;
		dummy->rth = CHILD;
		dummy->lth = THREAD;
		dummy->left = dummy;
		dummy->info = 65000;
	}

	void log(string msg) {
		if (debug) cout << msg << endl;
	}

	void insert(int data) {
		tmpGlobal = dummy;
		while (true) {
			if (tmpGlobal->info > data) {
				log("Search in left");
				if (tmpGlobal->lth == THREAD) break;
				else tmpGlobal = tmpGlobal->left;
			}
			else if (tmpGlobal->info < data) {
				log("Search in right");
				if (tmpGlobal->rth == THREAD) break;
				else tmpGlobal = tmpGlobal->right;
			}
			else {
				log("Duplicate Value");
				return;
			}
		}

		node *tmp = new node;
		tmp->info = data;
		tmp->rth = tmp->lth = THREAD;
		if (tmpGlobal->info < data) {
			log("Adding in right");
			tmp->left = tmpGlobal;
			tmp->lth = THREAD;
			tmp->right = tmpGlobal->right;
			tmp->rth = THREAD;
			tmpGlobal->right = tmp;
			tmpGlobal->rth = CHILD;
		}
		else if (tmpGlobal->info > data) {
			log("Adding in left");
			tmp->right = tmpGlobal;
			tmp->rth = THREAD;
			tmp->left = tmpGlobal->left;
			tmp->lth = THREAD;
			tmpGlobal->left = tmp;
			tmpGlobal->lth = CHILD;
		}
	}


	node* nextPreorder(node* p)
	{
		if (p->lth == THREAD) return(p->left);
		else {
			p = p->left;
			while (p->rth == CHILD)
				p = p->right;
			return p;
		}
	}

	void fastPreorder(node* p)
	{
		while ((p = nextPreorder(p)) != dummy)
			cout << p->info << endl;
		cout << endl;
		Sleep(100);

	}

	node* nextInorder(node* p)
	{
		if (p->rth == THREAD) return(p->right);
		else {
			p = p->right;
			while (p->lth == CHILD)
				p = p->left;
			return p;
		}
	}

	void fastInorder(node* p)
	{
		while ((p = nextInorder(p)) != dummy)
			cout << p->info << endl;
		cout << endl;
		Sleep(100);
		
	}
};



int main() {
	ThreadedBinaryTree t;
	t.debug = false;
	t.insert(10);
	t.insert(20);
	t.insert(30);

	// t.fastInorder(t.dummy);
	t.fastPreorder(t.dummy);

	return 0;
}
