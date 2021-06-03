#include <bits/stdc++.h>
using namespace std;
typedef struct node  *lptr;

struct node
{
    int data;
    struct node *next;
    node()
    {
        next=NULL;
    }
};

void insert(lptr &P, int x)
{
    lptr temp = new node;
    temp->data = x;

    if(P==NULL)
        P = temp;
    else
    {
        lptr T = P;
        while(T->next != NULL)
            T = T->next;
        T->next = temp;
    }

    return;
}

void takeInput(lptr &L)
{
    int n;
    cin>>n;
    while(n!=-1)
    {
        insert(L, n);
        cin>>n;
    }
    return;
}


void print(lptr L)
{
    while(L!=NULL)
    {
        cout<<L->data<<" ";
        L = L->next;
    }
    return;
}
lptr find(lptr L, int x)
{
    if(L==NULL)
        return L;
    while(L!=NULL)
    {
        if(L->data == x)
            return L;
        L = L->next;
    }
    return L;
}

int getSize(lptr L)
{
    int i=0;
    while(L!=NULL)
    {
        i++;
        L = L->next;
    }
    return i;
}

bool isAllFalse(bool a[], int n)
{
    for(int i=1;i<n;i++)
        if(a[i]) return false;
    return true;
}

void prints(bool meets[], int n, int curr, int prev)
{
    cout<<curr+1<<" ";
    for(int i=0;i<n;i++)
    {
        if(meets[i]==false || i==curr) continue;
        cout<<i+1<<" ";
    }
    cout<<prev<<endl;
}
void getAllIntersection(lptr L[], int n )
{
    stack<int> s[n];
    bool meets[n]; memset(meets, true, sizeof(meets));
    for(int i=0;i<n;i++)
    {
        while(L[i]!=NULL)
        {
            s[i].push(L[i]->data);
            L[i] = L[i]->next;
        }
    }

    int curr = s[0].top();
    int prev = curr;
    while(!isAllFalse(meets, n))
    {
        int temp[n];
        curr = s[0].top(); s[0].pop();

        for(int i=1;i<n;i++)
        {
            if(s[i].empty() || meets[i]==false) continue;
            temp[i] = s[i].top(); s[i].pop();

            if(temp[i] != curr )
            {
                meets[i] = false;
                prints(meets,n, i, prev);
            }
        }
        prev = curr;
    }
}

int main()
{
    int n =4;
    lptr L[n];
    for(int i=0;i<n;i++) L[i] = NULL;
    takeInput(L[0]);
    for(int i=1;i<n;i++)
    {
        int temp;
        while(true)
        {
            cin>>temp;
            if(temp==-1) break;
            if(find(L[0], temp))
            {
                lptr it = L[i];
                while(it->next!=NULL) it = it->next;
                it->next = find(L[0], temp);
            }
            else
                insert(L[i], temp);

        }
    }

    getAllIntersection(L, n);

    return 0;
}


