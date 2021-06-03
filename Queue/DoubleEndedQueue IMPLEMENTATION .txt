#include <iostream>
using namespace std;

struct dequee
{
    int front;
    int rear;
    int elements[500];
    int size;

    dequee()
    {
        front = -1;
        rear = -1;
        size = 50;
    }

    dequee(int n)
    {
        front = -1;
        rear = -1;
        size = n;
    }

    bool isEmpty()
    {
        if(front == -1 || rear ==-1)
            return true;
        return false;
    }

    bool isFull()
    {
        if( (rear+1)%size == front )
            return true;
        return false;
    }

    void pushFront(int x)
    {
        if(isFull())
        {
            cout<<"queue is full\n";
        }

        else if(front == -1)
        {
            front = 0;
            rear = 0;
            elements[front] = x;
        }

        else
        {
            front = (front-1+size)%size;
            elements[front] = x;
        }
    }

    void pushRear(int x)
    {
        if(isFull())
            cout<<"Queue is full"<<endl;
        else if(front == -1)
        {
            front=0;
            rear=0;
            elements[rear] = x;
        }
        else
        {
            rear = (rear+1)%size;
            elements[rear] = x;
        }
    }

    int popFront()
    {
        int temp;
        if(isEmpty())
            cout<<"queue is empty\n";
        else if(front==rear)
        {
            temp = elements[front];
            front = -1;
            rear = -1;
        }
        else
        {
            temp = elements[front];
            front = (front+1)%size;
        }
        return temp;
    }

    int popRear()
    {
        int temp;
        if(isEmpty())
            cout<<"queue is empty\n";
        else if(front==rear)
        {
            temp = elements[front];
            front = -1;
            rear = -1;
        }
        else
        {
            temp = elements[rear];
            rear = (rear-1+size)%size;
        }
        return temp;
    }

    int frontItem()
    {
        if(isEmpty())
        {
            cout<<"queue is empty"<<endl;
            return -1;
        }
        return elements[front];
    }

    int rearItem()
    {
        if(isEmpty())
        {
            cout<<"queue is empty"<<endl;
            return -1;
        }
        return elements[rear];
    }

    int getSize()
    {
        if(front==-1)
            return 0;
        return (rear - front + size )%size +1;
    }
};


int main()
{
    struct dequee dq(10);

    cout<<"size initially = "<<dq.getSize()<<endl;

    dq.pushRear(11);
    dq.pushRear(12);
    dq.pushRear(13);
    dq.pushRear(14);
    dq.pushRear(15);
    dq.pushRear(16);

    while(!dq.isEmpty())
        cout<<dq.popRear()<<" ";

    return 0;
}

