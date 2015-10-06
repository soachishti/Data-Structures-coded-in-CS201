#include <iostream>
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

    bool isEmpty() {
        if (topPtr == NULL) 
            return true;
        return false;
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

bool check(string s) {
    Stack stk(10);
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(') 
            stk.push(1);
        else if (s[i] == ')')
        {   
            if (stk.isEmpty()) {
                cout << "Syntax Error! - Too many ')'";
                return 0;
            }
            stk.pop();
        }
    }
    if (stk.isEmpty()) {
        cout << "Everything Good";
        return 1;
    }
    else {
        cout << "Syntax Error! - Too many '('";
        return 0;                
    }
}

int main () {
    string str = "((a + b) - c) + 3)";
    cout << str << endl;
    check(str);
    cout << endl << endl;
    
    str = "((a + b) - c) + 3";
    cout << str << endl;
    check(str);
    cout << endl << endl;
    
    str = "((((a + b) - c) + 3)";
    cout << str << endl;
    check(str);
    cout << endl << endl;
    
}