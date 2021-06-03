#include<bits/stdc++.h>
using namespace std;
typedef struct tnode *Tptr;
char ch = 1;
struct tnode
{
    bool wrd;
    Tptr ptr[256];

    tnode()
    {
        wrd = false;
        for(int i=0;i<256;i++)
            ptr[i]= NULL;
    }
};

bool find(Tptr T, string s, int index = 0)
{
    if(T==NULL)
        return false;
    if(index == s.size())
        return T->wrd;
    int k = s[index] - ch;
    return find(T->ptr[k], s, index+1);
}


void printAll(Tptr T, string s = "")
{
    if(T==NULL)
        return;
    if(T->wrd)
        cout<<s<<" ";
    for(int i=0;i<256;i++)
    {
        string temp = s + char( ch + i);
        printAll(T->ptr[i], temp);
    }
    return;
}

void insert(Tptr &T, string s, int index)
{
    if(index > s.size())
        return;
    if(index == s.size())
    {
        T->wrd = true;
        return;
    }
    int k = s[index] - ch;
    if(T->ptr[k]==NULL)
        T->ptr[k] = new tnode;

    insert(T->ptr[k], s, index+1);
    return;
}

void takeInput(Tptr &T)
{
    int cnt = 5;
    while(cnt--)
    {
        string s;   cin>>s;
        insert(T, s, 0);
    }
    return;
}

void printContainingPrefix(Tptr T, string s)
{
    int i=0;
    while(i!=s.size())
    {
        if(T==NULL)
            return;
        int k = s[i] - ch;
        T = T->ptr[k];
        i++;
    }
    printAll(T, s);
    return;
}

int main()
{
    Tptr T = new tnode;
    takeInput(T);
    printAll(T);

    return 0;
}


