#include<iostream>
using namespace std;
typedef struct btnode *btptr;

struct btnode
{
    btptr lchild;
    int data;
    btptr rchild;

    btnode()
    {
        lchild = NULL;
        rchild = NULL;
    }
    btnode(int k)
    {
        lchild = NULL;
        data = k;
        rchild = NULL;
    }
};

void insertChilds(btptr &T)
{
    btptr temp = new btnode;
    cin>>temp->data;

    if(temp->data != 0)
    {
        insertChilds(temp);
        T->lchild = temp;
    }

    btptr temp2 = new btnode;
    cin>>temp2->data;

    if(temp2->data != 0)
    {
        insertChilds(temp2);
        T->rchild = temp2;
    }
    return;
}

void takeInput(btptr &T)
{
    btptr temp = new btnode;
    cin>>temp->data;
    T = temp;
    insertChilds(T);
    return;
}

void print(btptr t1, btptr t2)
{
    if(t1==NULL) return;
    if(t2==NULL) return;

    if(t2->lchild==NULL && t2->rchild==NULL)
    {
        cout<<t1->data<<" ";
        return;
    }
    print(t1->lchild, t2->lchild->lchild);
    print(t1->rchild, t2->lchild->lchild);
}
int main()
{
    btptr T = NULL;
    takeInput(T);
    print(T, T);
    return 0;
}
