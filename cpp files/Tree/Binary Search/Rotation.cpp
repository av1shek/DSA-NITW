#include<bits/stdc++.h>
using namespace std;
typedef struct trnode *trptr;

void takeInput(trptr &);           /// takes input till -1
void insert(trptr &, int);         /// insert a integer value
void printInorder(trptr);          /// print left, self , right

struct trnode
{
    struct trnode *lchild;
    int data;
    struct trnode *rchild;
    trnode()
    {
        lchild = NULL;
        rchild = NULL;
    }
    trnode(int k)
    {
        lchild = NULL;
        data = k;
        rchild = NULL;
    }
};

void insert(trptr &T, int k)
{
    if(T==NULL)
        T = new trnode(k);
    else if(k > T->data)
        insert(T->rchild, k);
    else if(k < T->data)
        insert(T->lchild, k);
    return;
}

void printInorder(trptr T)
{
    if(T == NULL)
        return;
    printInorder(T->lchild);
    cout<<T->data<<" ";
    printInorder(T->rchild);
    return;
}

void printPreorder(trptr T)
{
    if(T==NULL)
        return;
    cout<<T->data<<" ";
    printPreorder(T->lchild);
    printPreorder(T->rchild);
    return;
}


void takeInput(trptr &T)
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

int getMin(trptr T)
{
    if(T==NULL)
    {
        cout<<"Not valid"<<endl;
        return INT_MAX;
    }
    if(T->lchild==NULL)
        return T->data;
    else
        return getMin(T->lchild);
}

int getMax(trptr T)
{
    if(T==NULL)
    {
        cout<<"Not valid"<<endl;
        return -1;
    }
    if(T->rchild==NULL)
        return T->data;
    else
        return getMax(T->rchild);
}

trptr leftR(trptr &T, int k)
{
    if(T==NULL || T->data==k)
    {
        trptr T2 = T->rchild;

        T->rchild = T2->lchild;
        T2->lchild = T;
        T = T2;
        return NULL;
    }
    if(k > T->data)
        return leftR(T->rchild, k);
    if(k < T->data)
        return leftR(T->lchild, k);
    return NULL;
}


trptr rightR(trptr &T, int k)
{
    if(T==NULL || T->data==k)
    {
        trptr T2 = T->lchild;

        T->lchild = T2->rchild;
        T2->rchild = T;
        T = T2;
        return NULL;
    }
    if(k > T->data)
        return rightR(T->rchild, k);
    if(k < T->data)
        return rightR(T->lchild, k);
    return NULL;
}


int main()
{
    trptr T = NULL;
    int cnt = 4;
    while(cnt--)
    {
        int temp;
        while(true)
        {
            cin>>temp;
            if(temp == -1)
                break;
            insert(T, temp);
        }
        int a, b;
        cin>>a>>b;
        leftR(T, a);
    }
    cin>>cnt;
    printPreorder(T);
    return 0;
}

/// 1 2 3 -1 1 0 4 5 -1 3 0 6 -1 2 0 7 -1 5 0 -2
