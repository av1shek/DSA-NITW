#include<bits/stdc++.h>
using namespace std;
typedef struct bstnode *bstptr;

void takeInput(bstptr &);           /// takes input till -1
void insert(bstptr &, int);         /// insert a integer value

struct queuee
{
    int front;
    int rear;
    bstptr elements[100];
    int size;

    queuee()
    {
        front = -1;
        rear = -1;
        size = 50;
    }
    queuee(int n)
    {
        front = -1;
        rear = -1;
        size = n;
    }
    bool empty()
    {
        if(front == -1)
            return true;
        return false;
    }
    bool isFull()
    {
        if( (rear+1)%size == front )
            return true;
        return false;
    }
    void enqueue(bstptr x)
    {
        if(isFull())
            cout<<"Queue is full"<<endl;
        else
        {
            rear = (rear+1)%size;
            elements[rear] = x;
            if(front == -1)
                front = rear;
        }
        return;
    }
    bstptr dequeue()
    {
        if(empty())
        {
            cout<<"Queue is empty"<<endl;
            return NULL;
        }
        bstptr data = elements[front];
        if(front == rear)
            front = rear = -1;
        else
            front = (front+1)%size;
        return data;
    }
    bstptr getFront()
    {
        return elements[front];
    }
};



struct bstnode
{
    struct bstnode *lchild;
    int *data;
    int d;
    struct bstnode *rchild;
    bstnode()
    {
        lchild = NULL;
        rchild = NULL;
        data = NULL;
    }
    bstnode(int k[], int d)
    {
        lchild = NULL;
        this->d = d;
        data = new int[d];
        for(int i = 0;i<d;i++)
            data[i] = k[i];
        rchild = NULL;
    }
};


void insert(bstptr &T, int k[], int d, int h)
{
    if(T==NULL)
        T = new bstnode(k, d);
    else if(k[h%d] > T->data[h%d])
        insert(T->rchild, k, d, h+1);
    else if(k[h%d] < T->data[h%d])
        insert(T->lchild, k, d, h+1);
    return;
}

void takeInput(bstptr &T, int d)
{
    while(true)
    {
        int temp[d];
        for(int i=0;i<d; i++)
        {
            cin>>temp[i];
            if(temp[0] == -1)
                break;
        }
        if(temp[0] == -1)
                break;
        insert(T, temp, d, 0);
    }
}

void printNode(bstptr node)
{
    if(node == NULL)
        return;
    cout<<"( ";
    for(int i=0;i<node->d; i++)
        cout<<node->data[i]<<" ";
    cout<<") ";
}

void printLevelOrder(bstptr T)
{
    if(T==NULL)
        return;

    queuee q;
    q.enqueue(T);
    q.enqueue(NULL);
    while(!q.empty())
    {
        bstptr temp = q.dequeue();
        printNode(temp);

        if(temp->lchild)
            q.enqueue(temp->lchild);
        if(temp->rchild)
            q.enqueue(temp->rchild);

        if(q.getFront() == NULL)
        {
            q.dequeue();
            if(!q.empty())
                q.enqueue(NULL);
            else
                break;
            cout<<endl;
        }
    }
    cout<<endl;
    return;
}

bool isSame(int arr1[], int arr2[], int d)
{
    for(int i=0;i<d;i++)
        if(arr1[i]!= arr2[i])
            return false;
    return true;
}

bstptr find(bstptr T, int arr[], int h=0)
{
    if(T==NULL)
        return T;

    if(T->data[ h%(T->d) ] == arr[ h%(T->d)])
        return T;

    if(T->data[ h%(T->d) ] > arr[ h%(T->d)])
        return find(T->lchild, arr, h+1);
    else
        return find(T->rchild, arr, h+1);
    return NULL;
}
int main()
{
    int d;
    cin>>d;

    bstptr T = NULL;
    takeInput(T, d);
    printLevelOrder(T);
    int a[T->d];
    a[0] = 3;
    a[1] = 18;
    bstptr temp = find(T, a);
    if(temp == NULL)
        cout<<"NOt persent\n";
    else
        printNode(temp);

    return 0;
}
/*
2
20 5
3 18
70 15
10 80
40 30
80 25
40 10
35 12
-1

*/
