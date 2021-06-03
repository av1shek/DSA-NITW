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
    string frontItem()
    {
        return elements[front];
    }
};

bool isOperator(string ch)
{
    if(ch=="+" || ch=="*" || ch=="-" || ch=="/" )
        return true;
    else
        return false;
}

string eval(float oprnd1, float oprnd2, string oprtr)
{
    if(oprtr == "+")
        return to_string(oprnd1+oprnd2);
    else if(oprtr == "-")
        return to_string(oprnd1-oprnd2);
    else if(oprtr == "*")
        return to_string(oprnd1*oprnd2);
    else
        return to_string(oprnd1/oprnd2);
}
float stringToNum(string s)
{
    stringstream str(s);
    float num;
    str>>num;
    return num;
}

int main()
{
    string infixStr = "-+*9+28*+4863";
    string temp, oprtr, oprnd1, oprnd2;
    struct queuee q(50);

    /// pushing all elements to queue
    for(int i=0;i<infixStr.size();i++)
    {
        temp = "";
        temp += infixStr[i];
        q.enqueue(temp);
    }

    /// algorithm starts here
    while(true)
    {
        temp = q.dequeue();
        if(q.isEmpty())
            break;
        while( !isOperator(temp) )
        {
            q.enqueue(temp);
            temp = q.dequeue();
        }

        oprtr = temp;
        oprnd1 = q.dequeue();
        oprnd2 = q.dequeue();

        while(!(isOperator(oprtr)&&(!isOperator(oprnd1))&&(!isOperator(oprnd2))))
        {
            q.enqueue(oprtr);
            oprtr = oprnd1;
            oprnd1 = oprnd2;
            oprnd2 = q.dequeue();
        }

        float num1 = stringToNum(oprnd1);
        float num2 = stringToNum(oprnd2);
        q.enqueue(eval(num1, num2, oprtr));

    }
    cout<<int(stringToNum(temp));
    return 0;
}
