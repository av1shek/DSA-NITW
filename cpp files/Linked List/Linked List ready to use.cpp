#include <bits/stdc++.h>
using namespace std;
typedef struct mlnode *mlptr;


struct mlnode
{
    int tag;    // 0 normal, 1-set
    int data;
    mlptr next;
    mlptr dlink;
    mlnode()
    {
        next = NULL;
        dlink = NULL;
    }
    mlnode(const mlnode &x)
    {
        tag = x.tag;
        data = x.data;
        next = x.next;
        dlink = x.dlink;
    }
};

void printDepth(mlptr ML)
{
    while(ML!=NULL)
    {
        cout<<ML->data<<" ";
        if(ML->tag==1)
            printDepth(ML->dlink);
        ML = ML->next;
    }
    return;
}

void printLevel(mlptr ML)
{
    queue<mlptr> q;
    q.push(ML);
    while(!q.empty())
    {
        mlptr temp = q.front();
        q.pop();
        while(temp!=NULL)
        {
            cout<<temp->data<<" ";
            if(temp->tag == 1)
                q.push(temp->dlink);
            temp = temp->next;
        }
    }
    return;
}

void insert(mlptr &P, struct mlnode x)
{
    mlptr temp = new mlnode(x);

    if(P==NULL)
        P = temp;
    else
    {
        mlptr T = P;
        while(T->dlink != NULL)
           T = T->dlink;
        T->dlink = temp;
    }
    return;
}

void takeInput(mlptr &ML)
{
    while(true)
    {
        struct mlnode temp;
        cin>>temp.data;
        if(temp.data==-1)
            break;
        cin>>temp.tag;
        if(temp.tag==1)
        {
            takeInput(temp.next);
        }
        insert(ML, temp);
    }
    return;
}
void solve(mlptr ML)
{
    if(ML==NULL)
        return;

    solve(ML->dlink);
    solve(ML->next);
    mlptr temp = ML->dlink;
    ML->dlink = ML->next;
    ML->next = temp;
}
int main()
{
    mlptr ML = NULL;
    takeInput(ML);
    //solve(ML);
    printLevel(ML); cout<<endl;
    printDepth(ML);
    return 0;
}

