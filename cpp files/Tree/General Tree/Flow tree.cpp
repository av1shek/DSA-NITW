
#include<bits/stdc++.h>
using namespace std;
typedef struct gtnode *gtptr;

struct gtnode
{
    char data;
    gtptr ns;   /// next sibling
    gtptr fc;   /// first child
    int time;
    gtnode()
    {
        ns = NULL;
        fc = NULL;
        time = 0;
    }
    gtnode(char k)
    {
        data = k;
        ns = NULL;
        fc = NULL;
        time = 0;
    }
};

bool comp(gtptr a, gtptr b)
{
    return a->time > b->time;
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

void assignTime(gtptr GT)
{
    if(GT == NULL)
        return;
    if(GT->fc == NULL)
    {
        GT->time = 0;
        return;
    }
    gtptr temp = GT->fc;

    vector<gtptr> vec;
    for(gtptr temp = GT->fc; temp; temp=temp->ns)
    {
        assignTime(temp);
        vec.push_back(temp);
    }
    sort(vec.begin(), vec.end(), comp);
    int timeReq = 0;
    int timeLeft = 0;
    for(auto i:vec)
    {
        if( (i->time +1) > timeLeft)
        {
            int temp = (i->time + 1 - timeLeft);
            timeLeft += temp;
            timeReq += temp;
        }
        timeLeft--;
    }
    GT->time = timeReq;
    return;
}

int main()
{
    gtptr GT = NULL;
    takeInput(GT);
    assignTime(GT);
    cout<<GT->time;
    return 0;
}


/// ABC.D.E..FG.H..JK.LP.Q..M.N...
