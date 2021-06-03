#include<bits/stdc++.h>
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

void findMin(btptr T, int currDis, int &dis)
{
    if(T==NULL)
        return;

    dis = min(dis, currDis);
    findMin(T->lchild, currDis-1, dis);
    findMin(T->rchild, currDis+1, dis);
    return;
}

void findMax(btptr T, int currDis, int &dis)
{
    if(T==NULL)
        return;

    dis = max(dis, currDis);
    findMax(T->lchild, currDis-1, dis);
    findMax(T->rchild, currDis+1, dis);
    return;
}
void print(btptr T, int currDis, int pos, int currH,  int &height, int &data)
{
    if(T==NULL)
        return;

    print(T->lchild, currDis-1, pos, currH+1, height, data);
    print(T->rchild, currDis+1, pos, currH+1, height, data);

    if(currDis == pos)
    {
        if(currH >= height)
        {
            height = currH;
            data = T->data;
        }

        return;
    }

    return;
}
void printBottomView(btptr T)
{
    int minn = 0;
    int maxx = 0;
    findMin(T, 0, minn);
    findMax(T, 0, maxx);
    for(int i=minn;i<=maxx;i++)
    {
        int data, height = INT_MIN;
        print(T, 0, i, 0, height, data);
        cout<<data<<" ";
    }
}
int main()
{
    btptr T = NULL;
    takeInput(T);
    printBottomView(T);
    return 0;
}

/// 20 8 5 0 0 3 10 0 0 14 0 0 22 0 25 0 0 => 5 10 3 14 25
/// 20 8 5 0 0 3 10 0 0 14 0 0 22 4 0 0 25 0 0 =>
