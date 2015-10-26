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

class AVLTree {
private:
	node *root = NULL;
	bool debug = true;
public:
	bool flag = false;

	void log(string msg) {
		if (debug) cout << msg << endl;
	}

	node *rootNode() {
		return root;
	}

	int diff(node *root) {
		if (root == NULL) return 0;
		int left = maxDepth(root->left);
		int right = maxDepth(root->right);
		int result = left - right;
		return result;
	}

	void balance(node *tmp, node* prev) {
		int result = diff(tmp);

		log("BF: " + to_string(result) + "\tInfo: " + to_string(tmp->info));

		if (result < -1) {
			int direction = diff(tmp->right);
			log("BF: " + to_string(direction));
			if (direction < 0)
				rotateLeft(tmp, prev);
			else
				rotateLeftRight(tmp, prev);
		}
		if (result > 1) {
			int direction = diff(tmp->left);
			log("BF: " + to_string(direction));
			if (direction > 0)
				rotateRight(tmp, prev);
			else
				rotateRightLeft(tmp, prev);
		}
	}

	void insert(node *root, int d, node* prev = NULL) {
		if (prev == NULL) {
			log("Adding " + to_string(d));
			flag = false;
		}

		if (root == NULL) {
			this->root = new node;
			this->root->info = d;
			this->root->right = NULL;
			this->root->left = NULL;
		}
		else
		{
			if (d > root->info) {
				if (root->right == NULL) {
					root->right = new node;
					root->right->info = d;
					root->right->right = NULL;
					root->right->left = NULL;
				}
				else {
					insert(root->right, d, root);
					balance(root, prev);
				}
			}
			else if (d < root->info) {
				if (root->left == NULL) {
					root->left = new node;
					root->left->info = d;
					root->left->right = NULL;
					root->left->left = NULL;
				}
				else {
					insert(root->left, d, root);
					balance(root, prev);
				}
			}
			else {
				log("Duplicate value found");
			}
		}
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

	node* rotateRight(node *victim, node *prev, bool setRoot = true) {
		log("rotateRight");
		node *next = victim->left;
		victim->left = next->right;
		next->right = victim;

		if (prev) prev->left = next;
		else {
			if (setRoot) root = next;
			else return next;
		}
	}

	node* rotateLeft(node *victim, node *prev, bool setRoot = true) {
		log("rotateLeft");
		node *next = victim->right;
		victim->right = next->left;
		next->left = victim;
		
		if (prev) prev->right = next;
		else {
			if (setRoot) root = next;
			else return next;
		}
	}

	void rotateLeftRight(node *root, node* prev) {
		log("rotateLeftRight");

		root->right = rotateRight(root->right, NULL, false);
		rotateLeft(root, prev);
	}

	void rotateRightLeft(node *root, node* prev) {
		log("rotateRightLeft");
		root->left = rotateLeft(root->left, NULL, false);
		rotateRight(root, prev);
	}

	int maxDepthDirection(node *root) {
		if (root == NULL) return 0;
		int left = maxDepth(root->left);
		int right = maxDepth(root->right);
		return (left > right) ? LEFT : RIGHT;
	}

	int maxDepth(node *root) {
		if (root == NULL) return 0;
		int left = maxDepth(root->left);
		int right = maxDepth(root->right);
		return (left > right) ? left + 1 : right + 1;
	}

	void inOrder(node *root) {
		if (root == NULL) {
			cout << "Empty";
		}
		else {
			if (root->left) inOrder(root->left);
			cout << root->info << " ";
			if (root->right) inOrder(root->right);
		}
	}

	void remove(node *root, int d) {
		if (root == NULL) return;

		if (root->info == d) {
			// If have both children
			if (root->right != NULL && root->left != NULL) {
				// search smallest
				log("Deleting element with both children.");

				node *tmp = root->right;
				node *prev = root;
				while (tmp->left != NULL) {
					prev = tmp;
					tmp = tmp->left;
				}
				log("Descendent = " + tmp->info);

				if (tmp->right != NULL) {
					log("Have right element.");
					root->info = tmp->info;
					tmp->info = tmp->right->info;

					node *tmp2 = tmp->right;
					tmp->right = tmp->right->right;

					delete tmp2;
				}
				else {
					log("No right element.");
					root->info = tmp->info;
					delete prev->left;
					prev->left = NULL;
				}
			}
			else if (root->right == NULL && root->left != NULL) {
				if (this->root == root) {
					log("Setting flag to delete root with only left child.");
					node *tmp = root;
					this->root = root->left;
					delete tmp;
				}
				else {
					log("Setting flag to delete element with only left child.");
					flag = true;
				}
			}
			else if (root->right != NULL && root->left == NULL) {
				if (this->root == root) {
					log("Deleting root with only right child.");
					node *tmp = root;
					this->root = root->right;
					delete tmp;
				}
				else {
					log("Setting flag to delete element with only right child.");
					flag = true;
				}
			}
			else {
				if (this->root == root) {
					log("Deleting root with no child.");
					delete this->root;
					this->root = NULL;
				}
				else {
					log("Flag set for deletion.");
					flag = true;
				}
			}
			return;
		}

		if (d < root->info) {
			log("Going left.");
			remove(root->left, d);
			if (flag == true) {
				log("Deleting left element.");
				node *tmp = root->left;
				root->left = root->left->left;
				delete tmp;
				flag = false;
			}
		}

		if (d > root->info) {
			log("Going right.");
			remove(root->right, d);
			if (flag == true) {
				log("Deleting right element.");
				node *tmp = root->right;
				root->right = root->right->right;
				delete tmp;
				flag = false;
			}
		}


		return;
	}

};



int main() {
	AVLTree t;
	/*
	// Rotate Left and right
	t.insert(t.rootNode(), 3);
	t.insert(t.rootNode(), 2);
	t.insert(t.rootNode(), 1);
	t.insert(t.rootNode(), 4);
	t.insert(t.rootNode(), 5);
	*/

	/*
	// Rotate left and left
	t.insert(t.rootNode(), 1);
	t.insert(t.rootNode(), 2);
	t.insert(t.rootNode(), 3);
	t.insert(t.rootNode(), 4);
	t.insert(t.rootNode(), 5);
	*/

	/*
	// Left left left left
	t.insert(t.rootNode(), 1);
	t.insert(t.rootNode(), 2);
	t.insert(t.rootNode(), 3);
	t.insert(t.rootNode(), 4);
	t.insert(t.rootNode(), 5);
	t.insert(t.rootNode(), 6);
	t.insert(t.rootNode(), 7);
	*/

	/*
	// Rotate Double Left 
	t.insert(t.rootNode(), 1);
	t.insert(t.rootNode(), 3);
	t.insert(t.rootNode(), 2);
	*/

	/*
	// Rotate Double Right
	t.insert(t.rootNode(), 3);
	t.insert(t.rootNode(), 1);
	t.insert(t.rootNode(), 2);
	*/


	/*
	// Sir slides input
	t.insert(t.rootNode(), 1);
	t.insert(t.rootNode(), 2);
	t.insert(t.rootNode(), 3);
	t.insert(t.rootNode(), 4);
	t.insert(t.rootNode(), 5);
	t.insert(t.rootNode(), 6);
	t.insert(t.rootNode(), 7);
	t.insert(t.rootNode(), 16);
	t.insert(t.rootNode(), 15);
	t.insert(t.rootNode(), 14);
	t.insert(t.rootNode(), 13);
	*/


	///*
	// Playing inputs
	t.insert(t.rootNode(), 1);
	t.insert(t.rootNode(), 2);
	t.insert(t.rootNode(), 3);
	t.insert(t.rootNode(), 4);
	t.insert(t.rootNode(), 5);
	t.insert(t.rootNode(), 6);
	t.insert(t.rootNode(), 7);
	t.insert(t.rootNode(), 16);
	t.insert(t.rootNode(), 15);
	t.insert(t.rootNode(), 14);
	t.insert(t.rootNode(), 13);
	//*/

	t.inOrder(t.rootNode());
	cout << endl << endl;    
	t.print(t.rootNode(), 40, 0);


	// Deleteing headache to start
	t.remove(t.rootNode(), 1);
	return 0;
}
