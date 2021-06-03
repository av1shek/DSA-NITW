#include<bits/stdc++.h>
using namespace std;
typedef struct bstnode *bstptr;

void takeInput(bstptr &);           /// takes input till -1
void insert(bstptr &, int);         /// insert a integer value
void insertNode(bstptr &, bstptr);  /// insert a node to with some data value
void printInorder(bstptr);          /// print left, self , right
void printPreorder(bstptr);         /// print in self, left, right
void printPostorder(bstptr);        /// print in left, right, self
void printLevelOrder(bstptr);       /// print level wise
void printReverseReversedLevelOrder(bstptr);
int getMax(bstptr);                 /// return max data(int) value in tree
int getMin(bstptr);                 /// returns min data(int) value in tree
int getIterativeMax(bstptr);        /// return max data(int) value in tree
int getIterativeMin(bstptr);        /// returns min data(int) value in tree
bstptr findbstNode(bstptr, int);    /// return a node whose data value is same as value passed else null
int getIterativeMax(bstptr);        /// return max data(int) value in tree
int getIterativeMin(bstptr);        /// returns min data(int) value in tree
void findPossibleValues(bstptr,int);/// prints a range whose possible values can be placed
void findPossibleValuesUtils(bstptr, int, int, int);     /// utility function to print range of possible values

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

void insertNode(bstptr &T, bstptr k)
{
    if(T==NULL)
        T = k;
    else if(k->data > T->data)
        insertNode(T->rchild, k);
    else if(k->data < T->data)
        insertNode(T->lchild, k);
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

void printPreorder(bstptr T)
{
    if(T==NULL)
        return;
    cout<<T->data<<" ";
    printPreorder(T->lchild);
    printPreorder(T->rchild);
    return;
}

void printPostorder(bstptr T)
{
    if(T==NULL)
        return;
    printPostorder(T->lchild);
    printPostorder(T->rchild);
    cout<<T->data<<" ";
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

int getMax(bstptr T)
{
    if(T==NULL)
    {
        cout<<"Not valid"<<endl;
        return -1;
    }
    if(T->rchild==NULL)
        return T->data;
    else
        return getMax(T->rchild);
}

int getMin(bstptr T)
{
    if(T==NULL)
    {
        cout<<"Not valid"<<endl;
        return INT_MAX;
    }
    if(T->lchild==NULL)
        return T->data;
    else
        return getMin(T->lchild);
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

int getIterativeMin(bstptr T)
{
    while(T->lchild)
        T = T->lchild;
    return T->data;
}

int getIterativeMax(bstptr T)
{
    while(T->rchild)
        T = T->rchild;
    return T->data;
}

void findPossibleValuesUtils(bstptr T, int val, int low, int high)
{
    if(T->data == val)
    {
        if(T->rchild)
            high = T->rchild->data;
        if(T->lchild)
            low = T->lchild->data;

        cout<<"greater than "<<low<<" and less than "<<high<<endl;
    }
    else if(val > T->data)
        findPossibleValuesUtils(T->rchild, val, T->data, high);
    else
        findPossibleValuesUtils(T->lchild, val, low, T->data);
    return;
}

void findPossibleValues(bstptr T, int val)
{
    bstptr temp = findbstNode(T, val);
    if(temp!=NULL)
        findPossibleValuesUtils(T, val, INT_MIN, INT_MAX);
    else
        cout<<"element not present"<<endl;
}

void printLevelOrder(bstptr T)
{
    if(T==NULL)
        return;

    queue<bstptr> q;
    q.push(T);

    while(!q.empty())
    {
        bstptr temp = q.front();
        q.pop();

        cout<<temp->data<<" ";
        if(temp->lchild)
            q.push(temp->lchild);
        if(temp->rchild)
            q.push(temp->rchild);
    }
    return;
}

void printReverseReversedLevelOrder(bstptr T)
{
    if(T==NULL)
        return;

    queue<bstptr> q;
    stack<int> s;
    q.push(T);

    while(!q.empty())
    {
        bstptr temp = q.front();
        q.pop();

        s.push(temp->data);
        if(temp->lchild)
            q.push(temp->lchild);
        if(temp->rchild)
            q.push(temp->rchild);
    }
    while(!s.empty())
    {
        cout<<s.top()<<" ";
        s.pop();
    }
    return;
}

void printReverseLevelOrder(bstptr T)
{
        if(T==NULL)
        return;

    queue<bstptr> q;
    stack<int> s;
    q.push(T);

    while(!q.empty())
    {
        bstptr temp = q.front();
        q.pop();

        s.push(temp->data);
        if(temp->rchild)
            q.push(temp->rchild);
        if(temp->lchild)
            q.push(temp->lchild);
    }
    while(!s.empty())
    {
        cout<<s.top()<<" ";
        s.pop();
    }
    return;
}

int main()
{
    bstptr T = NULL, temp;
    int k;
    takeInput(T);
    printLevelOrder(T); cout<<endl;
    printReverseReversedLevelOrder(T); cout<<endl;
    printReverseLevelOrder(T); cout<<endl;
    return 0;
}
