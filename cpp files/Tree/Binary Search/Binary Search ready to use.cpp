#include<bits/stdc++.h>
using namespace std;
typedef struct bstnode *bstptr;

void takeInput(bstptr &);           /// takes input till -1
void insert(bstptr &, int);         /// insert a integer value
void insertNode(bstptr &, bstptr);  /// insert a node to with some data value
void printInorder(bstptr);          /// print left, self , right
bstptr findbstNode(bstptr, int);    /// return a node whose data value is same as value passed else null

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

void printInorder(bstptr T)
{
    if(T == NULL)
        return;
    printInorder(T->lchild);
    cout<<T->data<<" ";
    printInorder(T->rchild);
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

bstptr findbstNode(bstptr T, int k)
{
    if(T==NULL || T->data==k)
        return T;
    if(k > T->data)
        return findbstNode(T->rchild, k);
    if(k < T->data)
        return findbstNode(T->lchild, k);
    return NULL;
}


int main()
{
    bstptr T1 = NULL, T2 = NULL;
    takeInput(T1);
    takeInput(T2);
    printInorder(T);
    return 0;
}
