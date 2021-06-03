#include<bits/stdc++.h>
using namespace std;
typedef struct gtnode *gtptr;

struct gtnode
{
    char data;
    gtptr ns;   /// next sibling
    gtptr fc;   /// first child

    gtnode()
    {
        ns = NULL;
        fc = NULL;
    }
    gtnode(char k)
    {
        data = k;
        ns = NULL;
        fc = NULL;
    }
};

void printLevel(gtptr GT)
{
    queue<gtptr> q;
    q.push(GT);
    gtptr temp = new gtnode;
    temp->data = '#';
    q.push(temp);
    while(!q.empty())
    {
        temp = q.front(); q.pop();
        cout<<temp->data<<" ";
        gtptr child = temp->fc;
        while(child != NULL)
        {
            q.push(child);
            child = child->ns;
        }

        if( q.front()->data=='#')
        {
            gtptr temp2 = q.front(); q.pop();
            cout<<endl;
            if(!q.empty())
                q.push(temp2);
        }
    }
}



void inputChilds(gtptr &GT)
{
    gtptr temp = new gtnode;
    cin>>temp->data;

    if(temp->data == '.')
        return;

    GT = new gtnode(temp->data);
    gtptr P = GT;
    inputChilds(GT->fc);

    cin>>temp->data;
    while(temp->data != '.')
    {
        P->ns = new gtnode(temp->data);
        P = P->ns;
        inputChilds(P->fc);
        cin>>temp->data;
    }
}

void takeInput(gtptr &GT)
{
    GT = new gtnode;
    cin>>GT->data;
    inputChilds(GT->fc);
}

void printDFS(gtptr GT)
{
    if(GT == NULL)
        return;
    cout<<GT->data<<" ";
    gtptr temp = GT->fc;

    for(gtptr temp = GT->fc; temp; temp=temp->ns)
        printDFS(temp);
}

string serialize(gtptr GT, string s="")
{
    if(GT==NULL)
        return s;

    s += GT->data;      /// ----- if data is integer then typecast it
    gtptr temp = GT->fc;

    for(gtptr temp = GT->fc; temp; temp=temp->ns)
        s = serialize(temp, s);
    s+='.';
    return s;
}

void printWithBraces(gtptr GT)
{
    if(GT == NULL)
        return;
    cout<<GT->data;
    gtptr temp = GT->fc;

    if(temp==NULL)
        return;

    cout<<"(";
    for(gtptr temp = GT->fc; temp; temp=temp->ns)
        printWithBraces(temp);
    cout<<")";
}


int main()
{
    gtptr GT = NULL;
    takeInput(GT);
    printLevel(GT);
    return 0;
}


/// ABC.D.E..FG.H..JK.LP.Q..M.N...
