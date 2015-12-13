#include <iostream>
#include <math.h>
#include <algorithm>
#include <ctime>
using namespace std;

void fill(int list[], int size) {
	srand(time(NULL));
	for (int i = 0; i < size; i++) {
		list[i] = rand() % 100 + 10;
	}
}

void print(int list[], int size) {
	for (int i = 0; i < size; i++) {
		cout << list[i] << " ";
	}
	cout << endl;
}

void swap(int &val1, int &val2) {
	int tmp = val1;
	val1 = val2;
	val2 = tmp;
}

void BubbleSort(int list[], int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 1; j < size - i; j++) {
			if (list[j - 1] > list[j])
				swap(list[j - 1], list[j]);
		}
	}
}

int main() {
	const int size = 10;
	int list[size];
	fill(list, size);
    BubbleSort(list, size);
	print(list, size);

	return 0;
}