#include<bits/stdc++.h>
using namespace std;
typedef struct mtnode *mtptr;
int M;
struct mtnode
{
    int cnt;
    int *keys = new int[M];
    mtptr *cptr = new mtptr[M];

    mtnode()
    {
        for(int i=0;i<M;i++)
            cptr[i] = NULL;
        cnt = 0;
    }
};


void insert(mtptr &T, int k)
{
    if(T==NULL)
    {
        T = new mtnode;
        T->keys[0] = k;
        T->cnt++;
        return;
    }

    if(T->cnt < M-1)
    {
        int i = T->cnt;
        T->keys[i] = k;
        T->cnt++;
        while(i>0)
        {
            if(T->keys[i] < T->keys[i-1])
                swap(T->keys[i], T->keys[i-1]);
            else
                break;
            i--;
        }
        return;
    }

    for(int i=0;i<T->cnt;i++)
    {
        if(k < T->keys[i])
        {
            insert(T->cptr[i], k);
            return;
        }
    }
    insert(T->cptr[T->cnt], k);
}

void constructInorder(mtptr &T, vector<int> &v, int low, int high)
{
    if(high<low)
        return;
    T = new mtnode;
    int batchSize = (high-low + 2 - M)/M;
    int i;
    for(i=0;i<M-1;i++)
    {
        constructInorder(T->cptr[i], v, low + i*batchSize + i, low + i*batchSize + i + batchSize - 1);
        T->keys[i] = v[low + i*batchSize + i + batchSize];
    }
    constructInorder(T->cptr[i], v, low + i*batchSize + i, low + i*batchSize + i + batchSize - 1);
}

void takeInput(mtptr &T)
{
    vector<int> v;
    while(true)
    {
        int temp;
        cin>>temp;
        if(temp == -1)
            break;
        v.push_back(temp);
    }
    constructInorder(T, v, 0, v.size()-1);
}




void printLevelOrder(mtptr T)
{
    if(T==NULL)
        return;
    queue<mtptr> q;
    q.push(T);

    while(!q.empty())
    {
        int n = q.size();
        for(int i=0;i<n;i++)
        {
            mtptr temp = q.front(); q.pop();

            for(int j=0;j<M-1;j++)
                cout<<temp->keys[j]<<" ";

            for(int j=0;j<M;j++)
                if(temp->cptr[j])
                    q.push(temp->cptr[j]);
        }
        cout<<endl;
    }
}



int main()
{
    cin>>M;
    mtptr MT = NULL;
    takeInput(MT);
    printLevelOrder(MT);
    return 0;
}

/// 3 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 -1
