#include <iostream>
using namespace std;

int factorialRecursive(int num) {
    if (num == 0)   return 1;
    else            return num * factorialRecursive(num - 1);
}

int factorialIteration(int num) {
    int fact = 1;
    for (int i = 1; i <= num; i++) {
        fact *= i;
    }
    return fact;
}

int i = 0;

void Recursive()
{
    // 64891
    ++i; // The value here will show you how deeper in stack you can go
    cout << i << endl;
    Recursive();
}

int main() {
    // Recursive();
    // return 0;
    
    
    int num;
    cout << "Enter number: ";
    cin >> num;
    cout << "FactorialIteration of " << num << " is " << factorialIteration(num) << endl;
    cout << "FactorialRecursive of " << num << " is " << factorialRecursive(num) << endl; 
    return 0;
}