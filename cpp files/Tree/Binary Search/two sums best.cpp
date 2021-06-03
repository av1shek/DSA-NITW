#include<bits/stdc++.h>
using namespace std;
typedef struct bstnode *bstptr;

void takeInput(bstptr &);           /// takes input till -1
void insert(bstptr &, int);         /// insert a integer value
void insertNode(bstptr &, bstptr);  /// insert a node to with some data value
void printInorder(bstptr);          /// print left, self , right
bstptr findbstNode(bstptr, int);    /// return a node whose data value is same as value passed else null

struct bstnode
{
    struct bstnode *lchild;
    int data;
    struct bstnode *rchild;
    bstnode()
    {
        lchild = NULL;
        rchild = NULL;
    }
    bstnode(int k)
    {
        lchild = NULL;
        data = k;
        rchild = NULL;
    }
};

void insert(bstptr &T, int k)
{
    if(T==NULL)
        T = new bstnode(k);
    else if(k > T->data)
        insert(T->rchild, k);
    else if(k < T->data)
        insert(T->lchild, k);
    return;
}

void printInorder(bstptr T)
{
    if(T == NULL)
        return;
    printInorder(T->lchild);
    cout<<T->data<<" ";
    printInorder(T->rchild);
    return;
}

void takeInput(bstptr &T)
{
    while(true)
    {
        int temp;
        cin>>temp;

        if(temp == -1)
            break;
        insert(T, temp);
    }
}

bstptr findbstNode(bstptr T, int k)
{
    if(T==NULL || T->data==k)
        return T;
    if(k > T->data)
        return findbstNode(T->rchild, k);
    if(k < T->data)
        return findbstNode(T->lchild, k);
    return NULL;
}

bool findtwosums(bstptr T, int k, int val)
{
    stack<bstptr> stk1, stk2;
    bstptr cur1 = T;
    bstptr cur2 = T;
    int lo = 0, hi = 0;

    while(cur1)
    stk1.push(cur1), lo = cur1->data, cur1 = cur1->lchild;

    while( (lo < val) && cur1 )
    {
        while(cur1)
            stk1.push(cur1), lo = cur1->data, cur1 = cur1->lchild;
        lo = stk1.top()->data, cur1 = stk1.top()->rchild, stk1.pop();
    }

    cout<<"check -------------- val = "<<val<<" lo = "<<lo<<endl;
    while(cur2)
    stk2.push(cur2), hi = cur2->data, cur2 = cur2->rchild;

    while (lo < hi)
    {
        int sum = lo + hi;
        if (sum < k)
        {
            while(cur1)
            stk1.push(cur1), lo = cur1->data, cur1 = cur1->lchild;
            lo = stk1.top()->data, cur1 = stk1.top()->rchild, stk1.pop();
        }
        else if (sum > k)
        {
            while(cur2)
            stk2.push(cur2), hi = cur2->data, cur2 = cur2->rchild;
            hi = stk2.top()->data, cur2= stk2.top()->lchild, stk2.pop();
        }
        else
        {
            cout<<val<<" "<<lo<<" "<<hi<<endl;

            while(cur1)
            stk1.push(cur1), lo = cur1->data, cur1 = cur1->lchild;
            lo = stk1.top()->data, cur1 = stk1.top()->rchild, stk1.pop();

            while(cur2)
            stk2.push(cur2), hi = cur2->data, cur2 = cur2->rchild;
            hi = stk2.top()->data, cur2= stk2.top()->lchild, stk2.pop();
        }
    }
    return false;
}

void findthreesums(bstptr T, bstptr head, int k)
{
    if(T==NULL)
        return;
    findthreesums(T->lchild, head,  k);
    if(k - T->data > T->data)
        findtwosums(head, k - T->data, T->data);
    findthreesums(T->rchild, head, k);
    return;
}

int main()
{
    bstptr T = NULL;
    takeInput(T);
    int k; cin>>k;
    findthreesums(T, T, k);
    return 0;
}
