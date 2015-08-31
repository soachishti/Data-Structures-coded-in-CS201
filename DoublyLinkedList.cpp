#include <iostream>
#include <cstdlib>

using namespace std;

struct node {
    int info;
    node *next = NULL;
    node *prev = NULL;
};

class DoublyLinkedList {
    private:    
    int size = 0;
    node *head = NULL;
    node *tmp = NULL;
    node *tmp2 = NULL;
    
    public:
    node* search(int key) {
        tmp = head;
        if (head != NULL) {
            do {
                if (tmp->info == key) return tmp;                
            }
            while (tmp = tmp->next);
        }
        return NULL;
    }
    
    void insert(int data) {
        if (head == NULL) {
            head = new node;
            head->info = data;
        } 
        else {
            tmp = new node;
            tmp->info = data;
            tmp->next = head;
            head->prev = tmp;
            head = tmp;
        }
        size++;
    }

    void insertAfter(int key, int data) {
        tmp = head;
        if(!tmp) return;
        do {
            if (tmp->info == key) break;   
        }
        while (tmp = tmp->next);
    
        node *tmp1 = new node;
        tmp1->info = data;
        
        tmp1->next = tmp->next;
        
        if (tmp->next != NULL) {
            tmp->next->prev = tmp1;
        }
        tmp1->prev = tmp;
        tmp->next = tmp1;        
        size++;
    }
    
    void remove(int key) {       
        tmp = head;
        if (!tmp) return;
        
        while (tmp != NULL) {
            if (tmp->info == key) {
                if(tmp->prev == NULL) {
                    // If first element
                    tmp2 = tmp;
                    tmp = head = tmp->next;
                    head->prev = NULL;
                    delete tmp2; 
                }
                else {
                    // If in the middle
                    tmp2 = tmp;
                    tmp->prev->next = tmp->next;
                    if (tmp->next != NULL) {
                        // If it is not last element
                        tmp->next->prev = tmp->prev;
                    }
                    tmp = tmp->next;
                    delete tmp2;
                }
            }
            else {            
                tmp = tmp->next;
            }
        }
        size--;
    }
    
    void print() { 
        tmp = head;
        if (!tmp) return;
        do {
            cout << tmp->info << endl;
        }  
        while (tmp = tmp->next);
    }
};

int main() {
    DoublyLinkedList lst;
    
    lst.insert(1);
    lst.insert(1);
    lst.insert(1);
    lst.insert(2);
    lst.insert(3);
    lst.insert(4);
    lst.insert(5);
    lst.insert(6);
    lst.insert(7);
    lst.insert(8);
    lst.insert(9);
    lst.insert(10);
    
    
    lst.insertAfter(2, 11);
    lst.insert(1000);
    lst.insertAfter(10, 12);
    
    lst.remove(1000);  // First element
    lst.remove(11);  // from mid
    lst.remove(10);  // First element
    lst.remove(1); // End
    
    lst.insertAfter(9, 10);   // It will be added after 9 not before because this model is based on LIFO
    lst.insertAfter(10,11);
    lst.insertAfter(2,1);
    lst.insertAfter(12,13);
    
    cout << "Location of 9 in LinkedList: " << lst.search(9);
    
    cout << endl
         << "List of all data:"
         << endl;
    lst.print();
    
    system("pause");
    return 0;
}