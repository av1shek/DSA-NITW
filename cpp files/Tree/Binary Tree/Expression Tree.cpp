#include<bits/stdc++.h>
using namespace std;
typedef struct etnode *etptr;

struct etnode
{
    etptr lchild;
    union
    {
        int oprnd;
        char oprtr;
    }data;
    int tag;    /// 0 - operand, 1 - operator
    etptr rchild;

    etnode()
    {
        lchild = NULL;
        rchild = NULL;
    }
};

bool isOperator(char ch)
{
    if( ch >= '0' && ch<= '9')
        return false;
    return true;
}

void takeInput(etptr &T, string str)
{
    stack<etptr> s;
    for(int i=0;i<str.size();i++)
    {
        etptr temp = new etnode;
        temp->tag = isOperator(str[i]);
        if(temp->tag == 0)
        {
            temp->data.oprnd = int( str[i] - '0' );
            s.push(temp);
        }
        else
        {
            temp->data.oprtr = str[i];
            temp->rchild = s.top(); s.pop();
            temp->lchild = s.top(); s.pop();
            s.push(temp);
        }
    }
    T = s.top();
    return;
}
void printInorder(etptr T)
{
    if(T == NULL)
        return;
    printInorder(T->lchild);
    if(T->tag)
        cout<<T->data.oprtr<<" ";
    else
        cout<<T->data.oprnd<<" ";
    printInorder(T->rchild);
    return;
}
int eval(int a, int b, char ch)
{
    if(ch == '+')
        return a+b;
    if(ch == '-')
        return a-b;
    if(ch == '*')
        return a*b;
    else
        return a/b;
}
int evaluate(etptr E)
{
    if(E->rchild==NULL && E->lchild==NULL)
        return E->data.oprnd;
    return eval( evaluate(E->lchild), evaluate(E->rchild), E->data.oprtr);
}
int main()
{
    string s = "231*+9-";
    etptr E = NULL;
    takeInput(E, s);
    printInorder(E);    cout<<endl;
    cout<<evaluate(E);
    return 0;
}
