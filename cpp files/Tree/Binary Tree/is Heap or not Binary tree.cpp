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

bool isCompleteBinaryTree(btptr T, int currH = 1 )
{
    static int height = getHeight(T);

    if(T==NULL && currH<height)
        return false;
    if(T==NULL)
        return true;
    if( getHeight(T->rchild) > getHeight(T->lchild))
        return false;
    return ( isCompleteBinaryTree(T->lchild, currH+1) && isCompleteBinaryTree(T->rchild, currH+1));
}

bool isMinHeapUtils(btptr T)
{
    if(T == NULL)
        return true;

    if( (T->rchild==NULL) && (T->lchild==NULL ) )
        return true;

    if(T->rchild != NULL)
        if(T->data >= T->rchild->data)
            return false;

    if( T->data >= T->lchild->data)
        return false;
    return ( isMinHeapUtils(T->lchild) && isMinHeapUtils(T->rchild));
}


bool isMaxHeapUtils(btptr T)
{
    if(T == NULL)
        return true;

    if( (T->rchild==NULL) && (T->lchild==NULL ) )
        return true;

    if(T->rchild != NULL)
        if(T->data <= T->rchild->data)
            return false;

    if( T->data <= T->lchild->data)
        return false;
    return ( isMaxHeapUtils(T->lchild) && isMaxHeapUtils(T->rchild));
}

bool isMinHeap(btptr T)
{
    return isCompleteBinaryTree(T) && isMinHeapUtils(T);
}

bool isMaxHeap(btptr T)
{
    return isCompleteBinaryTree(T) && isMaxHeapUtils(T);
}

int main()
{
    btptr T = NULL;
    takeInput(T);
    cout<<"Min Heap = "<<isMinHeap(T)<<endl;
    cout<<"Max Heap = "<<isMaxHeap(T)<<endl<<endl;

    T = NULL;
    takeInput(T);
    cout<<"Min Heap = "<<isMinHeap(T)<<endl;
    cout<<"Max Heap = "<<isMaxHeap(T)<<endl<<endl;

    T = NULL;
    takeInput(T);
    cout<<"Min Heap = "<<isMinHeap(T)<<endl;
    cout<<"Max Heap = "<<isMaxHeap(T)<<endl<<endl;



    return 0;
}
// Complete
/// 1 2 4 0 0 5 0 0 3 0 0
/// 1 2 0 0 3 0 0
/// 1 2 4 0 0 0 3 0 0
/// 1 2 4 0 0 5 0 0 3 6 0 0 0

// Incomplete
/// 1 0 3 0 0
/// 1 2 0 4 0 0 3 5 0 0 6 0 0
/// 1 2 0 0 3 4 0 0 5 0 0


// Min Heap
/// 1 2 3 9 0 0 7 0 0 6 0 0 4 5 0 0 8 0 0

// Max Heap
/// 9 7 6 1 0 0 5 0 0 2 0 0 8 3 0 0 4 0 0
/// 9 7 6 1 0 0 2 0 0 5 0 0 8 4 0 0 3 0 0

