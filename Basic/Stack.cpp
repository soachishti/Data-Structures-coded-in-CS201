#include <iostream>
#include <cstdlib>
using namespace std;

class Stack {
    int size;
    int *data;
    int curr = -1;
public:
    Stack(int s) {
        size = s - 1;
        data = new int[s];
    }
    
    void push(int d) {
        if (curr + 1 <= size) {
            curr++;
            data[curr] = d;
        }
        else {
            cout << "Stack Overflow." << endl;
        }
    }

    void pop() {
        if (curr == -1) {
            cout << "Stack Underflow" << endl;
        }   
        else {
            curr--;
        }
    }
    
    void top() {
        if (curr != -1 && curr <= size)
            cout << data[curr] << endl;
        else
            cout << "Stack Empty." << endl;
    }    
};



int main() {
    Stack s(5);
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);
    s.push(6); // Stack overflow

    s.top();
    s.pop();
    
    s.top();
    s.pop();
    
    s.top();
    s.pop();
    
    s.top();
    s.pop();    
    
    s.top();
    s.pop();
    
    s.top(); // Empty
    s.pop(); // Stack underflow
    
    
    system("pause");
    return 0;
}