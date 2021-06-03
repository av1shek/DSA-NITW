#include<iostream>
using namespace std;
typedef struct dlnode  *dlptr;

void insert(dlptr &, dlptr);                /// insert at last
void takeInput(dlptr &);                    /// takes input till -1
void print(dlptr);                          /// prints
int getSize(dlptr);                         /// return the length

struct ele
{
    int integer;
    char ch;
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
        cin>>temp->data.integer;
        if(temp->data.integer == -1)
            break;
        insert(DL, temp);
    }
    return;
}

void print(dlptr DL)
{
    while(DL!=NULL)
    {
        cout<<DL->data.integer<<" ";
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
