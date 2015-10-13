#include "start.cpp"

int main() {
    const int SIZE = 10;
    int data[SIZE] = {2,4,3,8,5,6,4,9,3,2};

    for (int i = 0 ; i < SIZE ; i++) {
        for (int k = i; k > 1 ;k--) {
            if (data[k] <= data[k-1]) {
                swap(data[k],data[k-1]);
            }
        }
    }

    printArr(data,SIZE);

    return 0;
}
