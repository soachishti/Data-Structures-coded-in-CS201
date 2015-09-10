#include <iostream>
#include <cstdlib>
#include <windows.h>
using namespace std;

struct node {
	int info;
	node *next;
};

class JosephusProblem {
	node *head = NULL;
	node *tail = NULL;
	node *tmp = NULL;
	node *tmp2 = NULL;
public:
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
	}

	void solveRand() {
		tmp2 = head;
        node *tmp3;
        do {
            for (int i = 0; i < 3 - 2; i++) {
                tmp2 = tmp2->next;                
            }
            cout << "Deleting " << tmp2->info << endl;
			tmp3 = tmp2->next;      
            tmp2->next = tmp2->next->next;
			if (tmp3 == head)
				head = tmp2->next;
            delete tmp3;
            //tmp2 = tmp2->next;
            Sleep(50);
		} while (head->next != head);

		cout << head->info << endl;
	}    
    
	void solve() {
		tmp = head;
		do {
			tmp2 = tmp->next->next;
			cout << "Deleting " << tmp2->info << endl;
			
			tmp->next->next = tmp->next->next->next;
			if (tmp2 == head)
				head = tmp2->next;
			delete tmp2;
			tmp = tmp->next;
		} while (head->next != head);

		cout << head->info << endl;
	}
};

int main() {
	JosephusProblem jp;
	jp.insert(1);
	jp.insert(2);
	jp.insert(3);
	jp.insert(4);
	jp.insert(5);
	jp.insert(6);
	jp.insert(7);
	jp.insert(8);
	jp.insert(9);
	jp.insert(10);

	jp.solveRand();

	//jp.solve();


	system("pause");
	return 0;
}