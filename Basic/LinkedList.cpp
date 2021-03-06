#include <iostream>
#include <cstdlib>

using namespace std;

struct node {
    int info;
    node *next = NULL;
};

class LinkedList {
    private:    
    int size = 0;
    
    node *tmp = NULL;
    node *tmp2 = NULL;
    
    public:
    node *head = NULL;
    node* search(int key) {
        tmp = head;
        if (head != NULL) {
            while (tmp->next != NULL) {
                if (tmp->info == key) return tmp;
                tmp = tmp->next;
            }
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
            head = tmp;
        }
        size++;
    }

    void insertAfter(int key, int data) {
        if (!tmp) return;       
        tmp = head;
        
        while(tmp->next != NULL) {
            if (tmp->info == key) break;
            tmp = tmp->next;
        }
            
        tmp2 = new node;
        tmp2->info = data;
        
        tmp2->next = tmp->next;
        tmp->next = tmp2;
            
        size++;
    }
    
    void remove(int key) {      
        tmp = head;
        if (!tmp) return; 
        tmp2 = NULL;
        while(tmp->next != NULL) {
            if (tmp->info == key) {
                if (tmp && tmp2) {
                    // Remove value in middle
                    tmp2->next = tmp->next;
                    delete tmp;
                    tmp = tmp2;
                }
                else if(!tmp2) {
                    // removing first value
                    head = tmp->next;
                    delete tmp;
                    tmp = head;
                }
                else {
                    // not required **
                    // removing last value
                    tmp2->next = NULL;
                    tmp = NULL;
                    head = NULL;
                }
            }   
            
            // History
            tmp2 = tmp;
            tmp = tmp->next;
        }
        
        size--;
    }
    
    void printRecursive(node *tmp) {
        if (tmp != NULL) {
            printRecursive(tmp->next);
            cout << tmp->info;
        }
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
    LinkedList lst;
    
    lst.insert(1);
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
    
    lst.print();
    lst.printRecursive(lst.head);
    return 0;
    lst.remove(1);  // First element
    lst.remove(2);  // from mid
    lst.remove(5);  // from mid
    lst.remove(10);
    
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