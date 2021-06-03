#include<bits/stdc++.h>
using namespace std;
typedef struct bstnode *bstptr;

void takeInput(bstptr &);           /// takes input till -1
void insert(bstptr &, int);         /// insert a integer value
void printInorder(bstptr);          /// print lchild, self , rchild

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

int getHeight(bstptr T)
{
    if(T==NULL)
        return 0;
    return ( 1 + max(getHeight(T->lchild), getHeight(T->rchild)));
}

void leftR(bstptr &T)
{
    bstptr T2 = T->rchild;
    T->rchild = T2->lchild;
    T2->lchild = T;
    T = T2;
    return;
}

void rightR(bstptr &T)
{
    bstptr T2 = T->lchild;
    T->lchild = T2->rchild;
    T2->rchild = T;
    T = T2;
}

void insert(bstptr &T, int key)
{
    if(T==NULL)
        T = new bstnode(key);
    else if(key > T->data)
        insert(T->rchild, key);
    else if(key < T->data)
        insert(T->lchild, key);
    else
        return;

    int balance = getHeight(T->lchild) - getHeight(T->rchild);

    if (balance > 1 && key < T->lchild->data)
    {
        rightR(T);
        return;
    }

    if (balance < -1 && key > T->rchild->data)
    {
        leftR(T);
        return;
    }

    if (balance > 1 && key > T->lchild->data)
    {
        leftR(T->lchild);
        rightR(T);
        return;
    }

    if (balance < -1 && key < T->rchild->data)
    {
        rightR(T->rchild);
        leftR(T);
        return;
    }
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

void printLevelOrder(bstptr T)
{
    if(T==NULL)
        return;

    queue<bstptr> q;
    q.push(T);

    while(!q.empty())
    {
        int n = q.size();
        for(int i=0;i<n;i++)
        {
            bstptr temp = q.front();
            q.pop();

            cout<<temp->data<<" ";
            if(temp->lchild)
                q.push(temp->lchild);
            if(temp->rchild)
                q.push(temp->rchild);
        }
        cout<<endl;
    }
    return;
}


int main()
{
    bstptr T1 = NULL;
    takeInput(T1);
    printInorder(T1);   cout<<endl;
    printLevelOrder(T1);
    return 0;
}
