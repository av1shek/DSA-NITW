#include <bits/stdc++.h>
using namespace std;

int maze[8][8]={{0,0,0,0,0,0,0,0},
                {0,1,1,1,1,1,1,0},
                {0,1,0,1,0,0,0,0},
                {0,0,0,1,1,1,1,0},
                {0,1,0,0,0,0,1,0},
                {0,1,0,0,1,0,1,0},
                {0,1,1,1,1,0,1,0},
                {0,0,0,0,0,0,0,0}};

int dx[4] = {1,0, -1, 0 };
int dy[4] = {0,1, 0, -1};

bool isValid(int x, int y)
{
    if(x>7 || x<0)
        return false;
     if(y>7 || y<0)
        return false;
    if(maze[x][y] == 1)
    {
        return true;
    }
    else
        return false;
}

struct coord{
    int x;
    int y;
};

struct queuee
{
    int front;
    int rear;
    struct coord elements[500];
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
    void enqueue(struct coord x)
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
    struct coord dequeue()
    {
        struct coord temp;
        if(isEmpty())
        {
            cout<<"Queue is empty"<<endl;
            return temp;
        }
        struct coord data = elements[front];
        if(front == rear)
            front = rear = -1;
        else
            front = (front+1)%size;
        return data;
    }
};

int main()
{

    int sx, sy;
    int destx, desty;

    cin>>sx>>sy>>destx>>desty;

    swap(sx,sy);
    swap(destx, desty);
    struct queuee q(40);
    struct coord pos, temp;
    pos.x=sx;
    pos.y=sy;

    q.enqueue(pos);
    bool flag=false;
    while(!q.isEmpty() )
    {
        pos = q.dequeue();
        if(pos.x==destx && pos.y ==desty)
        {
            flag=true;
            break;
        }
        for(int i=0;i<4;i++)
        {
            if(isValid(pos.x + dx[i], pos.y + dy[i]))
            {
                maze[pos.x + dx[i]][pos.y + dy[i]]  = -1;
                temp.x = pos.x + dx[i];
                temp.y = pos.y + dy[i];
                q.enqueue(temp);
            }
        }
    }
    cout<<flag;
    return 0;
}
