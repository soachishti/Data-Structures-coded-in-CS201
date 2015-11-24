#include <iostream>
using namespace std;

class Heap {
public:
	int *store, size;
	int *position = NULL;
	Heap(int s) {
		size = s;
		store = new int[s];
	}

	void swap(int *a, int *b) {
		int tmp = *a;
		*a = *b;
		*b = tmp;
	}

	void insert(int data) {
		if (position == NULL) {
			*(position = store) = data;
		} 
		else {
			*(++position) = data;
		}	

		int index = position - store + 1;
		int i = index;
		while (i > 1) {
			int prevIndex = floor(i / 2.0) - 1;
			if (data < *(store + prevIndex)) {
				swap(store + index - 1  , store + prevIndex);
			}
			index = i = prevIndex + 1;
		}
	}

	int pop() {
		int tmp = *store;
		//for (int *i = store; i <= position; i++) {
		//	swap(i, i + 1);
		//}
		//position--;
		return tmp;
	}

	void print() {
		cout << endl << endl;
		for (int *i = store; i <= position; i++) {
			cout << *i << " ";
		}
	}
};
int main() {
	Heap h(256);
	
	h.insert(30);
	h.insert(20);
	
	h.insert(10);
	h.insert(5);
	h.insert(1);
	h.insert(35);
	//h.insert(15);
	//h.insert(5);
	//h.insert(50);
	//h.insert(60);
	//h.pop();
	//h.pop();
	h.print();
}