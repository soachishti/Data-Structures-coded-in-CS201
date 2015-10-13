#include "start.cpp"

int main() {
    const int SIZE = 10;
    int data[SIZE] = {2,4,3,8,5,6,4,9,3,2};
    bool flag;
    int count = 0;

    while (true) {
        flag = false;
        for (int i = 1 ; i < SIZE ; i++) {
            if (data[i-1] > data[i]) {
                swap(data[i-1],data[i]);
                flag = true;
            }
            count++;
        }
        if (!flag) break;
    }
    cout << count << endl;
    printArr(data,SIZE);


    return 0;
}
