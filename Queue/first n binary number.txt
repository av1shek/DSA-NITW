#include <bits/stdc++.h>
using namespace std;

struct queuee
{
    int front;
    int rear;
    string elements[500];
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
    bool isEmpty()
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
    void enqueue(string x)
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
    string dequeue()
    {
        if(isEmpty())
        {
            cout<<"Queue is empty"<<endl;
            return "";
        }
        string data = elements[front];
        if(front == rear)
            front = rear = -1;
        else
            front = (front+1)%size;
        return data;
    }
};

void printFirstNBinaryNum(struct queuee &q, int n, int i)
{
    if(i<=n)
    {
        string data = q.dequeue();
        cout<<data<<" ";
        if(!q.isFull())
            q.enqueue(data + "0");
        if(!q.isFull())
            q.enqueue(data + "1");
        printFirstNBinaryNum(q, n, i+1);
    }
}

int main()
{
    int n=11;
    struct queuee q(n);
    q.enqueue("1");
    printFirstNBinaryNum(q, n, 1);
    return 0;
}
