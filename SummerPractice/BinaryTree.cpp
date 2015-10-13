#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

struct node
{
    int data = 0;
    node *left = NULL;
    node *right = NULL;
};

class BinaryTree
{
private:
    node *head = NULL;
public:
    void add(int d)
    {
        if (head == NULL)
        {
            head = new node;
            head->data = d;
        }
        else
        {
            node* tmp;
            tmp = getPosition(d);
            tmp->data = d;
        }
    }

    bool search (int d)
    {
        node *load = head;
        while(load != NULL)
        {
            if (d == load->data)
            {
                return true;
            }
            else if(d < load->data)
            {
                load = load->left;
            }
            else
            {
                load = load->right;
            }
        }
        return false;
    }

    node* getPosition (int d)
    {
        node *load = head;
        while(load != NULL)
        {
            if(d < load->data)
            {
                if (load->left == NULL)
                    return (load->left = new node);
                else
                    load = load->left;
            }
            else
            {
                if (load->right == NULL)
                    return (load->right = new node);
                else
                    load = load->right;
            }
        }
        return NULL;
    }

    void destroy()
    {
        //http://www.careercup.com/question?id=14656728
        if (!head) return;
        vector<node*> v;
        v.push_back(head);
        while(!v.empty())
        {
            node *load = v.back();
            v.pop_back();
            if (load->left)  v.push_back(load->left);
            if (load->right) v.push_back(load->right);
            cout << load << endl;
            delete load;


        }
    }
};

int main()
{
    BinaryTree tree;
    tree.add(10);
    tree.add(20);
    tree.add(30);
    tree.add(5);
    tree.add(2);
    tree.add(1);

    tree.destroy(); // Error Here

    cout << endl << endl;

    cout << tree.search(5) << endl;
    cout << tree.search(2) << endl;
    cout << tree.search(1) << endl;

    cout << tree.search(10) << endl;
    cout << tree.search(20) << endl;
    cout << tree.search(30) << endl;

    cout << tree.search(40) << endl;

}
