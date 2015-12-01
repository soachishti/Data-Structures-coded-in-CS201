#include <iostream>
#include <math.h>
#include <algorithm>
#include <ctime>
using namespace std;

struct Bucket {
	int data;
	Bucket *next = NULL;
};

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

void InsertionSort(int list[], int size) {
	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			if (list[i] > list[j]) swap(list[i], list[j]);
		}
	}
}

void BubbleSort(int list[], int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 1; j < size - i; j++) {
			if (list[j - 1] > list[j])
				swap(list[j - 1], list[j]);
		}
	}
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

void BucketSort(int list[], int size) {
	int *tempList = new int[size];

	Bucket **bucket = new Bucket*[size];
	for (int i = 0; i < size; i++) {
		bucket[i] = NULL;
	}

	// Get max divider
	int maxDivider = 10;
	for (int i = 0; i < size; i++) {
		while ((list[i] / maxDivider) > 0) {
			maxDivider *= 10;
		}
	}
	for (int i = 0; i < size; i++) {
		for (int digit = 0; digit < 10; digit++) {	
			int msb = list[i] % maxDivider;
			if (maxDivider > 10)
				msb /= (maxDivider / 10);

			if (msb == digit) {
				Bucket *tmp = bucket[digit];
				Bucket *prev = tmp;
				while (true) {
					if (tmp == NULL) {
						bucket[digit] = new Bucket;
						bucket[digit]->data = list[i];
						bucket[digit]->next = NULL;
						//cout << "#1 " << digit << " ";
						break;
					}
					else if (list[i] <= tmp->data) {
						if (tmp == bucket[digit]) {
							bucket[digit] = new Bucket;
							bucket[digit]->data = list[i];
							bucket[digit]->next = tmp;
							//cout << "#2a " << digit << " ";
						}
						else {
							//cout << "#2b " << digit << " ";
							prev->next = new Bucket;
							prev->next->data = list[i];
							prev->next->next = tmp;
						}
						
						break;
					}
					else if (tmp->next == NULL) {
						tmp->next = new Bucket;
						tmp->next->data = list[i];
						tmp->next->next = NULL;
						//cout << "#3  " << digit << " ";
						break;
					}
					else {
						prev = tmp;
						tmp = tmp->next;
					}
				} // Infinite loop
				//cout << list[i] << endl;
				break;
			} // Digit found
		} // digit find
	} // Digit loop

	// Print
	int index = 0;
	for (int i = 0; i < size; i++) {
		Bucket *tmp = bucket[i];
		cout << i << ") ";
		while (true) {
			if (tmp != NULL) {
				list[index] = tmp->data;
				index++;
				cout << tmp->data << " - ";
				// Bucket *tmp1 = tmp;
				tmp = tmp->next;
				// delete tmp1;
				
			}
			else {
				cout << endl;
				break;
			}
		}
	}
}

int main() {
	const int size = 10;
	//int list[size];// = { 50, 63, 33, 106, 44, 48, 100, 11, 11, 71 };
	int list[size]; // = { 10, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	fill(list, size);
	//InsertionSort(list, size);
	//BubbleSort(list, size);

	//print(list, size);
	//RadixSort(list, size);
	print(list, size);
	BucketSort(list, size);

	print(list, size);

	return 0;
}