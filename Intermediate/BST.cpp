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

struct LinkedListNode{
	int id, count;
	LinkedListNode *next;
};

class Tree {
private:
	node *root = NULL;
	bool flag = false;
	LinkedListNode *dupCount = NULL;
	bool debug = true;
public:
	void log(const char *msg) {
		if (debug) cout << msg << endl;
	}

	node *rootNode() {
		return root;
	}

	bool search(node *root, int d) {
		if (root == NULL) return 0;
		if (root->info == d) {
			return 1;
		}
		else {
			if (d > root->info) 
				return search(root->right, d);
			
			if (d < root->info) 
				return search(root->left, d);
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

		if (d > root->info) {
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

		if (d < root->info) {
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
			LinkedListNode *tmp;
			if (dupCount == NULL) {
				tmp = new LinkedListNode;
				tmp->id = root->info;
				tmp->count = 1;
				tmp->next = NULL;
				dupCount = tmp;
			}
			else {
				tmp = dupCount;
				while (tmp != NULL) {
					if (tmp->id == root->info) break;
					tmp = tmp->next;
				}

				if (tmp == NULL) {
					tmp = new LinkedListNode;
					tmp->id = root->info;
					tmp->count = 1;
					tmp->next = dupCount;
					dupCount = tmp;
				}
				else {
					tmp->count++;
				}
			}


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

	node* get_decender(node *root) {
		if (root->left == NULL || root->right == NULL) return root;
		if (root->left != NULL) return get_decender(root->left);
		if (root->right != NULL) return get_decender(root->right);
	}

	void remove(node *root, int d) {
		if (root == NULL) return;

		if (root->info == d) {
			delDuplicateInfo(d); // Delete duplicate info as well.

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

	void print(node *n, int x = 40, int y = 0, int isRight = -1) {
		int tmpY = whereY();

		if (n == NULL)  {
			gotoXY(x, y);
			cout << "Empty";
			return;
		}

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

		if (n->left != NULL) {
			print(n->left, x-5, y+2, 1);
		}
		
		if (n->right != NULL) {
			print(n->right, x+5, y+2, 0);
		}

		gotoXY(0, tmpY + maxDepth(this->root) + 4);

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

	void preOrder(node *root) {
		if (root == NULL) {
			cout << "Empty";
		}
		else {
			cout << root->info << " ";
			if (root->left) inOrder(root->left);
			if (root->right) inOrder(root->right);
		}
	}

	void postOrder(node *root) {
		if (root == NULL) {
			cout << "Empty";
		}
		else {
			if (root->left) postOrder(root->left);
			if (root->right) postOrder(root->right);
			cout << root->info << " ";
		}
	}

	void descendingOrder(node *root) {
		if (root == NULL) {
			cout << "Empty";
		}
		else {
			if (root->right) descendingOrder(root->right);
			cout << root->info << " ";		
			if (root->left) descendingOrder(root->left);
		}
	}

	int minDepth(node *root) {
		if (root == NULL) return 0;
		int left = minDepth(root->left);
		int right = minDepth(root->right);
		return (left < right) ? left + 1 : right + 1;
	}

	int maxDepth(node *root) {
		if (root == NULL) return 0;
		int left = maxDepth(root->left);
		int right = maxDepth(root->right);
		return (left > right) ? left + 1  : right + 1 ;
	}

	int nodeCount(node *root) {
		if (root == NULL) 
			return 0;
		else
			return 1 + nodeCount(root->right) + nodeCount(root->left);
	}

	void delDuplicateInfo(int key) {
		LinkedListNode *tmp = dupCount;
		LinkedListNode *prev = NULL;
		while (tmp != NULL) {
			if (tmp->id == key) {
				if (prev == NULL) {
					//is head
					tmp = dupCount->next;
					delete dupCount;
					dupCount = tmp;
				}
				else {
					prev->next = tmp->next;
					delete tmp;
				}
				return;
			}
			prev = tmp;
			tmp = tmp->next;
		}
	}

	void duplicateList() {
		LinkedListNode *tmp = dupCount;
		cout << "INFO\tCOUNT" << endl;
		while (tmp != NULL) {
			cout << tmp->id << "\t" << tmp->count << endl;
			tmp = tmp->next;
		}
	}
};



int main() {
	Tree t;
	// Sir Input Data
	t.insert(t.rootNode(), 14);
	t.insert(t.rootNode(), 15);
	t.insert(t.rootNode(), 4);
	t.insert(t.rootNode(), 9);
	t.insert(t.rootNode(), 7);
	t.insert(t.rootNode(), 18);
	t.insert(t.rootNode(), 3);
	t.insert(t.rootNode(), 5);
	t.insert(t.rootNode(), 16);
	t.insert(t.rootNode(), 4);
	t.insert(t.rootNode(), 20);
	t.insert(t.rootNode(), 17);
	t.insert(t.rootNode(), 9);
	t.insert(t.rootNode(), 14);
	t.insert(t.rootNode(), 5);
	t.insert(t.rootNode(), 50);
	t.insert(t.rootNode(), 60);
	t.insert(t.rootNode(), 60);
	t.insert(t.rootNode(), 60);
	t.insert(t.rootNode(), 60);
	t.insert(t.rootNode(), 1);
	t.insert(t.rootNode(), 1);
	t.insert(t.rootNode(), 1);
	t.insert(t.rootNode(), 1);
	t.insert(t.rootNode(), 1);
	t.insert(t.rootNode(), 1);
	t.insert(t.rootNode(), 1);

	//t.remove(t.rootNode(), 1); // if we remove element with duplicate element then their duplicate info is also deleted

	t.print(t.rootNode(), 40, whereY());
	//cout << endl << endl << endl;

	t.duplicateList();

	// cout << endl << endl;
	// cout << t.maxDepth(t.rootNode()) << endl;
	// cout << t.minDepth(t.rootNode()) << endl;
	// cout << t.nodeCount(t.rootNode()) << endl;

	return 0;

	t.inOrder(t.rootNode());
	cout << endl;
	t.preOrder(t.rootNode());
	cout << endl;
	t.postOrder(t.rootNode());
	cout << endl;
	t.descendingOrder(t.rootNode());

	return 0;
	
	t.insert(t.rootNode(), 10);
	t.insert(t.rootNode(), 5);
	t.insert(t.rootNode(), 9);
	t.insert(t.rootNode(), 3);
	t.insert(t.rootNode(), 15);
	t.insert(t.rootNode(), 30);
	t.insert(t.rootNode(), 40);
	t.insert(t.rootNode(), 1);

	//node *tmp = t.get_decender(t.rootNode()->right);
	//cout << tmp->info;



	//cout << t.search(t.rootNode(), 10) << endl;
	//cout << t.search(t.rootNode(), 1) << endl;
	//cout << t.search(t.rootNode(), 2) << endl;
	//cout << t.search(t.rootNode(), 15) << endl;
	t.print(t.rootNode(), 40, whereY());


	//t.remove(t.rootNode(), 40);
	//t.remove(t.rootNode(), 10);
	//t.remove(t.rootNode(), 9);
	//t.remove(t.rootNode(), 30);
	t.remove(t.rootNode(), 30);
	t.remove(t.rootNode(), 15);
	t.remove(t.rootNode(), 5);
	t.remove(t.rootNode(), 9);
	t.remove(t.rootNode(), 10);		// Error // Root with only on child
	t.remove(t.rootNode(), 40);
	t.remove(t.rootNode(), 10);


	cout << endl << endl << endl << endl;
	t.print(t.rootNode(), 40, whereY());

	//cout << "Destorying" << endl;
	//t.destroy(t.rootNode());
	//t.print(t.rootNode(), 40, whereY());


	cout << endl << endl << endl << endl;
	return 0;
}
 
