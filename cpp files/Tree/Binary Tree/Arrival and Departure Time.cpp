#include<bits/stdc++.h>
using namespace std;
typedef struct btnode *btptr;

struct btnode
{
    btptr lchild;
    int arrivalTime;
    int data;
    int departureTime;
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

int getHeight(btptr T)
{
    if(T==NULL)
        return 0;
    return (1+max(getHeight(T->lchild), getHeight(T->rchild)));
}

void assignTiming(btptr T, int &time)
{
    if(T==NULL)
        return;
    T->arrivalTime = time++;
    assignTiming(T->lchild, time);
    assignTiming(T->rchild, time);
    T->departureTime = time++;
    return;
}

void printInorder(btptr T)
{
    if(T == NULL)
        return;
    printInorder(T->lchild);
    cout<<T->data<<" ("<<T->arrivalTime<<", "<<T->departureTime<<") ";
    printInorder(T->rchild);
    return;
}

int main()
{
    btptr T = NULL;
    int i=0;
    takeInput(T);
    assignTiming(T, i);
    printInorder(T);


    return 0;
}

///-----------------------------------------------------------
/// 5 3 2 1 0 0 0 4 0 0 7 6 0 0 9 8 0 0 0
