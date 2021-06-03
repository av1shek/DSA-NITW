#include<bits/stdc++.h>
using namespace std;
typedef struct btnode *btptr;

struct btnode
{
    btptr lchild;
    int data;
    int x;
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
bool isBSTUtils(btptr T, int low, int high)
{
    if(T==NULL)
        return true;
    if(T->data>=low && T->data<=high)
    {
        if(!isBSTUtils(T->lchild, low, T->data-1))
            return false;
        if(!isBSTUtils(T->rchild, T->data+1, high))
            return false;
    }
    else
        return false;
    return true;
}

bool isBST(btptr T)
{
    return isBSTUtils(T, INT_MIN, INT_MAX);
}

btptr nonBSTNodeUtils(btptr T,  int low, int high)
{
    if(T==NULL)
        return T;
    if(T->data>=low && T->data<=high)
    {
        btptr t1 = nonBSTNodeUtils(T->lchild, low, T->data-1);
        btptr t2 = nonBSTNodeUtils(T->rchild, T->data+1, high);

        if(t1!=NULL && t2!=NULL)
            return T;
        if( (t1!=NULL) && (t1->data > T->data) )
            return T;
        if(t2!=NULL && (t2->data < T->data) )
            return T;
        if(t1!=NULL)
            return t1;
        if(t2!=NULL)
            return t2;
    }
    else
        return T;
    return NULL;

}
btptr nonBSTNode(btptr T)
{
    btptr temp = NULL;
    return nonBSTNodeUtils(T, INT_MIN, INT_MAX);

}



int main()
{
    btptr T = NULL;
    takeInput(T);
    if(isBST(T))
        cout<<"it is bst"<<endl;
    else
        cout<<"BST is not satisfied at "<<nonBSTNode(T)->data;
    return 0;
}
/// 6 4 3 0 0 5 0 0 8 7 0 0 9 0 0
/// 8 3 1 99 0 0 0 6 4 0 0 7 0 0 10 9 0 0 14 13 0 0 0
