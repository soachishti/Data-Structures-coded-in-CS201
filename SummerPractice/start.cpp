#include <iostream>
using namespace std;

void swap(int &a, int &b) {
    int t;
    t = a;
    a = b;
    b = t;
}

void printArr(int arr[], int size) {
    for (int i = 0 ; i < size ; i++)
        cout << arr[i] << " ";

    cout << endl;
}
