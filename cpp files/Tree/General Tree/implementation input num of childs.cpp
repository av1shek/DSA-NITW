#include<bits/stdc++.h>
using namespace std;
typedef struct gtnode *gtptr;

struct gtnode
{
    char data;
    gtptr ns;   /// next sibling
    int nc;     /// number of child
    gtptr fc;   /// first child

    gtnode()
    {
        ns = NULL;
        fc = NULL;
    }
    gtnode(char k, int cnt)
    {
        data = k;
        nc = cnt;
        ns = NULL;
        fc = NULL;
    }
};

void takeInput(gtptr &GT)
{

    GT = new gtnode;
    cin>>GT->data>>GT->nc;
    int cnt = GT->nc;

    if(cnt != 0)
    {
        takeInput(GT->fc);
        cnt--;
    }

    gtptr temp = GT->fc;
    while(cnt--)
    {
        takeInput(temp->ns);
        temp = temp->ns;

    }
    return;
}


string serializeUtils(gtptr GT, string s)
{
    if(GT==NULL)
        return s;

    s += GT->data;      /// ----- if data is integer then typecast it
    gtptr temp = GT->fc;

    for(gtptr temp = GT->fc; temp; temp=temp->ns)
        s = serializeUtils(temp, s);
    s+='.';
    return s;
}


string serialize(gtptr GT)
{
    string s = "";
    return (serializeUtils(GT, s) + ".");
}

int main()
{
    gtptr GT = NULL;
    takeInput(GT);
    cout<<serialize(GT);
}


