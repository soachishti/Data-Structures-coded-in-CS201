#include <iostream>
#include <windows.h>
#include <string>
using namespace std;

struct node {
	int info;
	node *right, *left;
};


class BSTTree {
public:
	node *root = NULL;

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
			cout << ("Duplicate value.");
			return tmp;
		}
		return tmp;
	}

    void SumOfPath(node *tmp, int sum = 0) {
        if (tmp == NULL) return;
        sum += tmp->info;
        if (tmp->right == NULL && tmp->left == NULL) {
            cout << sum << endl;
            return;
        }
        SumOfPath(tmp->left, sum);
        SumOfPath(tmp->right, sum);
    }

};



int main() {
	BSTTree t;
	t.root = t.insert(t.root, 50);
	t.root = t.insert(t.root, 75);
	t.root = t.insert(t.root, 100);
	t.root = t.insert(t.root, 25);
	t.root = t.insert(t.root, 26);
	t.root = t.insert(t.root, 15);
	t.root = t.insert(t.root, 5);
	
    t.SumOfPath(t.root);
    
	return 0;
}
