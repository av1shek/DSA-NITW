#include<iostream>
using namespace std;
typedef struct lnode *lptr;
bool flag=true;
struct lnode
{
    int data;
    struct lnode *next;
    lnode(){next=NULL;}
};

void linsert(lptr &P, int x)
{
    lptr temp = new lnode;
    temp->data = x;
    if(P == NULL) P = temp;
    else
    {
        lptr T = P;
        while(T->next != NULL)
            T = T->next;
        T->next = temp;
    }
}

void ltakeinput(lptr &L)
{
    int x;
    cin>>x;
    if(x==-1)
    {
        flag = false;
        return;
    }
    while(x!= 0)
    {
        linsert(L, x);
        cin>>x;
    }
}


struct queue
{
    int front;
    int rear;
    lptr elements[500];
    int size;

    queue()
    {
        front = -1;
        rear = -1;
        for(int i=0;i<500; i++) elements[i] = NULL;
        size = 500;
    }

    bool isEmpty()
    {
        if(front == -1) return true;
        return false;
    }

    bool isFull()
    {
        if((rear+1)%size==front) return true;
        return false;
    }

    void enqueue(lptr x)
    {
        if(isFull()) return;
        rear = (rear+1)%size;
        elements[rear] = x;
        if(front == -1)
            front=rear;
    }

    lptr dequeue()
    {
        if(isEmpty())
            return NULL;
        lptr data = elements[front];
        if(front == rear)
            front = rear = -1;
        else
            front = (front + 1)%size;
        return data;
    }
};

int main()
{
    // int n = 10;
    struct queue q;
    while(true)
    {
        if(flag==false)
            break;
        lptr L = NULL;
        ltakeinput(L);
        q.enqueue(L);
    }

    while(!q.isEmpty())
    {
        lptr L = q.dequeue();
        while(L!=NULL)
        {
            cout<<L->data<<" ";
            L = L->next;
        }
        cout<<endl;
    }
    return 0;
}










