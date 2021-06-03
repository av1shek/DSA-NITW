#include<iostream>
using namespace std;
typedef struct dlnode  *dlptr;

void insert(dlptr &, dlptr);                /// insert at last
void takeInput(dlptr &);                    /// takes input till -1
void print(dlptr);                          /// prints
int getSize(dlptr);                         /// return the length

union U
{
    int integer;
    char ch;
};
struct ele
{
    int tag;
    union U val;
};
struct dlnode
{
    dlptr left;
    struct ele data;
    dlptr right;
    dlnode()
    {
        left=NULL;
        right=NULL;
    }
};

void insert(dlptr &DL, dlptr x)
{

    if(DL==NULL)
        DL = x;
    else
    {
        dlptr T = DL;
        while( T->right != NULL)
            T = T->right;

        T->right = x;
        x->left = T;
    }
    return;
}

void takeInput(dlptr &DL)
{
    while(true)
    {
        dlptr temp = new dlnode;
        cin>>temp->data.tag;

        if(temp->data.tag == -1)
            break;
        if(temp->data.tag == 0)
            cin>>temp->data.val.integer;
        else
            cin>>temp->data.val.ch;
        insert(DL, temp);
    }
    return;
}

void print(dlptr DL)
{
    while(DL!=NULL)
    {
        if(DL->data.tag == 0)
            cout<<DL->data.val.integer<<" ";
        else
            cout<<DL->data.val.ch<<" ";

        DL = DL->right;
    }
    return;
}


int getSize(dlptr DL)
{
    int count=0;
    while(DL!=NULL)
    {
        count++;
        DL = DL->right;
    }
    return count;
}

int main()
{
    dlptr DL = NULL;
    int k, x, y;

    takeInput(DL);

    print(DL);


    return 0;
}
