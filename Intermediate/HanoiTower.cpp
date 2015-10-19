#include <iostream>
using namespace std;

int TowersOfHanoi(int num, char a, char b, char c) {
    if (num == 1) 
        cout << "Mov top disk from pole " << a << " to pole " << c << endl;
    else {
        TowersOfHanoi(num-1, a, c, b);
        TowersOfHanoi(1, a, b, c);
        TowersOfHanoi(num-1, b, a, c);
    }    
}

int main() {
    int disks;
    cout << "Numbers of disks: ";
    cin >> disks;
    TowersOfHanoi(disks,'A','B','C');
    return 0;
}