#include <iostream>
using namespace std;

struct Hash {
	int size;
	int *store;
	Hash(int s) {
		size = s;
		store = new int[size];
	
		//Fill with -1
		for (int i = 0; i < size; i++) {
			store[i] = -1;
		}
	}

	void insert(int d) {
		int tmp = d%size;
		while (store[tmp] != -1 && tmp < size) {
			tmp++;
		}
		if (tmp == size) {
			tmp = 0;
			// Search again from starting
			while (store[tmp] != -1 && tmp < size) {
				tmp++;
			}
			if (tmp == size) {
				cout << "Error: Store full." << endl;
				return;
			}
		}
		store[tmp] = d;
	}

	void print() {
		cout << "\nPRINT ALL VALUES\n";
		for (int i = 0; i < size; i++) {
			cout << store[i] << endl;
		}
		cout << endl;
	}


	bool search(int d) {
		int tmp = d%size;
		if (store[tmp] == -1) return false;

		while (store[tmp] != -1 && tmp < size) {
			if (store[tmp] == d) {
				return true;
			}
			tmp++;
		}
		if (tmp == size) {
			tmp = 0;
			// Search again from starting
			while (store[tmp] != -1 && tmp < size) {
				if (store[tmp] == d) {
					return true;
				}
				tmp++;
			}
			if (tmp == size) {
				return false;
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
	
	
	/*
	h.insert(1);
	h.insert(1);
	h.insert(1);
	h.insert(1);
	h.insert(1);
	h.insert(1);
	*/

	h.print();
	return 0;
}