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

int getHeight(btptr T)
{
    if(T==NULL)
        return 0;
    return (1+max(getHeight(T->lchild), getHeight(T->rchild)));
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

void findVerticalSum(btptr T, int verticalSum[], int currPos, int minn)
{
    if(T==NULL)
        return;
    verticalSum[currPos + minn] += T->data;
    findVerticalSum(T->lchild, verticalSum, currPos-1, minn);
    findVerticalSum(T->rchild, verticalSum, currPos+1, minn);
}


void printVerticalSum(btptr T)
{
    int minn = 0, maxx = 0;
    findMin(T, 0, minn);
    findMax(T, 0, maxx);
    minn = minn * (-1);
    int n = minn+maxx+1;

    int verticalSum[n];
    for(int i=0;i<n;i++)    verticalSum[i] = 0;
    findVerticalSum(T, verticalSum, 0, minn);
    for(int i=0;i<n;i++)
        cout<<verticalSum[i]<<" ";
    cout<<endl;
}

void findHorizontalSum(btptr T, int horizontalSum[], int currPos)
{
    if(T==NULL)
        return;
    horizontalSum[currPos] += T->data;
    findHorizontalSum(T->lchild, horizontalSum, currPos+1);
    findHorizontalSum(T->rchild, horizontalSum, currPos+1);
}

void printHorizontalSum(btptr T)
{
    int n = getHeight(T);   /// height is 1 if only root node is there
    int horizontalSum[n];
    for(int i=0;i<n;i++)    horizontalSum[i] = 0;
    findHorizontalSum(T, horizontalSum, 0);
    for(int i=0;i<n;i++)
        cout<<horizontalSum[i]<<" ";
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

int main()
{
    btptr T = NULL;
    int i=0;
    takeInput(T);
    printVerticalSum(T);
    printHorizontalSum(T);


    return 0;
}
/// 1 2 4 0 0 5 0 0 3 6 0 0 7 0 0
/// 5 3 2 1 0 0 0 4 0 0 7 6 0 0 9 8 0 0 0
