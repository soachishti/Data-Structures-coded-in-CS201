#include <iostream>
using namespace std;

struct node {
	int data;
	node *next;
};

struct Hash {
	int size;
	node **store;
	Hash(int s) {
		size = s;
		store = new node*[size];

		for (int i = 0; i < size; i++) {
			store[i] = NULL;
		}
	}

	void insert(int d) {
		int tmp = d%size;
		node *tmpNode = new node;
		tmpNode->data = d;
		tmpNode->next = NULL;
		if (store[tmp] == NULL) {
			store[tmp] = tmpNode;
		}
		else {
			node *tmpPos = store[tmp];
			while (tmpPos->next != NULL) {
				tmpPos = tmpPos->next;
			}
			tmpPos->next = tmpNode;
		}
	}

	void print() {
		cout << "\nPRINT ALL VALUES\n";
		for (int i = 0; i < size; i++) {
			node *tmp = store[i];
			while (tmp != NULL) {
				cout << tmp->data << "-";
				tmp = tmp->next;
			}
			cout << endl;
		}
	}

	bool search(int d) {
		for (int i = 0; i < size; i++) {
			node *tmp = store[i];
			while (tmp != NULL) {
				if (tmp->data == d) return true;
				tmp = tmp->next;
			}
		}
		return false;
	}

	bool remove(int d) {
		for (int i = 0; i < size; i++) {
			node *tmp = store[i];
			
			if (store[i]->data == d) {
				tmp = store[i];
				store[i] = store[i]->next;
				delete tmp;
				return true;
			}
			else {
				node *prev = tmp;
				tmp = tmp->next;
				while (tmp != NULL) {
					if (tmp->data == d) {
						prev->next = tmp->next;
						delete tmp;
						return true;
					}
					tmp = tmp->next;
				}
			}
		}
		return false;
	}

};

int main() {
	Hash h(5);

	h.insert(0);
	h.insert(1);
	h.insert(2);
	h.insert(3);
	h.insert(4);
	h.insert(5);
	h.insert(6);
	h.insert(7);
	h.insert(5);
	h.insert(5);
	h.insert(5);

	cout << h.remove(5) << endl; // Return true if node deleted

	h.print();
	return 0;
}