#include <iostream>
using namespace std;

struct node {
    int data;
    node *next = NULL;
    node *prev = NULL;
};

class DoublyLinkedList {
private:
    node *head = new node;
    node *curr = head;
public:
    void add(int d) {
        curr->data = d;
        curr->next = new node;  // Adding new node
        curr->next->prev = curr; // Setting previous node of next element
        curr = curr->next; // Setting curr to last element
    }

    void showAllReverse() {
        node *load = curr->prev;
        while(load->prev != NULL) {
            cout << load->data << endl;
            load = load->prev;
        }
        cout << load->data << endl;
    }

    void showAll() {
        node *load = head;
        while(load->next != NULL) {
            cout << load->data << endl;
            load = load->next;
        }
    }
};

int main(){
    DoublyLinkedList list;
    list.add(10);
    list.add(20);
    list.add(30);

    list.showAll();

    cout << endl << endl;

    list.showAllReverse();
}
