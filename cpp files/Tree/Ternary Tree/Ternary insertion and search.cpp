#include<bits/stdc++.h>
using namespace std;
typedef struct trnode *trptr;       /// ternary ptr

void takeInput(trptr &);           /// takes input
void insert(trptr &, int);         /// insert value
void printInorder(trptr);          /// print left, self , right

struct trnode
{
    trptr lchild;
    char data;
    bool flag;  /// represent end of word
    trptr eq;
    trptr rchild;
    trnode()
    {
        lchild = NULL;
        eq =NULL;
        rchild = NULL;
        flag = false;
    }
    trnode(char k)
    {
        lchild = NULL;
        rchild = NULL;
        eq = NULL;
        data = k;
        flag = false;
    }
};

trptr createNewNode(string s, int index)
{
    if(index >= s.size())
        return NULL;
    trptr T = new trnode(s[index]);
    if(index == s.size()-1)
        T->flag = true;
    T->eq = createNewNode(s, index+1);
    return T;
}
void insert(trptr &T, string s, int index)
{
    if(index >= s.size())
        return;
    if(T==NULL)
        T = createNewNode(s, index);
    else if(s[index] > T->data)
        insert(T->rchild, s, index);
    else if(s[index] < T->data)
        insert(T->lchild, s, index);
    else
    {
        if(index == s.size()-1)
            T->flag = true;
        insert(T->eq, s, index+1);
    }

    return;
}

void printInorder(trptr T)
{
    if(T == NULL)
        return;
    cout<<T->data<<" ";
    printInorder(T->lchild);
    printInorder(T->eq);
    printInorder(T->rchild);
    return;
}

void printPreorder(trptr T)
{
    if(T==NULL)
        return;
    cout<<T->data<<" ";
    printPreorder(T->lchild);
    printPreorder(T->rchild);
    return;
}


void takeInput(trptr &T)
{
    int cnt = 4;
    while(cnt--)
    {
        string temp;
        cin>>temp;
        insert(T, temp, 0);
    }
}

bool find(trptr T, string s, int index)
{
    if( (T==NULL) || (index >=s.size() ) )
        return false;

    if(s[index] > T->data)
        return find(T->rchild, s, index);
    else if(s[index] < T->data)
        return find(T->lchild, s, index);
    else
    {
        if(index == s.size() - 1)
            return T->flag;
        return find(T->eq, s , index+1);
    }
}

int main()
{
    trptr T = NULL;
    takeInput(T);
    string s;
    cin>>s; cout<<find(T, s, 0)<<" ";
    cin>>s; cout<<find(T, s, 0)<<" ";
    return 0;
}
