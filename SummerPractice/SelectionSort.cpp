#include "start.cpp"

int main() {
    const int SIZE = 10;
    int data[SIZE] = {2,4,3,8,5,6,4,9,3,2};

    for (int i = 1 ; i < SIZE ; i++) {
        int min = i;
        for (int k = i ; k < SIZE ; k++ ) {
            if(data[min] > data[k]) {
                min = k;
            }
        }
        if (i != min) swap(data[i],data[min]);
    }

    cout << endl;
    printArr(data,SIZE);


    return 0;
}

