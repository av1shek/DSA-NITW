#include<bits/stdc++.h>
using namespace std;
typedef struct btnode *btptr;

struct btnode
{
    btptr lchild;
    char data;
    btptr rchild;

    btnode()
    {
        lchild = NULL;
        rchild = NULL;
    }
    btnode(char k)
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

    if(temp->data != '.')
    {
        insertChilds(temp);
        T->lchild = temp;
    }

    btptr temp2 = new btnode;
    cin>>temp2->data;

    if(temp2->data != '.')
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

void printInorder(btptr T)
{
    if(T == NULL)
        return;
    printInorder(T->lchild);
    cout<<T->data<<" ";
    printInorder(T->rchild);
    return;
}

void printLevelOrder(btptr T)
{
    queue<btptr> q;
    q.push(T);
    btptr temp = new btnode;
    temp->data = -1;
    q.push(temp);
    while(!q.empty())
    {
        temp = q.front(); q.pop();
        cout<<temp->data<<" ";
        if(temp->lchild)
            q.push(temp->lchild);
        if(temp->rchild)
            q.push(temp->rchild);
        if( q.front()->data==-1)
        {
            btptr temp2 = q.front(); q.pop();
            if(!q.empty())
            {
                cout<<endl;
                q.push(temp2);
            }
        }
    }
}

int main()
{
    btptr T = NULL;
    takeInput(T);
    printInorder(T); cout<<endl;

    return 0;
}
