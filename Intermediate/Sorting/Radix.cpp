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

void RadixSort(int list[], int size) {
	int *tmpList = new int[size];
	int divider = 10;
	int index = 0;
	int digit = 0;

	// Get max divider
	int maxDivider = 10;
	for (int i = 0; i < size; i++) {
		while ((list[i] / maxDivider) > 0) {
			maxDivider *= 10;
		}
	}

	// Radix Sort
	while (divider <= maxDivider) {
		for (int i = 0; i < size; i++) {
			// Get the specific  number
			int lsdNum = (list[i] % divider);
			if (divider > 10) lsdNum /= (divider / 10);

			if (lsdNum == digit) {
				// Insert number in temp
				tmpList[index] = list[i];
				index++;
			}
		}
		if (digit == 9) {
			// Copy to list
			for (int i = 0; i < size; i++) {
				list[i] = tmpList[i];
			}

			divider *= 10;
			digit = 0;
			index = 0;
		}
		else {
			digit++;
		}
	}
}

int main() {
	const int size = 10;
	int list[size]; 
	fill(list, size);
	RadixSort(list, size);
	print(list, size);

	return 0;
}