#include<iostream>
#include<vector>
using namespace std;
typedef struct bstnode *bstptr;

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

void printPreorder(bstptr T)
{
    if(T==NULL) return;
    cout<<T->data<<" ";
    printPreorder(T->lchild);
    printPreorder(T->rchild);
}
void printPreorder2(bstptr T)
{
    if(T==NULL) return;
    cout<<T->data<<" ";
    printPreorder2(T->rchild);
    printPreorder2(T->lchild);
}
bool isLeaf(bstptr P)
{
    if(P==NULL) return false;
    if(P->lchild==NULL && P->rchild==NULL) return true;
    return false;
}
print(vector<int> v)
{
    for(auto it:v)
        cout<<it<<" ";
    cout<<endl;
}
void generates(bstptr T, vector<int> ans, bstptr H)
{
    if(T==NULL) return;

    if(T->lchild==NULL && T->rchild==NULL)
    {

        return;
    }
    if(T->lchild==NULL || T->rchild== NULL)
    {

        return;
    }

    swap(T->rchild, T->lchild);
}
int main()
{
    bstptr T = NULL;
    vector<int> ans;
    takeInput(T);
    generates(T, ans);
    return 0;
}
