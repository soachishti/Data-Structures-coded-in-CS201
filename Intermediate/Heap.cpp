//http://www.sanfoundry.com/cpp-program-implement-binary-heap/

#include <iostream>
using namespace std;

class Heap {
public:
	int *store, size;
	int position = 0;
	bool debug = true
    ;
	Heap(int s) {
		size = s;
		store = new int[s];
		store[0] = 0;
	}

	void swap(int &a, int &b) {
		int tmp = a;
		a = b;
		b = tmp;
	}

	void insert(int data) {
		if (position <= size) {
			position++;
			store[position] = data;
			heapifyUp(position);
		}
	}

	void heapifyUp(int pos) {
		int tmp = pos;
		while (tmp > 1) {
			int parent = tmp / 2;
			if (store[parent] > store[tmp]) {
				swap(store[parent], store[tmp]);
			}
			tmp = parent;
		}
	}

	void print() {
		//cout << position << endl;
		for (int i = 1; i <= position; i++) {
			cout << i << ") " << store[i] << endl;
		}
	}    
    
	void heapifyRoot() {
		int tmp = 1;
		while (tmp <= position) {
			int childLeft = tmp * 2;
			int childRight = (tmp * 2) + 1;
            //cout << tmp << childLeft << " " << childRight << " " << position << endl;

            if (childRight >= position) {
				store[tmp] = store[position];
				heapifyUp(tmp);
				break;
			}
			if (store[tmp] > store[childLeft] && store[childLeft] <= store[childRight]) {
                swap(store[childLeft], store[tmp]);
                tmp = childLeft;
            }
            else if (store[tmp] > store[childRight] && store[childRight] <= store[childLeft]) {
                swap(store[childRight], store[tmp]);
                tmp = childRight;
			}
            else {
                cout << "Not possible\n";
                break;
            }
		}
		position--;
	}

	int pop() {
		if (position == 0) {
			cout << "Queue Empty";
			return -1;
		}
		int tmp = store[1];
		store[1] = 999999;
		heapifyRoot();
		return tmp;
	}
};
int main() {
	Heap h(256);
	h.insert(9);
	h.insert(5);
	h.insert(4);
	h.insert(2);
	h.insert(1);
	h.insert(3);
	h.insert(8);
	h.insert(9);
	h.insert(-1);
	h.insert(0);
	h.insert(-2);
    
    cout << "Min: " << h.pop() << endl;
    cout << "Min: " << h.pop() << endl;
    cout << "Min: " << h.pop() << endl;
    cout << "Min: " << h.pop() << endl;
    cout << "Min: " << h.pop() << endl;
    cout << "Min: " << h.pop() << endl;
    cout << "Min: " << h.pop() << endl;
    cout << "Min: " << h.pop() << endl;
    cout << "Min: " << h.pop() << endl;
    cout << "Min: " << h.pop() << endl;
    cout << "Min: " << h.pop() << endl;
    
    
    return 0;
   	h.print();
}