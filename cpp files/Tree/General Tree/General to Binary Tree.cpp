#include<bits/stdc++.h>
using namespace std;
typedef struct gtnode *gtptr;

struct gtnode
{
    char data;
    gtptr ns;   /// next sibling
    gtptr fc;   /// first child
    bool visited;

    gtnode()
    {
        ns = NULL;
        fc = NULL;
        visited = false;
    }
    gtnode(char k)
    {
        data = k;
        ns = NULL;
        fc = NULL;
        visited = false;
    }
};


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

bool printDFS(gtptr GT)
{
    if(GT == NULL)
        return true;
    cout<<GT->data;

    gtptr temp = GT->fc;
    while(temp && temp->visited)
        temp = temp->ns;

    int i=0;
    bool res = true;
    for( i=0; (i<2) &&(temp); temp=temp->ns)
    {
        if(!temp->visited)
        {
           printDFS(temp);
           i++;
        }
    }

    if(i==0)
        cout<<"..";
    else if(i==1)
        cout<<".";

    if(temp==NULL)
        GT->visited = true;
    return GT->visited;
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

int main()
{
    gtptr GT = NULL;
    takeInput(GT);
    while(!GT->visited)
    {
        printDFS(GT);
        cout<<endl;
    }
    return 0;
}


/// ABC.D.E..FG.H..JK.LP.Q..M.N...

