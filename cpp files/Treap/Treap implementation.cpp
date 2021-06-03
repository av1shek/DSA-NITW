#include<bits/stdc++.h>
using namespace std;
typedef struct trnode *trptr;

void takeInput(trptr &);           /// takes input till -1
void insert(trptr &, int);         /// insert a integer value
void printInorder(trptr);          /// print left, self , right

struct trnode
{
    struct trnode *lchild;
    char data;
    int pri;
    struct trnode *rchild;
    trnode()
    {
        lchild = NULL;
        rchild = NULL;
    }
    trnode(char k, int n)
    {
        lchild = NULL;
        data = k;
        pri = n;
        rchild = NULL;
    }
};

trptr rightR(trptr &T, char k)
{
    if(T==NULL || T->data==k)
    {
        trptr T2 = T->lchild;

        T->lchild = T2->rchild;
        T2->rchild = T;
        T = T2;
        return NULL;
    }
    if(k > T->data)
        return rightR(T->rchild, k);
    if(k < T->data)
        return rightR(T->lchild, k);
    return NULL;
}

trptr leftR(trptr &T, char k)
{
    if(T==NULL || T->data==k)
    {
        trptr T2 = T->rchild;

        T->rchild = T2->lchild;
        T2->lchild = T;
        T = T2;
        return NULL;
    }
    if(k > T->data)
        return leftR(T->rchild, k);
    if(k < T->data)
        return leftR(T->lchild, k);
    return NULL;
}

void insert(trptr &T, char k, int pri)
{
    if(T==NULL)
        T = new trnode(k, pri);
    else if(k > T->data)
    {
        insert(T->rchild, k, pri);
        if(T->rchild->pri > T->pri)
            leftR(T, T->data);
    }

    else if(k < T->data)
    {
        insert(T->lchild, k, pri);
        if(T->lchild->pri > T->pri)
            rightR(T, T->data);
    }

    return;
}


void printInorder(trptr T)
{
    if(T == NULL)
        return;
    printInorder(T->lchild);
    cout<<T->data<<" "<<T->pri<<" ";
    printInorder(T->rchild);
    return;
}



void Delete(trptr &T, int k)
{
    if(T==NULL)
        return;
    if(T->data == k)
    {
        if( (T->rchild==NULL) && (T->lchild==NULL) )
        {
            T = NULL;
            return;
        }

        if( (T->rchild==NULL) && (T->lchild!=NULL) )
        {
            T = T->lchild;
            return;
        }
        else if( (T->rchild!=NULL) && (T->lchild ==NULL) )
        {
            T = T->rchild;
            return;
        }
        else
        {
            trptr temp = ( T->lchild->pri < T->rchild->pri ) ? T->lchild : T->rchild;
            char ch = temp->data;
            int pri = temp->pri;
            Delete(T, temp->data);
            T->data = ch;
            T->pri = pri;
            return;
        }
    }
    if(T->data > k)
        Delete(T->lchild, k);
    else
        Delete(T->rchild, k);

}


void takeInput(trptr &T)
{
    while(true)
    {
        trptr temp = new trnode;
        cin>>temp->data;
        if(temp->data == '#')
            break;
        cin>>temp->pri;
        insert(T, temp->data, temp->pri);
    }
}

int main()
{
    trptr T = NULL;
    takeInput(T);
    printInorder(T); cout<<endl;
    char ch;
    cin>>ch; Delete(T, ch);
    cin>>ch; Delete(T, ch);
    printInorder(T);
    return 0;
}

