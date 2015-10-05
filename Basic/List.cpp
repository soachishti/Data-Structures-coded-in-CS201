#include <iostream>
#include <cstdlib>

using namespace std;

class List {
public:
	int *data = NULL;
	int len = 0;
	int size = 0;
	int *current = NULL;

	List(int s) {
		size = s;
		data = new int[s]();
		current = data;
	}

	void swap(int *a, int *b) {
		int t = *a;
		*a = *b;
		*b = t;
	}

	void remove() {
		int *start = current;
		int *end = data + len - 1;
		while (start != end) {
			*start = *(start+1);
            start++;
		}
		*start = 0;

		if (current != data) {
			current--;
		}
        len--;
	}

	void add(int d) {
		if (len == size) {
			cout << "ERROR: Chadar ne jawab de diya!\n";
			return;
		}

		int *tmp = data + len;
		while (tmp != current) {
			if (tmp > current) 
				swap(tmp--, tmp);
			else
				swap(tmp++, tmp);
		}
		*tmp = d;

		len++;
		current++;
	}

	int _size() {
		return size;
	}

	int length() {
		return len;
	}

	int get(int p = -1) {
		if (p == -1) return *current;

		if (p < 0 && p >= size) {
			cout << "ERROR: Ye chadar ap ki nahi, Apni wali pe dehan dain, Shukriya!\n";
			return 0;
		}
		return *(data + p);
	}

	void update(int p, int d) {
		if (p < 0 && p >= size) {
			cout << "ERROR: Jitni chadar hai utne paon phelain, Shukriya!\n";
			return;
		}

		int *tmp = data + p;
		*tmp = d;
	}

	void print() {
		for (int i = 0; i < size; i++)  {
			if (data + i == current) cout << "*";
			cout << *(data + i) << endl;
		}
	}

	void start() {
		current = data;
	}

	void end() {
		current = data + size - 1;
	}

	void next() {
		if (current == (data + size - 1)) {
			cout << "ERROR: Ap chadar se bahir nikal jain ge, Atehat karye!\n";
			return;
		}
		current++;
	}

	void back() {
		if (current == data) {
			cout << "ERROR: Ap chadar se bahir nikal jain ge, Atehat karye!\n";
			return;
		}
		current--;
	}
};

int main() {
	List l(10);

	l.add(10);
	l.next();
	l.add(20);
	l.add(30);
	l.add(40);
	l.back();
	l.add(50);
	l.back();

	l.update(2,123);
	l.add(-1);
	l.add(-10);
	l.start();
	l.add(10000);
	l.remove();
	l.end();
	l.add(999);

    l.start();
    //l.remove();
	l.print();
	cout << "Value at 2nd index: " << l.get(2);

	cout << endl << "Length: " << l.length();
	cout << endl << "Size: " << l._size();

	system("pause");
}