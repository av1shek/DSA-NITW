#include<iostream>
using namespace std;

typedef struct bstnode *bstptr;
typedef struct lnode *lptr;

/// ----------using the linked list defined in question 1 --------------------------

struct lnode
{
    int data;
    struct lnode *next;
    lnode(){next=NULL;}
};

void linsert(lptr &P, int x)
{
    lptr temp = new lnode;
    temp->data = x;
    if(P == NULL) P = temp;
    else
    {
        lptr T = P;
        while(T->next != NULL)
            T = T->next;
        T->next = temp;
    }
}

void ltakeinput(lptr &L)
{
    int x;
    cin>>x;
    while(x!= -1)
    {
        linsert(L, x);
        cin>>x;
    }
}

/// ----------- end of linked list definition used in question 1 ----------

struct bstnode
{
    struct bstnode *lchild;
    lptr data;
    int d;
    struct bstnode *rchild;
    bstnode()
    {
        lchild=NULL; rchild=NULL; data=NULL;
    }

    bstnode(lptr k, int d)
    {
        lchild = NULL;
        this->d = d;
        data = NULL;
        while( k!=NULL)
        {
            linsert(data, k->data);
            k = k->next;
        }
    }

};

int value(lptr L, int n)
{
    for(int i=0;i<n;i++)
        L = L->next;
    return L->data;
}

void insert(bstptr &T, lptr k, int d, int n)
{
    if(T==NULL)
        T = new bstnode(k, d);
    else if( value(k, n%d) > value(T->data, n%d) )
        insert(T->rchild, k, d, n+1);
    else if( value(k, n%d) < value(T->data, n%d) )
        insert(T->lchild, k, d, n+1);
}

void takeInput(bstptr &T, int d)
{
    while(true)
    {
        lptr temp = NULL, temp2 = new lnode;
        for(int i=0;i<d;i++)
        {
            cin>>temp2->data;
            if(temp2->data == -1) break;
            linsert(temp, temp2->data);
        }
        if(temp2->data == -1) break;
        insert(T, temp, d, 0);
    }
}

void printNode(bstptr node)
{
    if(node == NULL) return;
    lptr temp = node->data;
    while(temp!=NULL)
    {
        cout<<temp->data<<" ";
        temp = temp->next;
    }
    cout<<endl;
}


void printInorder(bstptr T)
{
    if(T==NULL) return;
    printInorder(T->lchild);
    printNode(T);
    printInorder(T->rchild);
    return;
}

int main()
{
    int d;
    cin>>d;
    bstptr T = NULL;
    takeInput(T, d);
    printInorder(T);
    return 0;
}
