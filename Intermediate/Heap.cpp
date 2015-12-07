#include <iostream>
using namespace std;

class Heap {
public:
	int *store, size;
	int position = 0;
    bool debug = false;
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
        while(tmp > 1) {
            int parent = tmp/2;
            if (store[parent] > store[tmp]) {
                swap(store[parent], store[tmp]);
            }
            tmp = parent;
        }
    }
    
    void heapifyRoot() {
        int tmp = 1;
        while(tmp < position) {           
            int childLeft = tmp * 2;
            int childRight = (tmp * 2) + 1;            
            if (childLeft > position) {
                store[tmp] = store[position];
                heapifyUp(tmp);
                break;
            }           
            if (store[childLeft] < store[tmp]) {
                swap(store[childLeft], store[tmp]);
            }
            if (store[childRight] < store[tmp]) {
                swap(store[childRight], store[tmp]);
            }
            tmp = childLeft;           
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

	void print() {
        //cout << position << endl;
		cout << endl << endl;
		for (int i = 0; i <= position; i++) {
			cout << i << ") " << store[i] << endl;
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
	//h.insert(35);
	//h.insert(15);
	//h.insert(2);
	//h.insert(5);
	//h.insert(50);
	//h.insert(60);
	//h.pop();
    
    h.debug = true;

	h.pop();
	h.pop();
	h.pop();
	h.pop();
	h.pop();
	h.pop();
    
    h.insert(10);
    h.insert(20);
    h.insert(5);
    h.insert(1);
    h.insert(0);
    
    	h.pop();
	h.pop();
	h.pop();
	h.pop();
    
	h.print();
}