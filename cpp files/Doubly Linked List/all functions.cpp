#include<iostream>
using namespace std;
typedef struct dlnode  *dlptr;

void insert(dlptr &, dlptr);                /// insert at last
void insertSorted(dlptr &, dlptr);          /// insert in sorted order
void bubbleSort(dlptr);                     /// bubble sort
void takeInput(dlptr &);                    /// takes input till -1
void print(dlptr);                          /// prints
void printReverse(dlptr);                   /// prints reverse
int getSize(dlptr);                         /// return the length
void DeleteFront(dlptr &);                  /// deletes front element
void DeleteLast(dlptr &);                   /// deletes last element
void Delete(dlptr &, int);                  /// deletes first occurrence
void addFront(dlptr &, int);
void addBefore(dlptr &, int, int);
void addAfter(dlptr &, int, int);
void swap(dlptr, dlptr);



struct dlnode
{
    dlptr left;
    int data;
    dlptr right;
    dlnode()
    {
        left=NULL;
        right=NULL;
    }
    dlnode(int k)
    {
        left=NULL;
        data = k;
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
        {
            T = T->right;
        }

        T->right = x;
        x->left = T;
    }
    return;
}


void insertSorted(dlptr &DL, dlptr x)
{

    if(DL==NULL)
        DL = x;
    else if(DL->data >= x->data)
    {
        x->right = DL;
        DL->left = x;
        DL = x;
        return;
    }
    else
    {
        dlptr T = DL;

        while( (T->data <= x->data) && ( T->right != NULL) )
        {
            T = T->right;
        }
        if(T->right == NULL)
        {
            if(T->data > x->data)
            {
                x->right = T;
                x->left = T->left;
                T->left->right = x;
                T->left = x;
            }
            else
            {
                T->right = x;
                x->left = T;
            }

        }
        else
        {
            x->right = T;
            x->left = T->left;

            T->left->right = x;
            T->left = x;
        }
    }
    return;
}


void takeInput(dlptr &DL)
{

    while(true)
    {
        dlptr temp = new dlnode;
        cin>>temp->data;
        if(temp->data == -1)
            break;
        insert(DL, temp);
    }
    return;
}

void print(dlptr DL)
{
    while(DL!=NULL)
    {
        cout<<DL->data<<" ";
        DL = DL->right;
    }
    return;
}

void printReverse(dlptr DL)
{
    if(DL==NULL)
        return;
    while(DL->right!=NULL)
        DL = DL->right;
    while(DL!=NULL)
    {
        cout<<DL->data<<" ";
        DL = DL->left;
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

void DeleteFront(dlptr &DL)
{
    if(DL==NULL) return;
    DL = DL->right;
    if(DL!=NULL)
        DL->left=NULL;
    return;
}


void DeleteLast(dlptr &DL)
{
    if(DL->right==NULL)
    {
        DL = NULL;
        return ;
    }
    dlptr T = DL;
    while(T->right != NULL)
    {
        T = T->right;
    }
    T->left->right = NULL;
    return ;
}


void Delete(dlptr &DL, int k)
{
    if(DL==NULL) return;
    if(DL->data == k)
    {
        DeleteFront(DL);
        return;
    }
    dlptr T = DL;
    while( (T!=NULL) && (T->data != k) )
        T = T->right;

    if(T==NULL)
        return;
    if(T->right!=NULL)
        T->right->left = T->left;
    T->left->right = T->right;
    return;
}

void addFront(dlptr &DL, int k)
{
    dlptr temp = new dlnode(k);
    if(DL==NULL)
    {
        DL = temp;
        return;
    }
    temp->right = DL;
    DL->left = temp;
    DL = temp;
    return;
}

void addBefore(dlptr &DL, int k, int data)
{
    if(DL == NULL)
        return;
    if(DL->data == k)
    {
        addFront(DL, k);
        return;
    }
    dlptr T = DL, temp = new dlnode(data);

    while( (T!=NULL) && (T->data!=k) )
        T = T->right;

    if(T==NULL)
        return;

    temp->right = T;
    temp->left = T->left;
    if(T->left)
        T->left->right = temp;
    T->left = temp;

    return;
}

void addAfter(dlptr &DL, int k, int data)
{
    if(DL == NULL)
        return;

    dlptr T = DL, temp = new dlnode(data);

    while( (T!=NULL) && (T->data!=k) )
        T = T->right;

    if(T==NULL)
        return;

    temp->left = T;
    temp->right = T->right;

    if(T->right!=NULL)
        T->right->left = temp;
    T->right = temp;


    return;
}

void swap(dlptr a, dlptr b)
{
    int temp = a->data;
    a->data = b->data;
    b->data = temp;
    return;
}

void bubbleSort(dlptr DL)
{
    int n = getSize(DL), j;
    dlptr T, temp;
    for(T=DL; (T->right!=NULL) && (--n); T=T->right)
    {
        for(temp=DL, j=0; (temp->right!=NULL) && (j<n); temp=temp->right, j++)
        {
            if(temp->data > temp->right->data)
            swap(temp, temp->right);
        }
    }
    return;
}

int main()
{
    dlptr DL = NULL;
    int k, x, y;

    takeInput(DL);

    bubbleSort(DL);
    print(DL);


    return 0;
}
