#include<bits/stdc++.h>
using namespace std;
typedef struct bstnode *bstptr;

void takeInput(bstptr &);           /// takes input till -1
void insert(bstptr &, int);         /// insert a integer value


struct bstnode
{
    struct bstnode *lchild;
    int data;
    struct bstnode *rchild;
    bstnode()
    {
        lchild = NULL;
        rchild = NULL;
    }
    bstnode(int k)
    {
        lchild = NULL;
        data = k;
        rchild = NULL;
    }
};


void insert(bstptr &T, int k)
{
    if(T==NULL)
        T = new bstnode(k);
    else if(k > T->data)
        insert(T->rchild, k);
    else if(k < T->data)
        insert(T->lchild, k);
    return;
}


void takeInput(bstptr &T)
{
    while(true)
    {
        int temp;
        cin>>temp;

        if(temp == -1)
            break;
        insert(T, temp);
    }
}

void findDeadNode(bstptr T, int low, int high)
{
    if(T==NULL)
        return;
    if(T->lchild==NULL && T->rchild==NULL)
    {
        if(low==high && low==T->data)
            cout<<T->data<<" ";
        return;
    }
    findDeadNode(T->lchild, low, T->data-1);
    findDeadNode(T->rchild, T->data+1, high);
    return;
}

void findDeadNode(bstptr T)
{
    findDeadNode(T, INT_MIN, INT_MAX);
}

int main()
{
    bstptr T = NULL;
    takeInput(T);
    findDeadNode(T);

    return 0;
}
