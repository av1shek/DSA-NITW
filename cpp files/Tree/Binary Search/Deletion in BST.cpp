#include<bits/stdc++.h>
using namespace std;
typedef struct bstnode *bstptr;

void takeInput(bstptr &);           /// takes input till -1
void insert(bstptr &, int);         /// insert a integer value
void printInorder(bstptr);          /// print left, self , right

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

int getMin(bstptr T)
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

int getMax(bstptr T)
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

void DeleteNodeBST(bstptr &T, int k)
{
    if(T==NULL)
        return;
    if(T->data == k)
    {
        if( (T->rchild==NULL) && (T->lchild==NULL) )
        {
            T = NULL;
            return;
        }

        if( (T->rchild==NULL) && (T->lchild!=NULL) )
        {
            T = T->lchild;
            return;
        }
        else if( (T->rchild!=NULL) && (T->lchild ==NULL) )
        {
            T = T->rchild;
            return;
        }

        else
        {
            T->data = getMin(T->rchild);
            DeleteNodeBST(T->rchild, T->data);
            return;
        }
    }
    if(T->data > k)
        DeleteNodeBST(T->lchild, k);
    else
        DeleteNodeBST(T->rchild, k);

}



int main()
{
    bstptr T1 = NULL, T2 = NULL;
    takeInput(T1);
    DeleteNodeBST(T1, 20);
    printInorder(T1);   cout<<endl;

    T1 = NULL, T2 = NULL;
    takeInput(T1);
    DeleteNodeBST(T1, 30);
    printInorder(T1);      cout<<endl;

    T1 = NULL, T2 = NULL;
    takeInput(T1);
    DeleteNodeBST(T1, 50);
    printInorder(T1);
    return 0;
}

/// 50 30 40 20 70 60 80 -1
/// 50 40 70 80 60 -1
/// 50 30 70 80 60 40 -1
