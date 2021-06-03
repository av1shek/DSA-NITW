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
void print(btptr temp)
{
    for(int i=1;i<=temp->x; i++)
        cout<<setw(2)<<" ";
    if(temp->data)
        cout<<setw(2)<<temp->data;
    else
        cout<<setw(2)<<"_";
}

void printLevelOrder(btptr T)
{
    queue<btptr> q;
    q.push(T);
    btptr temp = new btnode;
    temp->data = -1;
    q.push(temp);
    int pos = 0;
    while(!q.empty())
    {
        temp = q.front(); q.pop();
        temp->x -= (pos);
        pos += temp->x+1;
        print(temp);
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
                pos = 0;
                q.push(temp2);
            }
        }
    }
}

void inorderIndex(btptr T, int &i)
{
    if(T == NULL)
        return;
    inorderIndex(T->lchild, i);
    T->x = i++;
    inorderIndex(T->rchild, i);
    return;
}
int getHeight(btptr T)
{
    if(T==NULL)
        return 0;
    return max(getHeight(T->lchild), getHeight(T->rchild)) + 1;
}
void completeTree(btptr &T, int currH, int height)
{
    if(currH == height)
    {
        if(T == NULL)
            T = new btnode(0);
        return;
    }
    if(T->lchild == NULL)
        T->lchild = new btnode(0);
    if(T->rchild == NULL)
        T->rchild = new btnode(0);
    completeTree(T->lchild, currH+1, height);
    completeTree(T->rchild, currH+1, height);
    return;
}
void draw(btptr T)
{
    int i=0, h = getHeight(T);
    completeTree(T, 1, h);
    inorderIndex(T, i);
    printLevelOrder(T);
}



int main()
{
    btptr T = NULL;
    takeInput(T);
    draw(T);
    return 0;
}
/// 6 4 3 0 0 5 0 0 8 7 0 0 9 0 0
/// 8 3 1 99 0 0 0 6 4 0 0 7 0 0 10 9 0 0 14 13 0 0 0
