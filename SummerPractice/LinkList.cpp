#include <iostream>
using namespace std;

struct node {
    int data;
    node *next = NULL;
};

class LinkList {
private:
    node *head = new node;
    node *curr = head;
public:
    void add(int d) {
        curr->data = d;
        curr->next = new node;
        curr = curr->next;
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
    LinkList list;
    list.add(10);
    list.add(20);
    list.add(30);

    list.showAll();
}
