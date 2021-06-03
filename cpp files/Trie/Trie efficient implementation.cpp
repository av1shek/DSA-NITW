#include<bits/stdc++.h>
using namespace std;
typedef struct tnode *Tptr;

struct tnode
{
    union
    {
        Tptr ptr[27];
        char s[100];
    }data;
    int tag=0;
};

void printAll(Tptr T)
{
    if(T==NULL)
        return;
    if(T->tag==0)
        cout<<T->data.s<<" ";
    else if(T->tag==1)
        for(int i=0;i<27;i++)
            printAll(T->data.ptr[i]);
}
void insert(Tptr &T, string s, int index=0)
{
    if(T==NULL)
    {
        T = new tnode;
        T->tag = 0;
        int i;
        for(i=0;i<s.size();i++)
            T->data.s[i] = s[i];
        T->data.s[i] = '\0';
        return;
    }
    if(T->tag == 0)
    {
        Tptr temp = new tnode;
        temp->tag = 1;
        for(int i=0;i<=26;i++)
            temp->data.ptr[i] = NULL;
        int k = T->data.s[index] - 'A';
        temp->data.ptr[k] = T;
        T = temp;
        k = s[index] - 'A';
        if(index<s.size())
            insert(T->data.ptr[k], s, index+1);
        else
            insert(T->data.ptr[26], s, index+1);
    }
    else
    {
        int k = s[index] - 'A';
        if(index<s.size())
            insert(T->data.ptr[k], s, index+1);
        else
            insert(T->data.ptr[26], s, index+1);
    }
}

void takeInput(Tptr &T)
{
    while(true)
    {
        string s;   cin>>s;
        if(s == "#")
            break;
        insert(T, s);
    }
}
int main()
{
    Tptr T= NULL;
    int cnt = 3;
    while(cnt--)
    {
        takeInput(T);
        printAll(T); cout<<endl;
    }

    return 0;
}
