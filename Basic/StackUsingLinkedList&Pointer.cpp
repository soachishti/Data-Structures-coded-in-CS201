#include <iostream>
#include <cstdlib>
using namespace std;

struct node {
    int info;
    node *next;
};

class Stack {
    int count = 0;
    int *data;
    int limit;
    node *topPtr = NULL;
    node *tmp = NULL;
public:
    
    Stack (int l) {
        limit = l;
    }
    
    void push(int d) {
        if (count == limit) {
            cout << "Stack Overflow." << endl;
            return;
        }
        
        if (topPtr == NULL) {
            topPtr = new node;
            topPtr->next = NULL;
            topPtr->info = d;
        }
        else     
        {
            tmp = new node;
            tmp->info = d;
            tmp->next = topPtr;
            topPtr = tmp;
        }
        count++;
    }

    void pop() {
        if (topPtr == NULL) {
            cout << "Stack Underflow." << endl;
            return;
        }        
        tmp = topPtr;
        topPtr = topPtr->next;
        delete tmp;
        count--;
    }
    
    void top() {
        if (topPtr == NULL) {
            cout << "Stack Empty" << endl;
            return;
        }
        cout << topPtr->info << endl;
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
    s.top(); // Empty    

    s.push(6); // Stack overflow
    s.top();
    s.pop();
    s.top();
    
    
    system("pause");
    return 0;
}