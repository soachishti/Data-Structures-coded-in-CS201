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

void MergeSort(int list[], int start, int end, int mid) {
	int size = end - start + 1;
	int *tmp = new int[size];
	int tmpIndex = 0;

	int left = start;
	int right = mid + 1;

	// Getting sorted data from 
	while(left <= mid && right <= end) {
		if (list[left] > list[right]) {		
			tmp[tmpIndex] = list[right];
            right++;
        }
		else {
			tmp[tmpIndex] = list[left];
            left++;
        }
        tmpIndex++;
	}

	// Dealing with remaing element in array
	while (left <= mid) 
		tmp[tmpIndex++] = list[left++];
	
	while (right <= end)
		tmp[tmpIndex++] = list[right++];
	
	// Putting sorted data into array
	for (int i = start, tmpIndex = 0; i <= end; i++, tmpIndex++) 
		list[i] = tmp[tmpIndex];
	
	delete[] tmp;
}

void MergeSortSplit(int list[], int start, int end) {
	if (start < end) {
		int mid = (end + start) / 2;        // 0+10 / 2 = 5
		MergeSortSplit(list, start, mid);   // Left     0-5 -> 0-2 | 3-5
		MergeSortSplit(list, mid + 1, end); // Right    6-10 -> (10+6)/2        6-8 | 9-10
   		//cout << start << "-" << mid << "\t\t" << mid+1 << "-" << end << endl;
		MergeSort(list, start, end, mid);
	}
}

int main() {
	const int size = 10;
	int list[size];
	fill(list, size);
	MergeSortSplit(list, 0, size-1);
	print(list, size);

	return 0;
}