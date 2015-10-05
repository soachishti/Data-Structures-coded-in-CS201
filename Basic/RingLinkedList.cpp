#include <iostream>
#include <cstdlib>

using namespace std;

struct node {
    int info;
    node *next = NULL;
};

class RingLinkedList {
    private:    
    int size = 0;
    node *head = NULL;
    node *tail = NULL;
    node *tmp = NULL;
    node *tmp2 = NULL;
    
    public:
    node* search(int key) {
        tmp = head;        
        if (head != NULL) {
            do {
                if (tmp->info == key) return tmp;
                tmp = tmp->next;
            }
            while (tmp != head);
        }
        return NULL;
    }
    
    void insert(int data) {
        if (head == NULL) {
            head = new node;
            head->info = data;
            head->next = head;
            tail = head;
        } 
        else {
            tmp = new node;
            tmp->info = data;
            tmp->next = head;
            tail->next = tmp;
            head = tmp;
        }
        size++;
    }

    void insertAfter(int key, int data) {
        if (!tmp) return;       
        tmp = head;
        
        do {
            if (tmp->info == key) {
                tmp2 = new node;
                tmp2->info = data;
                tmp2->next = tmp->next;
                tmp->next = tmp2;
                size++;
            }
            tmp = tmp->next;
        }
        while(tmp != head);
    }
    
    void remove(int key) {      
        if (!head) return;
        tmp = head;
        tmp2 = tail;
        
        do {
            //If all data equal to key is in head
            removeHeadAgain:
            if (tmp->info == key) {
                if(tmp == head) {
                    if (head->next == head) {
                        delete head;
                        head = NULL;
                        return;
                    }

                    tail->next = tmp->next;
                    head = tmp->next;
                    delete tmp;
                    tmp = head;
                    goto removeHeadAgain;
                }
                else {
                    // Added
                    if (tmp == tail) 
                        tail = tmp2;
                    
                    tmp2->next = tmp->next;
                    delete tmp;
                    tmp = tmp2->next; 
                }
                
                size--;
            }  
            else {
                // History
                tmp2 = tmp;
                tmp = tmp->next;    
            }
        }
        while(tmp != head);        
    }
    
    void print() {
        if (!head) return; 
        tmp = head;      
        do {
            if (tmp == head && tmp == tail)
                cout << "**" << tmp->info << endl;
            else if (tmp == head)
                cout << "*" << tmp->info << endl;
            else if (tmp == tail)
                cout << "-" << tmp->info << endl;
            else
                cout << tmp->info << endl;
            
            tmp = tmp->next;
        }  
        while (tmp != head);
        
    }
};

int main() {
    RingLinkedList lst;
    
    lst.insert(1);
    lst.insert(1);

    lst.insert(1);
    lst.insert(1);
    lst.insert(2);

 
    lst.remove(1);
    lst.print();
    system("pause");
 
    lst.insert(2);
    lst.insert(3);
    lst.insert(4);
    lst.insert(5);
    lst.insert(6);
    lst.insert(7);
    lst.insert(8);
    lst.insert(9);
    lst.insert(10);
    
    lst.remove(1);  // First element
    lst.remove(2);  // from mid
    lst.remove(5);  // from mid
    lst.remove(10);
    
    lst.insert(2);
        
    lst.insertAfter(9, 10);   // It will be added after 9 not before because this model is based on LIFO
    lst.insertAfter(10,11);
    
    cout << "Location of 9 in LinkedList: " << lst.search(9);
        
    cout << endl
         << "List of all data:"
         << endl;
    lst.print();
    
    system("pause");
    return 0;
}