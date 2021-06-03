// Life is a heap of problems
// Love them as possibilities
#include<bits/stdc++.h>
using namespace std;

typedef struct qtnode *qtptr;

struct qtnode
{
    int data;
    qtptr cptr[4];
    qtnode()
    {
        for(int i=0;i<4;i++)
            cptr[i] = NULL;
    }
    qtnode(int k)
    {
        data = k;
        for(int i=0;i<4;i++)
            cptr[i] = NULL;
    }

};


void printLevelOrder(qtptr H)
{
    if(H==NULL)
        return;
    queue<qtptr> q;
    q.push(H);

    while(!q.empty())
    {
        int n = q.size();
        for(int i=0;i<n;i++)
        {
            qtptr temp = q.front(); q.pop();

            cout<<temp->data<<" ";
            for(int j=0; (j<4) && (temp->cptr[j]);j++)
                q.push(temp->cptr[j]);
        }
        cout<<endl;
    }
}


void heapifyUtils(qtptr H, stack<int> &s)
{
    if(H==NULL || s.empty()==true)
        return;
    int index = s.top(); s.pop();
    heapifyUtils(H->cptr[index], s);
    if( H->data > H->cptr[index]->data)
        swap( H->data , H->cptr[index]->data);

    return;
}
void heapify(qtptr &H, int size)
{
    if(H==NULL)
        return;
    if(size==0) return;
    stack<int> s;
    while(size)
    {
        s.push( (size - 1)%4 );
        size = (size - 1)/4;
    }
    heapifyUtils(H, s);
    return;
}


void insert(qtptr &H, qtptr &root, int k, queue<qtptr> &q, int &size)
{
    if(H==NULL)
    {
        H = new qtnode(k);
        heapify(root, size);
        size++;
        q.push(H);
        return;
    }

    qtptr temp = q.front();

    int i;
    for( i=0;i<4;i++)
    {
        if(temp->cptr[i] == NULL)
        {
            insert(temp->cptr[i], root, k, q, size);
            break;
        }

    }
    if(i == 3)
        q.pop();


    return;
}

void takeInput(qtptr &H)
{
    queue<qtptr> q;
    int size = 0;
    while(true)
    {
        int temp;
        cin>>temp;

        if(temp == -1 )
            break;

        insert(H, H, temp, q, size);
    }
}

int main()
{
    qtptr H = NULL;
    takeInput(H);
    printLevelOrder(H);
    return 0;
}

/// 9 5 12 3 10 6 8 14 11 4 7 1 13 15 2 -1
