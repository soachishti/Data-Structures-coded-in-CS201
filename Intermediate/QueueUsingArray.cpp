#include <iostream>
using namespace std;

class Queue {
public: 
    int size, *data, *front = NULL, *rear = NULL;
    bool full;
    Queue(int s) {
        full = false;
        size = s;
        data = new int[size];
        front = data;
    }
    
    void enQueue(int d) {  
        int *tmp = (front == data) ? data + size - 1: front - 1;
        if (rear == tmp) {
            cout << "Queue is full" << endl;
        }
        else {    
            if (rear == NULL) {
                rear = data;
                *rear = d;
            }
            else {
                if (rear == (data + size - 1)) 
                    rear = data;
                else 
                    rear++;
                *rear = d;
            }
            cout << d << "\t\t" << rear << endl;
        }
    }
    
    void deQueue(){                       
        if (rear == NULL) {
            cout << "Queue is empty." << endl;
        }
        else {
            if (rear == front) rear = NULL;
            int tmp = *front;
            *front = -1;
            if (front == data + size - 1)   front = data;
            else                            front++;
       
            cout << tmp << endl;
        }
    }    
    
    void info () {
        cout << endl << endl;
        for (int i = 0 ; i < size ;i++) {
            if (rear == data + i)   cout << "r";
            if (front == data + i)  cout << "f";
            cout << "\t";
            cout << *(data + i) << "\t\t" << data + i << endl; 
        }
        cout << endl << endl;
    }
};

int main () {    
    Queue q(5);
    
    //q.deQueue();    // Empty
        
    q.enQueue(0);
    q.enQueue(1);
    q.enQueue(2);
    q.enQueue(3);
    q.enQueue(4);
    q.enQueue(5);       // Full
    q.enQueue(6);       // Full
    q.info();           
    
    q.deQueue();
    q.deQueue();
    q.deQueue();
    q.deQueue();
    q.deQueue();
    q.deQueue();        // Empty

    q.info();
    
    q.enQueue(6);
    q.enQueue(7);
    q.deQueue();
    q.deQueue();
    q.deQueue();        //Empty
     
    return 0;
}