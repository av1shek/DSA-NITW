#include<bits/stdc++.h>
using namespace std;
typedef struct mstnode *mstptr;
int M;
struct mstnode
{
    int cnt;
    int *keys = new int[M];
    mstptr *cptr = new mstptr[M];

    mstnode()
    {
        for(int i=0;i<M;i++)
            cptr[i] = NULL;
        cnt = 0;
    }
};


void insert(mstptr &T, int k)
{
    if(T==NULL)
    {
        T = new mstnode;
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
void takeInput(mstptr &T)
{
    while(true)
    {
        int temp;
        cin>>temp;
        if(temp == -1)
            break;
        insert(T, temp);
    }
}

void printInorder(mstptr T)
{
    if(T==NULL)
        return;
    for(int i=0;i<T->cnt;i++)
    {
        printInorder(T->cptr[i]);
        cout<<T->keys[i]<<" ";
    }
    printInorder(T->cptr[T->cnt]);
}

void printPreorderBlock(mstptr T)
{
    if(T==NULL)
        return;
    cout<< "[ ";
    for(int i=0;i<T->cnt;i++)
        cout<<T->keys[i]<<" ";
    cout<<"] ";
    for(int i=0;i<=T->cnt;i++)
        printPreorderBlock(T->cptr[i]);

}

void printLevelOrder(mstptr T)
{
    if(T==NULL)
        return;
    queue<mstptr> q;
    q.push(T);

    while(!q.empty())
    {
        int n = q.size();
        for(int i=0;i<n;i++)
        {
            mstptr temp = q.front(); q.pop();
            cout<< "[ ";
            for(int j=0;j<temp->cnt;j++)
                cout<<temp->keys[j]<<" ";
            cout<<"]  ";

            for(int j=0;j<=temp->cnt;j++)
            {
                if(temp->cptr[j])
                    q.push(temp->cptr[j]);
            }
        }
        cout<<endl;
    }
}

mstptr find(mstptr T, int k)
{
    if(T==NULL)
        return T;
    for(int i=0;i<T->cnt;i++)
        if(T->keys[i] == k)
            return T;
    for(int i=0;i<=T->cnt;i++)
    {
        mstptr temp = find(T->cptr[i], k);
        if(temp)
            return temp;
    }
    return NULL;
}

void Delete(mstptr &T, int k)
{
    if(T==NULL)
        return;
    mstptr temp = find(T, k);
    int i=0;
    for(i=0;i<temp->cnt;i++)
        if(temp->keys[i]==k)
            break;

    if( (temp->cptr[i] == NULL) &&  (temp->cptr[i+1] == NULL) )
    {
        for( ; i< (temp->cnt - 1); i++)
            temp->keys[i] = temp->keys[i+1];
        temp->cnt--;
        return;
    }
    else if(temp->cptr[i+1] == NULL)
    {
        temp->keys[i] = temp->cptr[i]->keys[temp->cptr[i]->cnt - 1];
        Delete(temp->cptr[i], temp->keys[i]);
    }
    else //if(temp->cptr[i] == NULL)
    {
        temp->keys[i] = temp->cptr[i+1]->keys[0];
        Delete(temp->cptr[i+1], temp->keys[i]);
    }


}

int main()
{
    mstptr MT = NULL;
    takeInput(MT);
    printInorder(MT);   cout<<endl;
    printPreorderBlock(MT); cout<<endl;
    printLevelOrder(MT);
    return 0;
}

/// 18 36 45 20 25 40 9 22 42 41 90 -1
