#include<bits/stdc++.h>
using namespace std;
typedef struct bstnode *bstptr;

void takeInput(bstptr &);           /// takes input till -1
void insert(bstptr &, int);         /// insert a integer value
void insertNode(bstptr &, bstptr);  /// insert a node to with some data value
int find(int [], int, int, int);    /// binary search to find an element in array

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

int find(int a[], int k, int low, int high)
{
    if(low<0 || high<0)
        return 0;
    if(low == high || (low+1==high))
    {
        if(a[low]==k)
            return 1;
        else if(a[high] == k)
            return 1;
        else
            return -1;
    }
    int mid = (low+high)/2;
    if(a[mid]==k)
        return 1;
    else if(a[mid]> k)
        return find(a, k, low, mid);
    else
        return find(a, k, mid, high);

}

bool solveUtils(bstptr T, int sum, int a[], int &pos)
{
    if(T == NULL)
        return false;
    solveUtils(T->lchild, sum, a, pos);
    if(find(a, sum - T->data, 0, pos-1)==1)
    {
        cout<< sum - T->data << " " << T->data <<endl;
        return true;
    }
    a[pos] = T->data;
    pos++;
    solveUtils(T->rchild, sum, a, pos);
    return false;
}

void solve(bstptr T, int sum)
{
    int a[100];
    int pos = 0;
    solveUtils(T, sum, a, pos);
    return;
}


int main()
{
    bstptr T = NULL, temp;
    int k;
    takeInput(T);
    cin>>k
       solve(T, k);
    return 0;
}



bool findTarget(bstptr T, int k)
{
    stack<bstptr> stk1, stk2;
    bstptr cur1 = T;
    bstptr cur2 = T;
    int lo = 0, hi = 0;
    while (cur1)
        stk1.emplace(cur1), lo = cur1->data, cur1 = cur1->left;
    while (cur2)
        stk2.emplace(cur2), hi = cur2->data, cur2 = cur2->right;
    while (lo < hi)
    {
        int sum = lo + hi;
        if (sum < k)
        {
            while(cur1)
                stk1.emplace(cur1), lo = cur1->data, cur1 = cur1->lchild;
            lo = stk1.top()->data, cur1 = stk1.top()->rchild, stk1.pop();
        }
        else if (sum > k)
        {
            while(cur2)
                stk2.emplace(cur2), hi = cur2->data, cur2 = cur2->rchild;
            hi = stk2.top()->data, cur2= stk2.top()->lchild, stk2.pop();
        }
        else
            return true;
    }
    return false;
}

