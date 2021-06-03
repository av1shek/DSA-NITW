#include<bits/stdc++.h>
using namespace std;
typedef struct gtnode *gtptr;

struct gtnode
{
    char data;
    int x;
    int cc;     /// child count
    gtptr ns;   /// next sibling
    gtptr fc;   /// first child

    gtnode()
    {
        cc = 0;
        ns = NULL;
        fc = NULL;
    }
    gtnode(char k)
    {
        cc = 0;
        data = k;
        ns = NULL;
        fc = NULL;
    }
};

int getChildCount(gtptr GT)
{
    gtptr temp = GT->fc;
    int i=0;
    while(temp!=NULL)
    {
        i++;
        temp = temp->ns;
    }
    return i;
}
void print(gtptr temp)
{
    for(int i=1;i<=temp->x; i++)
        cout<<setw(2)<<" ";
    if(temp->data!= '@')
        cout<<setw(2)<<temp->data;
    else
        cout<<setw(2)<<" ";
}

void printLevel(gtptr GT)
{
    queue<gtptr> q;
    q.push(GT);
    gtptr temp = new gtnode;
    temp->data = '#';
    q.push(temp);
    int pos = 0;
    while(!q.empty())
    {
        temp = q.front(); q.pop();
        temp->x -= (pos);
        pos += temp->x+1;
        print(temp);
        gtptr child = temp->fc;
        while(child != NULL)
        {
            q.push(child);
            child = child->ns;
        }

        if( q.front()->data=='#')
        {
            gtptr temp2 = q.front(); q.pop();
            cout<<endl<<endl;
            pos=0;
            if(!q.empty())
                q.push(temp2);
        }
    }
}



int inputChilds(gtptr &GT)
{
    gtptr temp = new gtnode;
    cin>>temp->data;

    if(temp->data == '.')
        return 0;

    GT = new gtnode(temp->data);
    gtptr P = GT;
    GT->cc = inputChilds(GT->fc);

    cin>>temp->data;
    int cnt =1;
    while(temp->data != '.')
    {
        P->ns = new gtnode(temp->data);
        P = P->ns;
        P->cc = inputChilds(P->fc);
        cin>>temp->data;
        cnt++;
    }
    return cnt;
}

void takeInput(gtptr &GT)
{
    GT = new gtnode;
    cin>>GT->data;
    GT->cc = inputChilds(GT->fc);
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


int getHeight(gtptr GT)
{
    if(GT==NULL)
        return 0;
    int h = 0;
    for(gtptr temp = GT->fc; temp; temp=temp->ns)
        h =  max(h, getHeight(temp));
    return h + 1;
}

void inorderIndex(gtptr GT, int &i, int &maxCC)
{
    if(GT==NULL)
        return;
    gtptr temp = GT->fc;
    int j=0;
    GT->cc = getChildCount(GT);
    if(GT->cc %2 == 0)
    {
        for( ;j<(GT->cc/2);j++)
        {
            inorderIndex(temp, i, maxCC);
            temp = temp->ns;
        }
        GT->x = i++;
        maxCC = max(maxCC, GT->cc);
        //cout<<GT->data<<"("<<GT->x<<")"<<" ";
        for(; j<GT->cc; j++)
        {
            inorderIndex(temp, i, maxCC);
            temp = temp->ns;
        }
    }
    else
    {
        for( ;j<( (GT->cc +1) /2);j++)
        {
            inorderIndex(temp, i, maxCC);
            temp = temp->ns;
        }
        GT->x = i++;
        maxCC = max(maxCC, GT->cc);
        //cout<<GT->data<<"("<<GT->x<<")"<<" ";
        for(; j<GT->cc; j++)
        {
            inorderIndex(temp, i, maxCC);
            temp = temp->ns;
        }
    }

}

void completeTree(gtptr &GT, int currH, int height, int maxCC)
{
    if(currH == height)
    {
        if(GT == NULL)
            GT = new gtnode('@');
        return;
    }

    GT->cc = maxCC-1;
    if(GT->fc == NULL)
        GT->fc = new gtnode('@');
    gtptr temp = GT->fc;

    for(int i=0;i<maxCC;i++, temp=temp->ns)
    {
        if(temp == NULL)
            temp = new gtnode('@');

    }


    for(temp = GT->fc; temp; temp=temp->ns)
        completeTree(temp, currH+1, height, maxCC);
    return;
}


void draw(gtptr GT)
{
    int i=0;
    int maxCC =4;  /// ----------- to be changed
    int height = getHeight(GT);
    completeTree(GT, 0, height, maxCC);
    inorderIndex(GT, i, maxCC);
    printLevel(GT);
}

int main()
{
    int i=0;
    gtptr GT = NULL;
    takeInput(GT);
    draw(GT); cout<<endl;
    return 0;
}


/// ABC.D.E..FG.H..JK.LP.Q..M.N...
