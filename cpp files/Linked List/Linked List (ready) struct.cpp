#include <iostream>
using namespace std;
typedef struct node  *lptr;

void insert(lptr &, int);       /// insert a element in last
void takeInput(lptr &);         /// takes input while not -1
void print(lptr);               /// prints the list
int getSize(lptr);              /// returns the size of list

struct ele
{
    int integer;
    char ch;
};
struct node
{
    struct ele data;
    struct node *next;
    node()
    {
        next=NULL;
    }
};

void insert(lptr &P, struct ele x)
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
    while(true)
    {
        struct ele temp;
        cin>>temp.integer;

        if(temp.integer == -1)
            break;

        insert(L, temp);
    }
    return;
}

void print(lptr L)
{
    while(L!=NULL)
    {
        cout<<L->data.integer<<" ";
        L = L->next;
    }
    return;
}

int getSize(lptr L)
{
    int count=0;
    while(L!=NULL)
    {
        count++;
        L = L->next;
    }
    return count;
}

int main()
{
    lptr L = NULL;
    takeInput(L);
    print(L);
    return 0;
}


