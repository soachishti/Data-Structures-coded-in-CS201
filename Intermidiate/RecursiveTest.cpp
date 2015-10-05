#include <iostream>
using namespace std;

int i = 0;

void Recursive()
{
    // 64891
    ++i; // The value here will show you how deeper in stack you can go
    cout << i << endl;
    Recursive();
}

int fib(int n) {
    if (n <= 2) {
        cout << "1" << " ";
        return 1;
    }
    int res = fib(n-1) + fib(n-2);
    cout << res << " ";
    return res;
}


int main() {
    // Recursive();
    // return 0;
    
    cout << fib(3);

    return 0;
}