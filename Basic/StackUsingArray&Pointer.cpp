#include <iostream>
#include <cstdlib>
using namespace std;

class Stack {
    int size, count = 0;
    int *data;
    int *curr = NULL;
public:
    Stack(int s) {
        size = s;
        data = new int[s];
    }
    
    void push(int d) {
        if (size == count) {
            cout << "Stack Overflow." << endl;
            return;
        }
        
        if (curr == NULL)
            curr = data;
        else     
            curr++;
        
        *curr = d;
        count++;
    }

    void pop() {
        if (count == 0) {
            curr = NULL;
            cout << "Stack Underflow." << endl;
            return;
        }        
        curr--;
        count--;
    }
    
    void top() {
        if (count == 0) {
            cout << "Stack Empty" << endl;
            return;
        }
        cout << *curr << endl;
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
    
    s.pop(); // Stack underflow
    s.pop(); // Stack underflow
    s.pop(); // Stack underflow
    s.pop(); // Stack underflow
    s.top(); // Empty    

    s.push(6); // Stack overflow
    s.top();
    s.pop();
    s.top();
    
    
    system("pause");
    return 0;
}